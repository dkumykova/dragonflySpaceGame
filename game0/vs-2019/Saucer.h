#include "Object.h"
#include "EventCollision.h"
class Saucer : public df::Object {
//int eventHandler(const df::Event *p_e);

public:
	Saucer();

	int eventHandler(const df::Event* p_e);
	void out();
	void moveToStart();
	void hit(const df::EventCollision* p_collision_event);
	~Saucer();

};

