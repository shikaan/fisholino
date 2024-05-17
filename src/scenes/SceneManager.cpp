#include <latebit/core/objects/Object.h>
#include "events/events.h"
#include "GameStart.cpp"
#include "GameOver.cpp"
#include <unordered_map>
#include "Scene.h"

using namespace lb;

class SceneManager : public Object {
  private:
    unordered_map<string, Scene*> scenes = {
        {GAME_START, new GameStart()},
        {GAME_OVER, new GameOver()},
    };
    Scene *currentScene = nullptr;

  public:
    SceneManager() {
      setType("SceneManager");
      subscribe(GAME_START);
      subscribe(GAME_OVER);
    }

    int eventHandler(const Event *p_e) {
      auto scene = scenes[p_e->getType()];
      if (scene) {
        if (this->currentScene) {
          this->currentScene->cleanup();
        }
        this->currentScene = scene;
        scene->play();
        return 1;
      }
      return 0;
    }
};