#include "helpers.h"
#include <latebit/core/events/EventStep.h>
#include <latebit/core/geometry/Box.h>
#include <latebit/core/geometry/Vector.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/WorldManager.h>

using namespace lb;

class CameraShake : public Object {
private:
  const int intensity;
  const int durationInFrames;
  Box originalView = WM.getView();
  int currentFrame = 0;

  void step() {
    if (this->currentFrame >= this->durationInFrames) {
      return stop();
    }

    this->currentFrame++;
    auto x = randomRange(-this->intensity, this->intensity);
    auto y = randomRange(-this->intensity, this->intensity);
    auto view = this->originalView;
    view.setCorner(view.getCorner() + Vector(x, y));
    WM.setView(view);
  }

public:
  CameraShake(int intensity, int durationInFrames)
      : durationInFrames(durationInFrames), intensity(intensity) {
    setType("CameraShake");
    subscribe(STEP_EVENT);
    setActive(false);
  }

  void start() {
    if (this->isActive()) {
      return;
    }

    setActive(true);
    this->originalView = WM.getView();
    this->currentFrame = 0;
  }

  void stop() {
    setActive(false);
    WM.setView(this->originalView);
  }

  int eventHandler(const Event *e) {
    if (e->getType() == STEP_EVENT) {
      this->step();
      return 1;
    }
    return 0;
  }
};