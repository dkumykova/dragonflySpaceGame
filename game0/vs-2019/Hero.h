#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Reticle.h"

class Hero : public df::Object {
private:
	void kbd(const df::EventKeyboard* p_key_event);
	void move(int dy);
	void step();
	int move_slowdown;
	int move_countdown; 
	int fire_slowdown;
	int fire_countdown;
	int nuke_count;
	void fire(df::Vector target);
	void mouse(const df::EventMouse *p_mouse_event);
	Reticle *p_reticle;
	void nuke();
	

public:
	Hero();
	int eventHandler(const df::Event* p_e);
	~Hero();
	int health;
	void handleHealth();

};

