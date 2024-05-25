#include <latebit/core/objects/Object.h>
#include <latebit/core/events/EventOut.h>
#include <latebit/core/objects/WorldManager.h>
#include <functional>

using namespace lb;
using namespace std;

class Bubbles : public Object {
private:
  function<void(Bubbles*)> onOut;
public:
  Bubbles(Vector position, function<void(Bubbles*)> onOut) {
    setType("Bubbles");
    setSprite("bubbles");
    setSolidness(SPECTRAL);
    setVelocity(Vector(0, -1));
    setPosition(position);
    setAltitude(2);
    subscribe(OUT_EVENT);
    this->onOut = onOut;
  }

  int eventHandler(const Event *event) {
    if (event->getType() == OUT_EVENT) {
      this->onOut(this);
    }
    return 0;
  }
};