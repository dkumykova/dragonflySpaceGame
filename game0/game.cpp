//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "vs-2019/Points.h"
#include "vs-2019/Saucer.h"
#include "vs-2019/Bullet.h"
#include "vs-2019/Hero.h"
#include "vs-2019/Star.h"
#include "vs-2019/GameStart.h"
#include "Pause.h"



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

  //load stuff
  loadResources();
  //populate
  populateWorld();
  
  new df::Pause(df::Keyboard::F10);

  GM.run();

  // Shut everything down.
  GM.shutDown();
}


void loadResources(void) {
	//load saucer sprite
	RM.loadSprite("sprites/saucer-spr.txt", "saucer");
	RM.loadSprite("sprites/ship-spr.txt", "ship");
	RM.loadSprite("sprites/bullet-spr.txt", "bullet");
	RM.loadSprite("sprites/explosion-spr.txt", "explosion");
	RM.loadSprite("sprites/gameover-spr.txt", "gameover");
	RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
	RM.loadSprite("sprites/healthpack-spr.txt", "healthpack");

	RM.loadSound("sounds/fire.wav", "fire");
	RM.loadSound("sounds/explode.wav", "explode");
	RM.loadSound("sounds/nuke.wav", "nuke");
	RM.loadSound("sounds/game-over.wav", "gameOver");
	RM.loadSound("sounds/health-pickup.wav", "healthpickup");

	RM.loadMusic("sounds/start-music.wav", "startMusic");
	RM.loadMusic("sounds/game-music.wav", "gameMusic");
}


void populateWorld(void) {
	

	for (int j = 0; j < 15; j++) {
		new Star;
	}

	new GameStart();

}

