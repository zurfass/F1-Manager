#include "Component.h"

struct Bodywork: public Component
{
	// Attributes (out of 10)
	short downforce, drag;

	// Member functions
	void init(short att[4]);
	void update_condition(short accident_scale);

	// Constructors
	Bodywork(short att[4]) {
		init(att);
	}
	Bodywork(short att[2], short _down, short _drag)
	{
		short all_att[] = {att[0],att[1],_down,_drag};
		init(all_att);
	}
};

// Initialize member values when object is created
void Bodywork::init(short att[4])
{
	short component_att[] = {att[0],att[1]};
	setAttributes(component_att);
	downforce = att[2];
	drag = att[3];
}

// Updates bodywork wear based on scale of accident (1-5)
void Bodywork::update_condition(short accident_scale)
{
	_condition -= 10*accident_scale;
}

