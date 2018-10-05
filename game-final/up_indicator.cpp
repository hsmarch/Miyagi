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
#include "Box.h"

// Game includes.
#include "GameOver.h"
#include "up_indicator.h"

void up_indicator::kbd(const df::EventKeyboard * p_keyboard_event)
{
	df::ObjectList all_objects = WM.getAllObjects();
	df::ObjectListIterator oli(&all_objects);
	df::ObjectList up_arrows;
	up_arrows.clear();
	for (oli.first(); !oli.isDone(); oli.next())
	{
		if (oli.currentObject()->getType() == "up_arrow") 
		{
			up_arrows.insert(oli.currentObject());
			LM.writeLog("Adding to moving arrows list");
			LM.writeLog("%p", oli.currentObject());
		}
	}

	switch (p_keyboard_event->getKey())
	{
	case df::Keyboard::W:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			LM.writeLog("UP PRESSED");
			bool hit = false;
			df::ObjectListIterator up_arrows_iterator(&up_arrows);
			for (up_arrows_iterator.first(); !up_arrows_iterator.isDone(); up_arrows_iterator.next()) {
				df::Box b = df::getWorldBox(this);
				df::Box b_temp = df::getWorldBox(up_arrows_iterator.currentObject());
				if (df::boxIntersectsBox(b, b_temp)) {
					LM.writeLog("Verticals good!");
					WM.markForDelete(up_arrows_iterator.currentObject());

					//add points 
					// Send "view" event with points to interested ViewObjects.
					float accuracy = 1.1 - abs(b.getCorner().getY() - b_temp.getCorner().getY());
					df::EventView ev(POINTS_STRING, 100 * accuracy, true);
					WM.onEvent(&ev);
					hit = true;
				}
			}
			if (!hit)
			{
				df::EventView ev(POINTS_STRING, -10 , true);
				WM.onEvent(&ev);
			}
		}
		break;

	case df::Keyboard::Q:        // quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			df::WorldManager &world_manager = df::WorldManager::getInstance();
			world_manager.markForDelete(this);
			new GameOver;
		}
		break;
	default:
		break;
	}
	return;
}

up_indicator::up_indicator()
{
	df::Sprite *p_temp_sprite;
	p_temp_sprite = RM.getSprite("up_arrow");

	if (!p_temp_sprite)
		LM.writeLog("up_indicator::up_indicator(): Warning! Sprite '%s' not found", "up_arrow");
	else {
		setSprite(p_temp_sprite, true);

		setSpriteSlowdown(3);  // 1/3 speed animation.
		setTransparency();	   // Transparent sprite.

	}

	// Player controls player, so register for input events.
	registerInterest(df::KEYBOARD_EVENT);

	// Set object type.
	setType("up_indicator");
	setAltitude(df::MAX_ALTITUDE);
	setSolidness(df::SPECTRAL);
	// Set starting location.
	df::Vector p(WM.getBoundary().getHorizontal() / 2 + 4, WM.getBoundary().getVertical() - 1);
	setPosition(p);
}

up_indicator::~up_indicator()
{
}

int up_indicator::eventHandler(const df::Event * p_e)
{
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	// If get here, have ignored this event.
	return 0;
}
