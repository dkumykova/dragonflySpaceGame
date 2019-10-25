#include "ViewObject.h"
#include "Music.h"

class GameStart : public df::ViewObject {
private:
	void start();
	
	
public:
	GameStart();
	int eventHandler(const df::Event *p_e);
	int draw();
	void playMusic(df::Music *song);
	df::Music* start_music;
	df::Music* game_music;
};