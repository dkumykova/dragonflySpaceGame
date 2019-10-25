#include "Reticle.h"
#include "EventMouse.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventMouse.h"
#include "EventKeyboard.h"


Reticle::Reticle() {
	setType("Reticle");
	setSolidness(df::SPECTRAL);
	setAltitude(df::MAX_ALTITUDE); //put in foreground

	registerInterest(df::MSE_EVENT);

	int world_x = (int)WM.getBoundary().getHorizontal();
	int world_y = (int)WM.getBoundary().getVertical();
	df::Vector position(world_x / 2, world_y / 2);
	setPosition(position);
}

int Reticle::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event =
			dynamic_cast <const df::EventMouse*> (p_e);
		if (p_mouse_event->getMouseAction() == df::MOVED) {
			//change loc to new mouse pos
			setPosition(p_mouse_event->getMousePosition());
			return 1;
		}
	}
	return 0;
}

int Reticle::draw() {
	return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}