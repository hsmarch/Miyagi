// System includes.
#include <stdlib.h>		// for rand()

// Engine includes.
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "left_arrow.h"
#include "Vector.h"
#include "Points.h"

left_arrow::left_arrow() {

	// Setleft "left_arrow" sprite.
	df::Sprite *p_temp_sprite = RM.getSprite("left_arrow");
	if (!p_temp_sprite)
		LM.writeLog("Saucer::Saucer(): Warning! Sprite '%s' not found", "left_arrow");
	else {
		setSprite(p_temp_sprite, true);
		setSpriteSlowdown(4);
	}
	//duh
	// Set object type.`
	setType("left_arrow");
	setSolidness(df::SPECTRAL);
	setPosition(df::Vector((WM.getBoundary().getHorizontal() / 2) + 4, 0));
	//setBox(df::Box(this->getPosition(), this->getSprite()->getWidth(), this->getSprite()->getHeight()));
	//down W/2+10
	// Set speed in horizontal direction.
	setVelocity(df::Vector(0, 0.125)); // 1 space down every 8 frames
}
left_arrow::~left_arrow() {
	// Send "view" event with points to interested ViewObjects.
	// Add 10 points.
	df::EventView ev(POINTS_STRING, -10, true);
	WM.onEvent(&ev);
}


// Handle event.
// Return 0 if ignored, else 1.
int left_arrow::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}


	return 0;
}

void left_arrow::out() {

	// If haven't moved off left edge, then nothing to do.
	if (getPosition().getY() < WM.getBoundary().getVertical() - 1)
		return;
	new left_arrow;

	WM.markForDelete(this);
}




