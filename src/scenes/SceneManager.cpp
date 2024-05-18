#include "Death.cpp"
#include "GameOver.cpp"
#include "GameStart.cpp"
#include "Scene.h"
#include "events/events.h"
#include <latebit/core/objects/Object.h>
#include <unordered_map>

using namespace lb;

class SceneManager : public Object {
private:
  unordered_map<string, Scene *> scenes = {{GAME_START, new GameStart()},
                                           {GAME_OVER, new GameOver()},
                                           {PLAYER_DEAD, new Death()}};
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
  }

  int eventHandler(const Event *p_e) {
    auto scene = scenes[p_e->getType()];
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