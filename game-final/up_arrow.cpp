//
// Saucer.cpp
//
 
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
#include "up_arrow.h"
#include "Vector.h"


up_arrow::up_arrow() {

  // Setup "up_arrow" sprite.
  df::Sprite *p_temp_sprite = RM.getSprite("up_arrow");
  if (!p_temp_sprite)
    LM.writeLog("Saucer::Saucer(): Warning! Sprite '%s' not found", "up_arrow");
  else {
    setSprite(p_temp_sprite, true);
    setSpriteSlowdown(4);
  }

  // Set object type.
  setType("up_arrow");
  setSolidness(df::SPECTRAL);
  setPosition(df::Vector((WM.getBoundary().getHorizontal() / 2)+4,0));
  //down W/2+10
  // Set speed in horizontal direction.
  setVelocity(df::Vector(0,0.125)); // 1 space down every 8 frames
}
up_arrow::~up_arrow() {

  // Send "view" event with points to interested ViewObjects.
  // Add 10 points.
  df::EventView ev(POINTS_STRING, -10, true);
  WM.onEvent(&ev);
}


// Handle event.
// Return 0 if ignored, else 1.
int up_arrow::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

  
  return 0;
}

void up_arrow::out() {

	// If haven't moved off left edge, then nothing to do.
	if (getPosition().getY() < WM.getBoundary().getVertical()-1)
		return;
	new up_arrow;

	WM.markForDelete(this);
}
 



