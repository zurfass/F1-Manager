#include "Engine.h"

struct GearBox: public Component
{
	// Member functions

	// Constructors
	GearBox(short att[2]) {
		setAttributes(att);
	}
};

