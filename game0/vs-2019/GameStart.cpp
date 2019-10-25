#include "GameStart.h"
#include "EventKeyboard.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "Points.h"
#include "Saucer.h"
#include "Hero.h"
#include "HealthPack.h"
#include "ResourceManager.h"

GameStart::GameStart() {
	setSprite("gamestart");

	setType("GameStart");
	registerInterest(df::KEYBOARD_EVENT);

	start_music = RM.getMusic("startMusic");
	game_music = RM.getMusic("gameMusic");
	playMusic(start_music);
	setLocation(df::CENTER_CENTER);

}

int GameStart::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard* p_key_event =
			(df::EventKeyboard *) p_e;
		
		switch (p_key_event->getKey()) {
		case df::Keyboard::P:
			start();
			break;
		case df::Keyboard::Q:
			GM.setGameOver();
			break;
		default:
			break;
		}
		
		return 1;
	}
	return 0;
}

void GameStart::start() {
	for (int i = 0; i < 7; i++) {
		new Saucer;
	}


	new Hero;

	//HUD
	new Points;
	df::ViewObject* p_vo = new df::ViewObject; //count nukes
	p_vo->setLocation(df::TOP_LEFT);
	p_vo->setViewString("Nukes");
	p_vo->setValue(1);
	p_vo->setColor(df::YELLOW);

	df::ViewObject* p_health = new df::ViewObject; //keep track of health
	p_health->setLocation(df::TOP_CENTER);
	p_health->setViewString("Health");
	p_health->setValue(50);
	p_health->setColor(df::GREEN);

	setActive(false);
	start_music->pause();

	playMusic(game_music);
}

int GameStart::draw() {
	return df::Object::draw();
}

void GameStart::playMusic(df::Music *song) {
	song->play();
}