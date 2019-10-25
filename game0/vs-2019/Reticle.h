#define RETICLE_CHAR '+'
#include "Object.h"


class Reticle : public df::Object {
public:
	Reticle();
	int draw(void);
	int eventHandler(const df::Event* p_e);
};
