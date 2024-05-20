#include "Scene.h"
#include "characters/characters.h"
#include "helpers.h"
#include "powerups/powerups.h"
#include "props/props.h"
#include "scenes/scenes.h"
#include "ui/ui.h"
#include <latebit/core/audio/Music.h>
#include <latebit/core/objects/Object.h>

using namespace lb;

class Game : public Scene {
private:
  unique_ptr<Music> music = unique_ptr<Music>(RM.getMusic("groovy"));

public:
  void cleanup() {
    this->music->stop();

    auto objects = WM.getAllObjects();
    ObjectListIterator oli(&objects);

    for (oli.first(); !oli.isDone(); oli.next()) {
      auto type = oli.currentObject()->getType();
      if (type == "HUD" || type == "Player" || type == "Floor" ||
          type == "FoodFactory" || type == "EnemyFactory" || type == "Coral" ||
          type == "Wave") {
        WM.markForDelete(oli.currentObject());
      }
    }
  }

  void play() {
    DM.setBackground(Color::BLUE);
    new HUD();
    new Player();
    new FoodFactory();
    new EnemyFactory();
    new Floor();

    ObjectList corals = WM.objectsOfType("Coral");
    for (int i = corals.getCount(); i < 5; i++) {
      new Coral();
    }

    ObjectList waves = WM.objectsOfType("Wave");
    for (int i = waves.getCount(); i < 20; i++) {
      new Wave();
    }

    this->music->play(true);
  }

  Game() { setType("Game"); };
};