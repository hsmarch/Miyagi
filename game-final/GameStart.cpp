//
// GameStart.cpp
//

// Engine includes.
#include "Color.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "GameStart.h"
#include "player.h"
#include "Music.h"
#include "Points.h"
#include "up_arrow.h"
#include "down_arrow.h"
#include "up_indicator.h"

GameStart::GameStart() {
	setType("GameStart");

	// Link to "message" sprite.
	df::Sprite *p_temp_sprite = RM.getSprite("gamestart");
	if (!p_temp_sprite)
		LM.writeLog("GameStart::GameStart(): Warning! Sprite 'gamestart' not found");
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(15);
	}

	// Put in center of screen.
	setLocation(df::CENTER_CENTER);

	// Register for "keyboard" event.
	registerInterest(df::KEYBOARD_EVENT);

	// Play start music.
	p_music = RM.getMusic("start music");
	playMusic();
}

// Play start music.
void GameStart::playMusic() {
	p_music->play();
}

// Handle event.
// Return 0 if ignored, else 1.
int GameStart::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard *p_keyboard_event = (df::EventKeyboard *) p_e;
		switch (p_keyboard_event->getKey()) {
		case df::Keyboard::P: 			// play
			start();
			break;
		case df::Keyboard::Q:			// quit
			GM.setGameOver();
			break;
		default:
			break;
		}
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

void GameStart::start() {
	// Create player.
	new up_indicator;
	// Setup heads-up display.
	new Points;		                     // Points display.
	new up_arrow;
	new down_arrow;
	// Pause start music.
	p_music->pause();
	// When game starts, become inactive.
	setActive(false);
}
//start
// Override default draw so as not to display "value".
void GameStart::draw() {
	df::Object::draw();
}
