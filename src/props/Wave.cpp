#include <latebit/core/events/EventOut.h>
#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>

using namespace lb;

class Wave : public Object {
private:
  void placeOnScreen() {
    auto position = getPosition();
    position.setX(rand() % DM.getHorizontalCells());
    position.setY(rand() % DM.getVerticalCells());
    setPosition(position);
  }

  void placeOnScreen(int x) {
    auto position = getPosition();
    position.setX(x);
    position.setY(rand() % DM.getVerticalCells());
    setPosition(position);
  }

public:
  Wave() {
    setType("Wave");
    setSprite("waves");
    setSolidness(SPECTRAL);
    setVelocity(Vector(-0.5 * ((rand() % 3) + 1), 0));
    placeOnScreen();
    setAltitude(1);
  }

  int eventHandler(const Event *e) {
    if (e->getType() == OUT_EVENT) {
      placeOnScreen(DM.getHorizontalCells() + 1);
      return 1;
    }
    return 0;
  }
};