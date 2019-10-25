#include "GameOver.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "GameStart.h"

GameOver::GameOver() {
	if (setSprite("gameover") == 0) {
		time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
	}
	else {
		time_to_live = 0;
	}

	registerInterest(df::STEP_EVENT);

	setLocation(df::CENTER_CENTER);

	df::Sound* p_sound = RM.getSound("gameOver");
	p_sound->play();

}

int GameOver::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}

void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0) {
		WM.markForDelete(this);
	}
}

GameOver::~GameOver() {
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) {
		df::Object* p_o = i.currentObject();
		if (p_o->getType() == "Saucer" || p_o->getType() == "ViewObject") {
			WM.markForDelete(p_o);
		}
		if (p_o->getType() == "GameStart") {
			p_o->setActive(true);
			//pause game music and play menu music again
			dynamic_cast <GameStart*> (p_o)->game_music->pause();
			dynamic_cast <GameStart*> (p_o)->playMusic(dynamic_cast <GameStart *> (p_o)->start_music); 
		}
	}
	//GM.setGameOver();
}

int GameOver::draw() {
	return df::Object::draw();
}