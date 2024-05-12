#include <latebit/core/objects/Object.h>

using namespace lb;

class Bubbles : public Object {
public:
  Bubbles(Vector position) {
    setType("Bubbles");
    setSprite("bubbles");
    setSolidness(SPECTRAL);
    setVelocity(Vector(0, -1));
    setPosition(position);
    setAltitude(2);
  }
};