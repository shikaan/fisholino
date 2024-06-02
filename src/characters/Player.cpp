#include "events/events.h"
#include "helpers.h"
#include "props/props.h"
#include "ui/ui.h"
#include <latebit/core/GameManager.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/core/audio/Sound.h>
#include <latebit/core/events/EventCollision.h>
#include <latebit/core/events/EventKeyboard.h>
#include <latebit/core/events/EventStep.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/ObjectList.h>
#include <latebit/core/objects/ObjectListIterator.h>
#include <latebit/core/objects/WorldManager.h>
#include <latebit/utils/Math.h>

using namespace lb;

class Player : public Object {
private:
  const int initialSlowdown;
  const int INITIAL_DASHING_STEPS = 15;
  const int INITIAL_COOLDOWN_STEPS = 30;
  int dashingSteps = 0;
  int cooldownSteps = 0;
  // This cannot be made smart: the garbage collection would delete the sound
  // from resource manager
  Sound *dash = RM.getSound("dash");
  Sound *bad = RM.getSound("bad");
  bool isDead = false;

  int keyboard(Keyboard::Key key) {
    if (key == Keyboard::UPARROW) {
      move(-1);
      return 1;
    } else if (key == Keyboard::DOWNARROW) {
      move(1);
      return 1;
    } else if (key == Keyboard::P) {
      if (GM.isPaused())
        GM.resume();
      else
        GM.pause();
    } else if (key == Keyboard::SPACE && cooldownSteps <= 0) {
      dashingSteps = INITIAL_DASHING_STEPS;
      cooldownSteps = INITIAL_COOLDOWN_STEPS;
      setVelocity(Vector(2, 0));
      setSprite("player-dash");
      this->dash->play();
      return 1;
    }
    return 0;
  }

  void move(int dy) {
    auto position = getPosition();
    position.setY(clamp(position.getY() + dy * 4.0, HUD::HEIGHT + 1.0,
                        DM.getVerticalCells() - (Floor::HEIGHT) -
                            (int)this->getBox().getHeight() - 1));
    setPosition(position);
  }

  void resetPosition() { setPosition(Vector(6, getPosition().getY())); }

public:
  Player() : initialSlowdown(10) {
    setType("Player");
    setSprite("player-idle");
    setSolidness(HARD);
    setPosition(Vector(6, DM.getVerticalCells() / 2.0));
    subscribe(KEYBOARD_EVENT);
    subscribe(STEP_EVENT);
    subscribe(COLLISION_EVENT);
    subscribe(OUT_EVENT);
  }

  ~Player() {
    ObjectList bubbles = WM.objectsOfType("Bubbles");
    ObjectListIterator it(&bubbles);
    for (it.first(); !it.isDone(); it.next()) {
      WM.markForDelete(it.currentObject());
    }
  }

  int eventHandler(const Event *e) {
    if (this->isDead) {
      return 0;
    }

    if (e->getType() == KEYBOARD_EVENT) {
      auto keyboard_event = static_cast<const EventKeyboard *>(e);
      if (keyboard_event->getKeyboardAction() != KEY_PRESSED) {
        return 0;
      }

      auto key = keyboard_event->getKey();
      return keyboard(key);
    }

    if (GM.isPaused()) {
      return 0;
    }

    if (e->getType() == OUT_EVENT) {
      this->bad->play();
      cooldownSteps = 200;
      return 1;
    }

    if (e->getType() == STEP_EVENT) {
      if (cooldownSteps > 0) {
        cooldownSteps--;
      }

      if (dashingSteps > 0) {
        dashingSteps--;
        if (dashingSteps == 0) {
          setSprite("player-idle");
          setVelocity(Vector(-1, 0));
        }
      }

      if (getPosition().getX() < 6) {
        setVelocity(Vector(0, 0));
        resetPosition();
      }

      if (rand() % 100 == 0) {
        auto b = new Bubbles(getPosition() + Vector(16, 0),
                             [this](Bubbles *b) { WM.markForDelete(b); });
      }

      return 1;
    }

    if (isCollisionWith(e, "Enemy")) {
      this->isDead = true;
      WM.onEvent(new PlayerDeadEvent());
      return 1;
    }

    return 0;
  }
};