
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
#include "Points.h"
#include "down_arrow.h"
#include "Vector.h"

void down_arrow::out()
{
	// If haven't moved off left edge, then nothing to do.
	if (getPosition().getY() < WM.getBoundary().getVertical() - 1)
		return;
	new down_arrow;

	WM.markForDelete(this);
}

down_arrow::down_arrow()
{
	// Setup "up_arrow" sprite.
	df::Sprite *p_temp_sprite = RM.getSprite("down");
	if (!p_temp_sprite)
		LM.writeLog("down_arrow::down_arrow(): Warning! Sprite '%s' not found", "down");
	else {
		setSprite(p_temp_sprite, true);
		setSpriteSlowdown(4);
	}

	// Set object type.
	setType("down_arrow");
	setSolidness(df::SPECTRAL);
	setPosition(df::Vector(WM.getBoundary().getHorizontal() / 2 + 10, 0));
	// Set speed in horizontal direction.
	setVelocity(df::Vector(0, 0.125)); // 1 space down every 8 frames
}

down_arrow::~down_arrow()
{
}

int down_arrow::eventHandler(const df::Event * p_e)
{
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}


	return 0;
}
