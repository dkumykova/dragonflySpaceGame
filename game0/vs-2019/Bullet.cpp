#include "Bullet.h"
#include "WorldManager.h"
#include "Saucer.h"
#include "EventOut.h"

Bullet::Bullet(df::Vector hero_position) {
	//link to sprite
	setSprite("bullet");

	setType("Bullet");
	df::Vector p(hero_position.getX() + 3, hero_position.getY());
	setPosition(p);
	//make bullets soft so can pass through Hero
	setSolidness(df::SOFT);

	//bullets move 1 space each game loop
	//direction set when hero fires
	setSpeed(1);
}

int Bullet::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision *> (p_e);
		hit(p_collision_event);
		return 1;
	}

	
	return 0;
}

void Bullet::out() {
	WM.markForDelete(this);
}

//if bullet hits saucer, mark both for deletion
void Bullet::hit(const df::EventCollision *p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "Saucer") ||
		(p_collision_event->getObject2()->getType() == "Saucer")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}
}