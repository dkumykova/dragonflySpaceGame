#include "stdlib.h"
#include <string>
#include <Event.h>

const std::string NUKE_EVENT = "nuke";

class EventNuke : public df::Event {
public:
	EventNuke();
};
