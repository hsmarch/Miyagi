#include "Object.h"
#include "EventCollision.h"

class up_arrow : public df::Object {
private:
	void out();

public:
	up_arrow();
	~up_arrow();
	int eventHandler(const df::Event *p_e);
};