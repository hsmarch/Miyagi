//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "Pause.h"
#include "ResourceManager.h"

// Game includes.
#include "GameStart.h"
#include "Star.h"

// Function prototypes.
void loadResources(void);
void populateWorld(void);
 
int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  // Show splash screen.
  df::splash();

  // Load game resources.
  loadResources();

  // Populate game world with some objects.
  populateWorld();

  // Enable player to pause game.
  new df::Pause(df::Keyboard::F10);
 
  // Run game (this blocks until game loop is over).
  GM.run();
  
  // Shut everything down.
  GM.shutDown();
}

// Load resources (sprites, sound effects, music).
void loadResources(void) {
  RM.loadSprite("sprites/up_arrow_spr.txt", "up_arrow");
  RM.loadSprite("sprites/down_arrow_spr.txt", "down");
  RM.loadSprite("sprites/left_arrow_spr.txt", "left");
  RM.loadSprite("sprites/right_arrow_spr.txt", "right");
  RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
  RM.loadSprite("sprites/gameover-spr.txt", "gameover");
  RM.loadSprite("sprites/player_spr.txt", "player");
  RM.loadSound("sounds/fire.wav", "fire");
  RM.loadSound("sounds/explode.wav", "explode");
  RM.loadSound("sounds/nuke.wav", "nuke");
  RM.loadSound("sounds/game-over.wav", "game over");
  RM.loadMusic("sounds/start-music.wav", "start music");
}

// Populate world with some objects.
void populateWorld(void) {

		
  // Create GameStart object.
  new GameStart();
}
