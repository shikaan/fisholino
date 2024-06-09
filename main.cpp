#include <stdio.h>

#include "./scenes/scenes.h"
#include <latebit/core/GameManager.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/core/configuration/Configuration.h>
#include <latebit/utils/Logger.h>

using namespace lb;
using namespace std;

void loadSprite(const char *label) {
  std::string filePath = "assets/sprites/" + std::string(label) + ".txt";
  if (RM.loadTextSprite(filePath.c_str(), label) != 0) {
    printf("Error loading %s sprite\n", label);
  };
}

void loadSound(const char *label) {
  std::string filePath = "assets/audio/" + std::string(label) + ".lbsfx";
  if (RM.loadSound(filePath, label) != 0) {
    printf("Error loading %s sound\n", label);
    exit(1);
  };
}

void loadMusic(const char *label) {
  std::string filePath = "assets/audio/" + std::string(label) + ".lbmus";
  if (RM.loadMusic(filePath, label) != 0) {
    printf("Error loading %s music\n", label);
    exit(1);
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

  loadSound("dash");
  loadSound("death");
  loadSound("confirm");
  loadSound("bad");
  loadSound("food");
  loadSound("swimback");

  loadMusic("groovy");
}

int main() {
  Configuration::fromFile("latebit.cfg");
  GM.startUp();

  loadResources();
  auto SM = new SceneManager();

  WM.onEvent(new BootEvent());
  GM.run();

  return 0;
}
