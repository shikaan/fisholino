#include "./Bubbles.cpp"
#include "./Floor.cpp"
#include "./GameOverEvent.cpp"
#include "./HUD.cpp"
#include "./helpers.h"
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/events/EventCollision.h>
#include <latebit/core/events/EventKeyboard.h>
#include <latebit/core/events/EventStep.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/core/objects/WorldManager.h>
#include <latebit/core/audio/Sound.h>
#include <latebit/utils/Math.h>

using namespace lb;

class Player : public Object {
private:
  int dashingTicks = 0;
  int slowdown = 0;
  Sound *dash;

  int keyboard(Keyboard::Key key) {
    if (key == Keyboard::UPARROW) {
      move(-1);
      return 1;
    } else if (key == Keyboard::DOWNARROW) {
      move(1);
      return 1;
    } else if (key == Keyboard::SPACE) {
      dashingTicks = 10;
      setVelocity(Vector(2, 0));
      setSprite("player-dash");
      this->dash->play();
      return 1;
    }
    return 0;
  }

  void move(int dy) {
    auto position = getPosition();
    position.setY(clamp((int)position.getY() + dy * 4.0, HUD::HEIGHT + 1.0,
                        DM.getVerticalCells() - (Floor::HEIGHT) -
                            (int)this->getBox().getHeight() - 1));
    setPosition(position);
  }

  void resetPosition() { setPosition(Vector(6, getPosition().getY())); }

public:
  Player() {
    setType("Player");
    setSprite("player-idle");
    setSolidness(HARD);
    setPosition(Vector(6, DM.getVerticalCells() / 2.0));
    subscribe(KEYBOARD_EVENT);
    subscribe(STEP_EVENT);
    subscribe(COLLISION_EVENT);
    this->slowdown = getAnimation().getSprite()->getSlowdown();
    this->dash = RM.getSound("dash");
  }

  int eventHandler(const Event *p_e) {
    if (p_e->getType() == KEYBOARD_EVENT) {
      auto keyboard_event = static_cast<const EventKeyboard *>(p_e);
      if (keyboard_event->getKeyboardAction() != KEY_PRESSED) {
        return 0;
      }

      auto key = keyboard_event->getKey();
      return keyboard(key);
    }

    if (p_e->getType() == STEP_EVENT) {
      if (dashingTicks > 0) {
        dashingTicks--;
        if (dashingTicks == 0) {
          setSprite("player-idle");
          setVelocity(Vector(-1, 0));
        }
      }

      if (getPosition().getX() < 6) {
        setVelocity(Vector(0, 0));
        resetPosition();
      }

      if (rand() % 100 == 0) {
        new Bubbles(getPosition() + Vector(16, 0));
      }

      return 1;
    }

    if (isCollisionWith(p_e, "Enemy")) {
      WM.onEvent(new GameOverEvent());
      return 1;
    }

    return 0;
  }
};