//
// Bullet.cpp
//

// Engine includes.
#include "EventOut.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "Bullet.h"
#include "Saucer.h"

Bullet::Bullet(df::Vector hero_pos) {

  // Link to "bullet" sprite.
  df::Sprite *p_temp_sprite = RM.getSprite("bullet");
  if (!p_temp_sprite)
    LM.writeLog("Bullet::Bullet(): Warning! Sprite '%s' not found", "bullet");
  else {
    setSprite(p_temp_sprite);
    setSpriteSlowdown(5);		
  }

  // Make the Bullets soft so can pass through player.
  setSolidness(df::SOFT);
  // Set other object properties.
  setType("Bullet");

  // Set starting location, based on player's position passed in.
  df::Vector p(hero_pos.getX()+3, hero_pos.getY());
  setPosition(p);
}

// Handle event.
// Return 0 if ignored, else 1.
int Bullet::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::OUT_EVENT) {
    out();
    return 1;
  }

  if (p_e->getType() == df::COLLISION_EVENT) {
    const df::EventCollision *p_collision_event = dynamic_cast <const df::EventCollision *> (p_e);
    hit(p_collision_event);
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}

// If Bullet moves outside world, mark self for deletion.
void Bullet::out() {
  WM.markForDelete(this);
}

// If Bullet hits Saucer, mark Saucer and Bullet for deletion.
void Bullet::hit(const df::EventCollision *p_collision_event) {
  if ((p_collision_event -> getObject1() -> getType() == "Saucer") || 
    (p_collision_event -> getObject2() -> getType() == "Saucer")) {
    WM.markForDelete(p_collision_event->getObject1());
    WM.markForDelete(p_collision_event->getObject2());
  }
}
