#include "Death.cpp"
#include "Game.cpp"
#include "GameOver.cpp"
#include "Scene.h"
#include "Welcome.cpp"
#include "events/events.h"
#include <latebit/core/objects/Object.h>
#include <unordered_map>

using namespace lb;

class SceneManager : public Object {
private:
  Game game = Game();
  GameOver gameOver = GameOver();
  Death death = Death();
  Welcome welcome = Welcome();

  unordered_map<string, Scene *> eventToScene = {{GAME_START, &game},
                                                 {GAME_OVER, &gameOver},
                                                 {PLAYER_DEAD, &death},
                                                 {BOOT, &welcome}};

  Scene *currentScene = nullptr;

public:
  SceneManager() {
    setType("SceneManager");
    gameOver.setActive(false);
    death.setActive(false);
    welcome.setActive(false);
    // To receive the boot event. That's the only case where we need two scenes
    // active at the same time.
    game.setActive(true);

    subscribe(GAME_START);
    subscribe(GAME_OVER);
    subscribe(PLAYER_DEAD);
    subscribe(BOOT);
  }

  int eventHandler(const Event *e) {
    auto it = eventToScene.find(e->getType());
    if (it != eventToScene.end()) {
      auto &scene = it->second;
      if (this->currentScene) {
        this->currentScene->setActive(false);
        this->currentScene->cleanup();
      }
      scene->setActive(true);
      scene->play();
      this->currentScene = scene;
      return 1;
    }
    return 0;
  }
};