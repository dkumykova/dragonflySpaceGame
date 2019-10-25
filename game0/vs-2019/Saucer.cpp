#include "Saucer.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "Explosion.h"
#include <stdlib.h>
#include "EventNuke.h"
#include "EventView.h"
#include "Points.h"
#include "Hero.h"
#include "EventHealth.h"

//constructor; 
//syntax: function saucer within class saucer
Saucer::Saucer() {
	//setup sacuer sprite
	setSprite("saucer");
	//set object type
	setType("Saucer");
	//set speed in x direction
	setVelocity(df::Vector(-.6, 0)); //1 space for every 4 frames
	registerInterest(NUKE_EVENT);
	registerInterest(HEALTH_EVENT);

	//set start location to middle of window
	int world_x = (int)WM.getBoundary().getHorizontal();
	int world_y = (int)WM.getBoundary().getVertical();
	df::Vector position(world_x / 2, world_y / 2);
	moveToStart();
}

Saucer::~Saucer() {
	//send a view event with points to interested vew objects
	//add 10 points
	df::EventView ev(POINTS_STRING, 10, true);
	WM.onEvent(&ev);
}
int Saucer::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	if (p_e->getType() == NUKE_EVENT) {
		Explosion* p_explosion = new Explosion();
		p_explosion->setPosition(this->getPosition());
		WM.markForDelete(this);
		//spawn a new one for the one destroyed
		new Saucer;
		return 1;
	}
	if (p_e->getType() == HEALTH_EVENT) {
		
		return 1;
	}
	return 0;
}

void Saucer::out() {
	if (getPosition().getX() >= 0) {
		return;
	}
	moveToStart();
	new Saucer;
}

void Saucer::moveToStart() {
	df::Vector temp_pos;

	float world_x = WM.getBoundary().getHorizontal();
	float world_y = WM.getBoundary().getVertical();

	//x is off right side of window
	temp_pos.setX(world_x + rand() % (int) world_x + 3.0f);

	//y is in vertical range
	temp_pos.setY(rand() % (int) (world_y - 4) + 4.0f);

	//if collision at spawn location, move until none
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (!collision_list.isEmpty()) {
		temp_pos.setX(temp_pos.getX() + 1);
		collision_list = WM.getCollisions(this, temp_pos);
	}
	WM.moveObject(this, temp_pos);
}

void Saucer::hit(const df::EventCollision* p_collision_event) {
	df::Sound* p_sound = RM.getSound("explode");
	
	if ((p_collision_event->getObject1()->getType() == "Saucer") &&
		(p_collision_event->getObject2()->getType() == "Saucer")) {
		return;
	}
	if ((p_collision_event->getObject1()->getType() == "HealthPack") ||
		(p_collision_event->getObject2()->getType() == "HealthPack")) {
		return;
	}
	if ((p_collision_event->getObject1()->getType() == "Bullet") ||
		(p_collision_event->getObject2()->getType() == "Saucer")) {
		//create explosion
		Explosion* p_explosion = new Explosion();
		p_explosion->setPosition(this->getPosition());
		p_sound->play();
		//spawn a new one for the one destroyed
		new Saucer;
	}

	if ((p_collision_event->getObject1()->getType() == "Hero") ||
		(p_collision_event->getObject2()->getType() == "Hero")) {

		if (p_collision_event->getObject1()->getType() == "Hero") {
			Hero* hero = dynamic_cast <Hero*> (p_collision_event->getObject1());
			//reduce hero health
			hero->handleHealth();
			if (hero->health <= 0) {
				WM.markForDelete(p_collision_event->getObject1());
			}
			WM.markForDelete(p_collision_event->getObject2());
		}

		if (p_collision_event->getObject2()->getType() == "Hero") {
			Hero* hero = dynamic_cast <Hero*> (p_collision_event->getObject2());
			//reduce hero health
			hero->handleHealth();
			if (hero->health <= 0) {
				WM.markForDelete(p_collision_event->getObject2());
			}
			WM.markForDelete(p_collision_event->getObject1());
		}
		p_sound->play();
		
		
	}

	
}