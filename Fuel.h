#include "Component.h"

struct Fuel: public Component
{
	unsigned short mass;
	Fuel() {
		setAttributes(10,10);
	}
};

