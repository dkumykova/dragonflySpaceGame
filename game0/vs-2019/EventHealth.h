#include "stdlib.h"
#include <string>
#include <Event.h>

const std::string HEALTH_EVENT = "health";

class EventHealth : public df::Event {
public:
	EventHealth();
};
