#include <latebit/core/audio/Music.h>
#include <latebit/core/objects/Object.h>
#include "./Coral.cpp"
#include "./EnemyFactory.cpp"
#include "./Floor.cpp"
#include "./FoodFactory.cpp"
#include "./GameOver.cpp"
#include "./GameStartEvent.cpp"
#include "./HUD.cpp"
#include "./Player.cpp"
#include "./Wave.cpp"
#include "helpers.h"

using namespace lb;

class GameStart : public lb::Object {
private:
  Music *music = RM.getMusic("music");

public:
  void start() {
    new HUD();
    new Player();
    new FoodFactory();
    new EnemyFactory();

    new Floor();
    for (int i = 0; i < 5; i++) {
      auto coral = new Coral();
      coral->setPosition(
          Vector(i * 30 + randomRange(16, 48), coral->getPosition().getY()));
    }
    for (int i = 0; i < 20; i++)
      new Wave;
    this->music->play(true);
    new GameOver();
  }

  GameStart() {
    setType("GameStart");
    subscribe(GAME_START);
    this->music = RM.getMusic("music");
    start();
  };

  int eventHandler(const Event *p_e) {
    if (p_e->getType() == GAME_START) {
      start();
      return 1;
    }

    return 0;
  };
};