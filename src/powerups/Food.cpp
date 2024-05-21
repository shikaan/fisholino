#include "events/events.h"
#include "helpers.h"
#include "props/props.h"
#include "state.h"
#include "ui/ui.h"
#include <latebit/core/events/EventOut.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/WorldManager.h>

using namespace lb;

class Food : public Object {
private:
  Sound *sound = RM.getSound("food");

  void initialize() {
    const static auto h = DM.getHorizontalCells();
    const static auto v = DM.getVerticalCells();

    Vector position(randomRange(h, 2 * h),
                    randomRange(HUD::HEIGHT + 1,
                                v - Floor::HEIGHT - 1 -
                                    getAnimation().getSprite()->getHeight()));
    setPosition(position);
    setVelocity(Vector(-0.25, 0));
  }

public:
  Food() {
    setType("Food");
    setSprite("food");
    setSolidness(SOFT);
    initialize();
  }

  int eventHandler(const Event *e) {
    if (e->getType() == OUT_EVENT) {
      initialize();
      return 1;
    }

    if (isCollisionWith(e, "Player")) {
      WM.markForDelete(this);
      sound->play();
      State::addScore(5);
      return 1;
    }

    return 0;
  }
};