#include "Object.h"
#include "EventCollision.h"

class HealthPack : public df::Object {

public:
	HealthPack();

	int eventHandler(const df::Event* p_e);
	void moveToStart();
	void hit(const df::EventCollision* p_collision_event);
	~HealthPack();

};

