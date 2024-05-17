#include <latebit/core/audio/Music.h>
#include <latebit/core/objects/Object.h>
#include "props/props.h"
#include "scenes/scenes.h"
#include "characters/characters.h"
#include "powerups/powerups.h"
#include "ui/ui.h"
#include "helpers.h"
#include "Scene.h"

using namespace lb;

class GameStart : public Scene {
private:
  Music *music = RM.getMusic("music");
  vector<Object *> objects = {};


public:
  void cleanup() {
    for (auto object : objects) {
      WM.markForDelete(object);
    }
    objects.clear();
  }
  
  void play() {
    setActive(true);
    DM.setBackground(Color::BLUE);

    objects.push_back(new HUD());
    objects.push_back(new Player());
    objects.push_back(new FoodFactory());
    objects.push_back(new EnemyFactory());

    objects.push_back(new Floor());
    for (int i = 0; i < 5; i++) {
      auto coral = new Coral();
      objects.push_back(coral);
      coral->setPosition(
          Vector(i * 30 + randomRange(16, 48), coral->getPosition().getY()));
    }
    
    for (int i = 0; i < 20; i++) {
      auto wave = new Wave();
      objects.push_back(wave);
    }

    this->music->play(true);
  }

  GameStart() {
    setType("GameStart");
    this->music = RM.getMusic("music");
    setActive(false);
  };
};