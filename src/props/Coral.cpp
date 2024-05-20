#include "./Floor.cpp"
#include "helpers.h"
#include <latebit/core/events/EventOut.h>
#include <latebit/core/graphics/Animation.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>

using namespace lb;

class Coral : public Object {
private:
  void initialize() {
    static const auto h = DM.getHorizontalCells();

    Vector position = getPosition();
    position.setX(randomRange(h, 2 * h));
    setPosition(position);

    Animation animation = getAnimation();
    static int frames = animation.getSprite()->getFrameCount();

    animation.setIndex(randomRange(frames));
    setAnimation(animation);
  }

public:
  Coral(int x = 0) {
    setType("Coral");
    setSprite("coral");
    setSolidness(SPECTRAL);

    setPosition(Vector(x, DM.getVerticalCells() - getBox().getHeight() -
                              Floor::HEIGHT));
    setVelocity(Vector(-1, 0));

    // Freeze animation
    Animation animation = getAnimation();
    animation.setSlowdownCount(STOP_ANIMATION_SLOWDOWN);
    setAnimation(animation);
    subscribe(OUT_EVENT);

    initialize();
  }

  int eventHandler(const Event *p_e) {
    if (p_e->getType() == OUT_EVENT) {
      initialize();
      return 1;
    }
    return 0;
  }
};
