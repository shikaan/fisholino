#include "Scene.h"
#include "events/events.h"
#include "helpers.h"
#include <latebit/core/ResourceManager.h>
#include <latebit/core/events/EventKeyboard.h>
#include <latebit/core/events/EventStep.h>
#include <latebit/core/geometry/Box.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/WorldManager.h>
#include <props/props.h>

using namespace lb;

class FakePlayer : public Object {
public:
  FakePlayer(Vector position) {
    setType("FakePlayer");
    setSprite("player-idle");
    setPosition(position);
    setSolidness(SPECTRAL);
  }
};

class Text : public Object {
public:
  Text(Vector position) {
    setType("Text");
    setPosition(position);
    setSolidness(SPECTRAL);
    setBox(Box(DM.getHorizontalCells(), DM.getVerticalCells()));
    setAltitude(4);
  };

  int draw() {
    int result = 0;
    auto position = getPosition();
    result += DM.drawRectangle(position - Vector(104, 70), 208, 56,
                               Color::ORANGE, Color::ORANGE);
    result += DM.drawRectangle(position - Vector(100, 66), 200, 48,
                               Color::WHITE, Color::WHITE);
    result +=
        DM.drawString(position - Vector(0, 60), "FISHOLINO", TEXT_ALIGN_CENTER,
                      Color::DARK_BLUE, TEXT_SIZE_XLARGE);
    result +=
        DM.drawString(position - Vector(0, 30), "\"A Charged Breakout\"",
                      TEXT_ALIGN_CENTER, Color::DARK_GRAY, TEXT_SIZE_NORMAL);

    result += DM.drawString(position + Vector(0, 32), "PRESS [ENTER] TO START",
                            TEXT_ALIGN_CENTER, Color::WHITE, TEXT_SIZE_NORMAL);

    return result;
  }
};

class Welcome : public Scene {
private:
  static const int INITIAL_DASHING_STEPS = 230;
  enum State { IDLE, STARTING, READY };

  FakePlayer *player = new FakePlayer(CENTER - Vector(8, 8) + Vector(0, 8));
  Text *text = new Text(CENTER);
  Floor *floor = new Floor();

  Sound *confirmSound = RM.getSound("confirm");
  Music *swimSound = RM.getMusic("swimback");
  int dashingSteps = INITIAL_DASHING_STEPS;
  State state = IDLE;

public:
  Welcome() {
    setType("Welcome");
    DM.setBackground(Color::BLUE);
    subscribe(KEYBOARD_EVENT);
    subscribe(STEP_EVENT);
  }

  void play() {}

  void cleanup() {
    WM.markForDelete(player);
    WM.markForDelete(text);
    WM.markForDelete(floor);
  }

  int eventHandler(const Event *e) {
    if (e->getType() == KEYBOARD_EVENT) {
      auto keyEvent = dynamic_cast<const EventKeyboard *>(e);
      if (keyEvent->getKey() == Keyboard::RETURN) {
        this->confirmSound->play();
        this->unsubscribe(KEYBOARD_EVENT);
        this->state = STARTING;
        return 1;
      }
    }

    if (this->state == STARTING && e->getType() == STEP_EVENT) {
      dashingSteps--;

      if (dashingSteps == INITIAL_DASHING_STEPS - 30) {
        this->player->setSprite("player-dash");
        this->player->setVelocity(Vector(-1, 0));
        this->text->setVelocity(Vector(-4, 0));
        this->swimSound->play(true);
      }

      if (this->player->getPosition().getX() <= 6) {
        this->player->setVelocity(Vector(0, 0));
        this->player->setSprite("player-idle");
        this->player->setPosition(
            Vector(6, this->player->getPosition().getY()));
        this->swimSound->stop();
        this->state = READY;
      }

      return 1;
    }

    if (this->state == READY && e->getType() == STEP_EVENT) {
      dashingSteps--;

      if (dashingSteps == 0) {
        WM.onEvent(new GameStartEvent());
      }
      return 1;
    }

    return 0;
  }
};