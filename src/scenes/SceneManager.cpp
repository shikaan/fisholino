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
  unordered_map<string, Scene *> scenes = {{GAME_START, new Game()},
                                           {GAME_OVER, new GameOver()},
                                           {PLAYER_DEAD, new Death()},
                                           {"", new Welcome()}};
  Scene *currentScene = nullptr;

public:
  SceneManager() {
    setType("SceneManager");
    for (auto &scene : scenes) {
      scene.second->setActive(false);
    }

    subscribe(GAME_START);
    subscribe(GAME_OVER);
    subscribe(PLAYER_DEAD);

    this->currentScene = scenes[""];
    this->currentScene->setActive(true);
    this->currentScene->play();
  }

  int eventHandler(const Event *e) {
    auto scene = scenes[e->getType()];
    if (scene) {
      if (this->currentScene) {
        this->currentScene->setActive(false);
        this->currentScene->cleanup();
      }
      this->currentScene = scene;
      this->currentScene->setActive(true);
      scene->play();
      return 1;
    }
    return 0;
  }
};