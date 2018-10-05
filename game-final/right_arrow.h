#include "Object.h"
#include "EventCollision.h"

class right_arrow : public df::Object {
private:
	void out();

public:
	right_arrow();
	~right_arrow();
	int eventHandler(const df::Event *p_e);
};