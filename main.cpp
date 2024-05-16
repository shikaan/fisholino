#include <stdio.h>

#include "scenes/scenes.h"
#include <latebit/core/configuration/Configuration.h>
#include <latebit/core/GameManager.h>
#include <latebit/utils/Logger.h>
#include <latebit/core/ResourceManager.h>

using namespace lb;
using namespace std;

void loadSprite(const char *label) {
  std::string filePath = "assets/sprites/" + std::string(label) + ".txt";
  if (RM.loadTextSprite(filePath.c_str(), label) != 0) {
    printf("Error loading %s sprite\n", label);
  };
}

void loadResources() {
  loadSprite("player-idle");
  loadSprite("player-dash");
  loadSprite("coral");
  loadSprite("bubbles");
  loadSprite("enemy");
  loadSprite("food");
  loadSprite("waves");

  if (RM.loadSound("assets/audio/dash.lbtune", "dash") != 0) {
    printf("Error loading dash sound\n");
  };
  if (RM.loadMusic("assets/audio/groovy.lbtune", "music") != 0) {
    printf("Error loading music\n");
  };
}

int main() {
  Configuration::fromFile("latebit.cfg");
  GM.startUp();

  loadResources();

  DM.setBackground(Color::BLUE);
  new GameStart();

  GM.run();

  return 0;
}
