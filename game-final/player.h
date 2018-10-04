//
// player.h
//

#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"
#include "Reticle.h"

class player : public df::Object {

 private:
  void kbd(const df::EventKeyboard *p_keyboard_event);
  
 public:
  player();
  ~player();
  int eventHandler(const df::Event *p_e);
};
