#include <stdio.h>

#include "src/GameStart.cpp"
#include <latebit/Configuration.h>
#include <latebit/GameManager.h>
#include <latebit/Logger.h>
#include <latebit/ResourceManager.h>

using namespace lb;
using namespace std;

void loadSprite(const char *label) {
  std::string filePath = "assets/sprites/" + std::string(label) + ".txt";
  if (RM.loadSprite(filePath.c_str(), label) != 0) {
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

  if (RM.loadSound("assets/audio/jump.wav", "dash") != 0) {
    printf("Error loading food sound\n");
  };
  if (RM.loadMusic("assets/audio/music.mp3", "music") != 0) {
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
