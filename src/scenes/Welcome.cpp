#include "Scene.h"
#include "events/events.h"
#include "helpers.h"
#include "ui/ui.h"
#include <latebit/core/ResourceManager.h>
#include <latebit/core/events/EventKeyboard.h>
#include <latebit/core/events/EventStep.h>
#include <latebit/core/geometry/Box.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/WorldManager.h>
#include <props/props.h>

using namespace lb;

class Welcome : public Scene {
private:
  static const int INITIAL_DASHING_STEPS = 200;
  enum State { IDLE, STARTING, READY };

  unique_ptr<Fish> player = nullptr;
  unique_ptr<WelcomeText> text = nullptr;
  unique_ptr<Floor> floor = nullptr;
  unique_ptr<Sound> confirm = nullptr;

  int dashingSteps = INITIAL_DASHING_STEPS;
  State state = IDLE;

public:
  Welcome() {
    setType("Welcome");
    DM.setBackground(Color::BLUE);
    subscribe(KEYBOARD_EVENT);
    subscribe(STEP_EVENT);
  }

  void play() {
    player = make_unique<Fish>(CENTER - Vector(8, 0));
    text = make_unique<WelcomeText>(CENTER);
    floor = make_unique<Floor>();
    confirm = unique_ptr<Sound>(RM.getSound("confirm"));

    for (int i = 0; i < 5; i++) {
      new Coral();
    }

    for (int i = 0; i < 20; i++) {
      new Wave();
    }
  }

  void cleanup() {
    WM.markForDelete(player.get());
    WM.markForDelete(text.get());
    WM.markForDelete(floor.get());

    // Deliberately not deleting the corals and waves
    // They will be taken over by the Game Scene
  }

  int eventHandler(const Event *e) {
    if (e->getType() == KEYBOARD_EVENT) {
      auto keyEvent = dynamic_cast<const EventKeyboard *>(e);
      if (keyEvent->getKey() == Keyboard::RETURN) {
        this->unsubscribe(KEYBOARD_EVENT);
        this->confirm->play();
        this->state = STARTING;
        return 1;
      }
    }

    if (e->getType() == STEP_EVENT) {
      if (this->state == IDLE)
        return 0;

      dashingSteps--;

      switch (state) {
      case STARTING: {
        if (dashingSteps == INITIAL_DASHING_STEPS - 30) {
          this->player->swimStart();
          this->text->setVelocity(Vector(-4, 0));
        }

        if (this->player->getPosition().getX() <= 6) {
          this->player->swimStop();
          this->state = READY;
        }

        return 1;
      }
      case READY: {
        if (dashingSteps == 0) {
          WM.onEvent(new GameStartEvent());
        }
        return 1;
      }
      default:
        return 0;
      }
    }

    return 0;
  }
};