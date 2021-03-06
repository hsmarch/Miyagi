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
#include "EventView.h"
#include "Points.h"
#include <math.h>

// Game includes.
#include "GameOver.h"
#include "player.h"

player::player() {
	//reset
	// Link to "ship" sprite.
	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("player");

	if (!p_temp_sprite)
		LM.writeLog("player::player(): Warning! Sprite '%s' not found", "ship");
	else {
		setSprite(p_temp_sprite, true);

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
	//
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

// Take appropriate action according to key pressed.
void player::kbd(const df::EventKeyboard *p_keyboard_event) {
	//setBox(df::Box(this->getPosition(), this->getSprite()->getWidth(), this->getSprite()->getHeight()));
	df::ObjectList all_objects = WM.getAllObjects();
	df::ObjectListIterator oli(&all_objects);
	df::ObjectList moving_arrows;
	moving_arrows.clear();
	for (oli.first(); !oli.isDone(); oli.next()) {
		if (oli.currentObject()->getType() == "up_arrow" || oli.currentObject()->getType() == "down_arrow" || oli.currentObject()->getType() == "left_arrow" || oli.currentObject()->getType() == "right_arrow") {
			moving_arrows.insert(oli.currentObject());
			LM.writeLog("Adding to moving arrows list");
			LM.writeLog("%p", oli.currentObject());
		}
	}

	switch (p_keyboard_event->getKey()) {
		//check intersect boxes with all objs
	case df::Keyboard::W:       // up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			LM.writeLog("UP PRESSED");
			df::ObjectListIterator moving_arrows_iterator(&moving_arrows);
			for (moving_arrows_iterator.first(); !moving_arrows_iterator.isDone(); moving_arrows_iterator.next()) {
				if (moving_arrows_iterator.currentObject()->getType() == "up_arrow") {
					//moving_arrows_iterator.currentObject()->setBox(df::Box(moving_arrows_iterator.currentObject()->getPosition(), moving_arrows_iterator.currentObject()->getSprite()->getWidth(), moving_arrows_iterator.currentObject()->getSprite()->getHeight()));
					LM.writeLog("Checking Collision");
					if (moving_arrows_iterator.currentObject()->getPosition().getY() + 1 >= this->getPosition().getY()) {
						LM.writeLog("Verticals good!");
						WM.markForDelete(moving_arrows_iterator.currentObject());
						//add points 
						// Send "view" event with points to interested ViewObjects.
						int accuracy = 10 - abs(this->getPosition().getY() - moving_arrows_iterator.currentObject()->getPosition().getY());
						df::EventView ev(POINTS_STRING, 10 * accuracy, true);
						WM.onEvent(&ev);
					}
				}
			}
			break;

		}
	case df::Keyboard::S:       // down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			LM.writeLog("DOWN PRESSED");
			df::ObjectListIterator moving_arrows_iterator(&moving_arrows);
			for (moving_arrows_iterator.first(); !moving_arrows_iterator.isDone(); moving_arrows_iterator.next()) {
				if (moving_arrows_iterator.currentObject()->getType() == "down_arrow") {
					//moving_arrows_iterator.currentObject()->setBox(df::Box(moving_arrows_iterator.currentObject()->getPosition(), moving_arrows_iterator.currentObject()->getSprite()->getWidth(), moving_arrows_iterator.currentObject()->getSprite()->getHeight()));
					LM.writeLog("Checking Collision");
					if (moving_arrows_iterator.currentObject()->getPosition().getY() + 1 >= this->getPosition().getY()) {
						LM.writeLog("Verticals good!");
						WM.markForDelete(moving_arrows_iterator.currentObject());
						//add points 
						// Send "view" event with points to interested ViewObjects.
						int accuracy = 10 - abs(this->getPosition().getY() - moving_arrows_iterator.currentObject()->getPosition().getY());
						df::EventView ev(POINTS_STRING, 10 * accuracy, true);
						WM.onEvent(&ev);
					}
				}
			}
			break;

		}
	case df::Keyboard::A:       // left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			LM.writeLog("LEFT PRESSED");
			df::ObjectListIterator moving_arrows_iterator(&moving_arrows);
			for (moving_arrows_iterator.first(); !moving_arrows_iterator.isDone(); moving_arrows_iterator.next()) {
				if (moving_arrows_iterator.currentObject()->getType() == "left_arrow") {
					//moving_arrows_iterator.currentObject()->setBox(df::Box(moving_arrows_iterator.currentObject()->getPosition(), moving_arrows_iterator.currentObject()->getSprite()->getWidth(), moving_arrows_iterator.currentObject()->getSprite()->getHeight()));
					LM.writeLog("Checking Collision");
					if (moving_arrows_iterator.currentObject()->getPosition().getY() + 1 >= this->getPosition().getY()) {
						LM.writeLog("Verticals good!");
						WM.markForDelete(moving_arrows_iterator.currentObject());
						//add points 
						// Send "view" event with points to interested ViewObjects.
						int accuracy = 10 - abs(this->getPosition().getY() - moving_arrows_iterator.currentObject()->getPosition().getY());
						df::EventView ev(POINTS_STRING, 10 * accuracy, true);
						WM.onEvent(&ev);
					}
				}
			}
			break;

		}
	case df::Keyboard::D:       // right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
			LM.writeLog("RIGHT PRESSED");
			df::ObjectListIterator moving_arrows_iterator(&moving_arrows);
			for (moving_arrows_iterator.first(); !moving_arrows_iterator.isDone(); moving_arrows_iterator.next()) {
				if (moving_arrows_iterator.currentObject()->getType() == "right_arrow") {
					//moving_arrows_iterator.currentObject()->setBox(df::Box(moving_arrows_iterator.currentObject()->getPosition(), moving_arrows_iterator.currentObject()->getSprite()->getWidth(), moving_arrows_iterator.currentObject()->getSprite()->getHeight()));
					LM.writeLog("Checking Collision");
					if (moving_arrows_iterator.currentObject()->getPosition().getY() + 1 >= this->getPosition().getY()) {
						LM.writeLog("Verticals good!");
						WM.markForDelete(moving_arrows_iterator.currentObject());
						//add points 
						// Send "view" event with points to interested ViewObjects.
						int accuracy = 10 - abs(this->getPosition().getY() - moving_arrows_iterator.currentObject()->getPosition().getY());
						df::EventView ev(POINTS_STRING, 10 * accuracy, true);
						WM.onEvent(&ev);
					}
				}
			}
			break;

		}
	case df::Keyboard::Q:        // quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			df::WorldManager &world_manager = df::WorldManager::getInstance();
			world_manager.markForDelete(this);
			new GameOver;
		}
		break;
	};

	return;
}




