#include <latebit/core/ResourceManager.h>
#include <latebit/core/audio/Music.h>
#include <latebit/core/geometry/Vector.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <memory>

using namespace lb;
using namespace std;

class Fish : public Object {
private:
  unique_ptr<Music> swim = unique_ptr<Music>(RM.getMusic("swimback"));

public:
  Fish(Vector position) {
    setType("Fish");
    setSprite("player-idle");
    setPosition(position);
    setSolidness(SPECTRAL);
  }

  void swimStart() {
    swim->play(true);
    setSprite("player-dash");
    setVelocity(Vector(-1, 0));
  }

  void swimStop() {
    swim->stop();
    setSprite("player-idle");
    setVelocity(Vector(0, 0));
    setPosition(Vector(6, getPosition().getY()));
  }
};