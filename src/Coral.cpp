#include "./Floor.cpp"
#include "./helpers.h"
#include <latebit/Animation.h>
#include <latebit/DisplayManager.h>
#include <latebit/EventOut.h>
#include <latebit/Object.h>

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
  Coral() {
    setType("Coral");
    setSprite("coral");
    setSolidness(SPECTRAL);

    setPosition(Vector(0, DM.getVerticalCells() - getBox().getHeight() -
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
