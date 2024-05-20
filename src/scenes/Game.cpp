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
  Music *music = RM.getMusic("groovy");
  vector<Object *> objects = {};
  vector<Wave *> waves;
  vector<Coral *> corals;

  void populateCoralsAndWaves() {
    if (corals.size() == 0) {
      auto screenWidth = DM.getHorizontalCells();
      for (int i = 0; i < 5; i++) {
        auto coral = new Coral();
        corals.push_back(coral);
        coral->setPosition(Vector(screenWidth + i * 30 + randomRange(16, 48),
                                  coral->getPosition().getY()));
      }
    }

    if (waves.size() == 0) {
      for (int i = 0; i < 20; i++) {
        waves.push_back(new Wave());
      }
    }
  }

public:
  void cleanup() {
    this->music->stop();
    for (auto object : objects) {
      WM.markForDelete(object);
    }
    for (auto wave : waves) {
      WM.markForDelete(wave);
    }
    for (auto coral : corals) {
      WM.markForDelete(coral);
    }
    objects.clear();
    waves.clear();
    corals.clear();
  }

  void play() {
    setActive(true);
    DM.setBackground(Color::BLUE);

    objects.push_back(new HUD());
    objects.push_back(new Player());
    objects.push_back(new FoodFactory());
    objects.push_back(new EnemyFactory());
    objects.push_back(new Floor());
    populateCoralsAndWaves();
    this->music->play(true);
  }

  Game() {
    setType("Game");
    // This is needed to display these props in the welcome screen
    populateCoralsAndWaves();
  };
};