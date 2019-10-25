#include "HealthPack.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include <stdlib.h>
#include "EventView.h"
#include "Hero.h"
#include "EventHealth.h"


HealthPack::HealthPack() {

	setSprite("healthpack");
	//set object type
	setType("HealthPack");
	//set speed in x direction
	setVelocity(df::Vector(-1.0, 0)); //move faster so they're harder to catch
	registerInterest(HEALTH_EVENT);

	setSolidness(df::SOFT);
	//set start location to middle of window
	moveToStart();
}

HealthPack::~HealthPack() {
	//send a view event with points to interested vew objects
	//add 10 points
	df::EventView ev("Health", 10, true);
	WM.onEvent(&ev);
}
int HealthPack::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	return 0;
}

void HealthPack::moveToStart() {
	df::Vector temp_pos;

	float world_x = WM.getBoundary().getHorizontal();
	float world_y = WM.getBoundary().getVertical();

	//x is off right side of window
	temp_pos.setX(world_x + rand() % (int)world_x + 3.0f);

	//y is in vertical range
	temp_pos.setY(rand() % (int)(world_y - 4) + 4.0f);

	WM.moveObject(this, temp_pos);
}

void HealthPack::hit(const df::EventCollision* p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "Saucer") ||
		(p_collision_event->getObject2()->getType() == "Saucer")) {
		return;
	}

	if ((p_collision_event->getObject1()->getType() == "Hero") ||
		(p_collision_event->getObject2()->getType() == "Hero")) {

		if (p_collision_event->getObject1()->getType() == "Hero") {
			Hero* hero = dynamic_cast <Hero*> (p_collision_event->getObject1());
			//increase hero health
			hero->health = hero->health + 10;
			
			WM.markForDelete(p_collision_event->getObject2());
			
		}

		if (p_collision_event->getObject2()->getType() == "Hero") {
			Hero* hero = dynamic_cast <Hero*> (p_collision_event->getObject2());
			hero->health = hero->health + 10;
			WM.markForDelete(p_collision_event->getObject1());
		}

		
		df::Sound* p_sound = RM.getSound("healthpickup");
		p_sound->play();

	}
}