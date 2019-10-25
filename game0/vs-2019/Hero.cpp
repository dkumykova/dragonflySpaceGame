#include "Hero.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include <stdlib.h>
#include "Bullet.h"
#include "EventMouse.h"
#include "EventKeyboard.h"
#include "EventNuke.h"
#include "EventView.h"
#include "GameOver.h"
#include "EventHealth.h"
#include "HealthPack.h"

Hero::Hero() {
	move_slowdown = 2;
	move_countdown = move_slowdown;
	fire_slowdown = 30;
	fire_countdown = fire_slowdown;
	nuke_count = 1;
	health = 50;

	//link to ship sprite
	setSprite("ship");
	//listen for keyboard events
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MSE_EVENT);
	
	//create reticle
	p_reticle = new Reticle();
	p_reticle->draw();
	//setSolidness(df::SOFT);

	setType("Hero");
	df::Vector position(7, WM.getBoundary().getVertical() / 2);
	setPosition(position);
}

Hero::~Hero() {
	//GM.setGameOver();
	WM.markForDelete(p_reticle);
	df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
	df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
	
	new GameOver;

	
}
//respond to keyboard event only; casts generic event
//object pointer as an event keyboard pointer then calls kbd from hero
int Hero::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_key_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_key_event);
		return 1;
	}
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event =
			dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	if (p_e->getType() == HEALTH_EVENT) {
		handleHealth();
		return 1;
	}
	return 0;
}

//look at key pressed and act
void Hero::kbd(const df::EventKeyboard *p_key_event) {
	switch (p_key_event->getKey()) {
	case df::Keyboard::Q:
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED) {
			//GM.setGameOver();
			WM.markForDelete(this);
		}
		break;
	case df::Keyboard::W:
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			move(-1);
		}
		break;
	case df::Keyboard::S:
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			move(+1);
		}
		break;
	case df::Keyboard::SPACE:
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			nuke();
		}
		break;
	default:
		return;
	};
	return;
}

void Hero::move(int dy) {

	//check if it's ok to move
	if (move_countdown > 0) {
		return;
	}
	move_countdown = move_slowdown;

	//if stays in window, allow object to move
	df::Vector new_position(getPosition().getX(), getPosition().getY() + dy);
	if ((new_position.getY() > 3) && (new_position.getY() < WM.getBoundary().getVertical())) {
		WM.moveObject(this, new_position);
	}
}

//keep track of when hero can move
void Hero::step() {
	//move countdown
	move_countdown--;
	if (move_countdown < 0) {
		move_countdown = 0;
	}
	fire_countdown--;
	if (fire_countdown < 0) {
		fire_countdown = 0;
	}
}

void Hero::fire(df::Vector target) {
	if (fire_countdown > 0) {
		return;
	}
	fire_countdown = fire_slowdown;

	//compute normalized vector to position, scale by speed (1)
	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);
	Bullet* p = new Bullet(getPosition());
	p->setVelocity(v);

	df::Sound* p_sound = RM.getSound("fire");
	p_sound->play();

}

void Hero::mouse(const df::EventMouse *p_mouse_event) {
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
	(p_mouse_event->getMouseButton() == df::Mouse::LEFT)){
		fire(p_mouse_event->getMousePosition());
	}
}

void Hero::nuke() {
	if (!nuke_count) {
		return;
	}
	nuke_count--;

	//create nuke event and send to interested objects
	EventNuke nuke;
	WM.onEvent(&nuke);
	
	//send view event with nukes to interested view object
	df::EventView ev("Nukes", -1, true);
	WM.onEvent(&ev);

	df::Sound* p_sound = RM.getSound("nuke");
	p_sound->play();
}

void Hero::handleHealth() {
	if (!health) {
		return;
	}
	health = health - 10;

	//create health event and send to interested objects
	EventHealth h;
	WM.onEvent(&h);

	//send view event with updated health value 
	df::EventView ev("Health", -10, true);
	WM.onEvent(&ev);

	//spawn healthpack on low health
	if (health <= 30) {
		new HealthPack();
	}
	

}