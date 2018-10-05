#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"
#include "Reticle.h"

class up_indicator : public df::Object {

private:
	void kbd(const df::EventKeyboard *p_keyboard_event);

public:
	up_indicator();
	~up_indicator();
	int eventHandler(const df::Event *p_e);
};