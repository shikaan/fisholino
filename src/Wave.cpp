#include <latebit/Colors.h>
#include <latebit/DisplayManager.h>
#include <latebit/EventOut.h>
#include <latebit/Object.h>

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

  int eventHandler(const Event *p_e) {
    if (p_e->getType() == OUT_EVENT) {
      placeOnScreen(DM.getHorizontalCells() + 1);
      return 1;
    }
    return 0;
  }
};