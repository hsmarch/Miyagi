#include "Object.h"
#include "EventCollision.h"


class left_arrow : public df::Object {
private:
	void out();

public:
	left_arrow();
	~left_arrow();
	int eventHandler(const df::Event *p_e);
};