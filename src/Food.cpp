#include "./Floor.cpp"
#include "./HUD.cpp"
#include "./ScoreEvent.cpp"
#include "./helpers.h"
#include <latebit/DisplayManager.h>
#include <latebit/EventOut.h>
#include <latebit/Object.h>
#include <latebit/WorldManager.h>

using namespace lb;

class Food : public Object {
private:
  void initialize() {
    const static auto h = DM.getHorizontalCells();
    const static auto v = DM.getVerticalCells();

    Vector position(randomRange(h, 2 * h),
                    randomRange(HUD::HEIGHT + 1, v - Floor::HEIGHT - 1));
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

  int eventHandler(const Event *p_e) {
    if (p_e->getType() == OUT_EVENT) {
      initialize();
      return 1;
    }

    if (isCollisionWith(p_e, "Player")) {
      WM.markForDelete(this);
      WM.onEvent(new ScoreEvent(5));
      return 1;
    }

    return 0;
  }
};