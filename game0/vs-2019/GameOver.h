#include "ViewObject.h"
#include "Event.h"

class GameOver : public df::ViewObject {
public:
	GameOver();
	int time_to_live;
	int eventHandler(const df::Event *p_e);
	void step();
	~GameOver();
	int draw();
};
