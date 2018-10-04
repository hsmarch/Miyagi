#include "Object.h"
#include "EventCollision.h"

class down_arrow : public df::Object {
private:
	void out();

public:
	down_arrow();
	~down_arrow();
	int eventHandler(const df::Event *p_e);
};