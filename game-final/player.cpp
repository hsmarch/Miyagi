//
// player.cpp
//

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "utility.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"

// Game includes.
#include "GameOver.h"
#include "player.h"

player::player() {

	// Link to "ship" sprite.
	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("player");
	if (!p_temp_sprite)
		LM.writeLog("player::player(): Warning! Sprite '%s' not found", "ship");
	else {
		setSprite(p_temp_sprite);
		setSpriteSlowdown(3);  // 1/3 speed animation.
		setTransparency();	   // Transparent sprite.
	}

	// Player controls player, so register for input events.
	registerInterest(df::KEYBOARD_EVENT);

	// Set object type.
	setType("player");
	setAltitude(df::MAX_ALTITUDE);
	setSolidness(df::SPECTRAL);
	// Set starting location.
	df::Vector p(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() - 1);
	setPosition(p);
}

player::~player() {

}

// Handle event.
// Return 0 if ignored, else 1.
int player::eventHandler(const df::Event *p_e) {

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	// If get here, have ignored this event.
	return 0;
}

/**void player::wtf() {
	df::ObjectList moving_arrows;
	df::ObjectListIterator oli(&WM.getAllObjects());
	for (oli.first(); !oli.isDone(); oli.next()) {
		if (oli.currentObject()->getType() == "up_arrow") {
			moving_arrows.insert(oli.currentObject());
		}
	}
	df::ObjectListIterator moving_arrows_iterator(&moving_arrows);
	for (moving_arrows_iterator.first(); moving_arrows_iterator.isDone(); moving_arrows_iterator.next())
	{
		if (boxIntersectsBox(this->getBox(), oli.currentObject()->getBox())) {
			WM.markForDelete(oli.currentObject());
		}
		oli.next();
	}
}
**/

// Take appropriate action according to key pressed.
void player::kbd(const df::EventKeyboard *p_keyboard_event) {
	switch (p_keyboard_event->getKey()) {
		//check intersect boxes with all objs
	case df::Keyboard::W:       // up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			LM.writeLog("UP PRESSED");
			break;
		}
	case df::Keyboard::S:       // down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			LM.writeLog("DOWN PRESSED");
		break;
	case df::Keyboard::A:       // left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			LM.writeLog("LEFT PRESSED");
		break;
	case df::Keyboard::D:       // left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			LM.writeLog("RIGHT PRESSED");
		break;
	case df::Keyboard::Q:        // quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			df::WorldManager &world_manager = df::WorldManager::getInstance();
			world_manager.markForDelete(this);
		}
		break;
	};

	return;
}




