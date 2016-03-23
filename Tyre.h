#include "Suspension.h"

struct Tyre: public Component
{
	// Attributes (out of 10)
	short grip, durability, upToTemperature;
	TyreType type;

	// Race temperature (100 C = optimum)
	unsigned short temperature;

	// Member functions
	void new_condition();
	void update_grip(TrackCondition);
	void update_temperature(TrackCondition);
	void update_condition(unsigned short,TrackCondition);
	void display_tyre();

	// Constructors
	Tyre(short att[3], TyreType tt)
	{
		// Attributes
		efficiency = 10;
		reliability = 10;
		grip = att[0];
		durability = att[1];
		upToTemperature = att[2];

		// Type
		type = tt;
	}
};

// Brand new tyre
void Tyre::new_condition()
{
	Component::new_condition();
	temperature = 50;
}

// Updates tyre grip level (ONCE PER LAP)
void Tyre::update_grip(TrackCondition cond)
{
	// First take temperature into account
	if (temperature <= 101) grip = temperature / 10;
	else if (temperature <= 108) grip = 9;
	else if (temperature <= 114) grip = 8;
	else if (temperature <= 120) grip = 7;
	else if (temperature <= 125) grip = 6;
	else if (temperature <= 130) grip = 5;
	else if (temperature <= 135) grip = 4;
	else grip = 3;

	// Then take condition into account
	if (_condition < 70) grip--;
	if (_condition < 50) grip--;
	if (_condition < 35) grip--;
	if (_condition < 23) grip--;
	if (_condition < 13) grip--;
	if (_condition < 6) grip--;
	if (_condition < 0) grip--;

	// Check track conditions
	if (cond == damp) grip -= 1;
	else if (cond == wet) grip -= 2;
	else if (cond == flood) grip -= 3;

	// Check compound vs conditions
	if (type == inter) {
		if (cond == dry) grip -= 1;
		if (cond == wet) grip -= 1;
		if (cond == flood) grip -= 2;
	}
}

// Updates tyre temperature (ONCE PER LAP)
void Tyre::update_temperature(TrackCondition cond)
{
	// Assuming 100 C is optimum temperature
	if (cond == dry) {
		if ((type == soft) || (type == hard)) temperature += (101-temperature)/2;
		else if (type == inter) temperature += (135-temperature)/2;
		else temperature += (160-temperature)/2;
	}
	else if (cond == damp) {
		if ((type == soft) || (type == hard)) temperature += (101-temperature)/5;
		else if (type == inter) temperature += (101-temperature)/2;
		else temperature += (135-temperature)/2;
	}
	else {
		if ((type == soft) || (type == hard)) temperature += (101-temperature)/10;
		else if (type == inter) temperature += (101-temperature)/5;
		else temperature += (101-temperature)/2;
	}
}

// Updates tyre condition (ONCE PER LAP)
void Tyre::update_condition(unsigned short distance, TrackCondition cond)
{
	// Temperature depends on compound and track conditions
	update_temperature(cond);

	// Wear rate depends on track conditions, tyre type and compound
	if (cond == dry) {
		if (type == soft) _condition -= 3;
		else if (type == hard) _condition -= 2;
		else _condition -= 4;
	}
	else if (cond == damp) {
		if (type == soft) _condition -= 3;
		else if (type == hard) _condition -= 2;
		else if (type == inter) _condition -= 2;
		else _condition -= 3;
	}
	else _condition -= 1;

	// Grip depends on new temperature, wear, compound and track conditions
	update_grip(cond);
}

// Display tyre compound and condition
void Tyre::display_tyre()
{
	cout << "  Tyr: ";

	// First the type/compound and condition
        if (type == soft) cout << "S";
	else if (type == hard) cout << "H";
        else if (type == inter) cout << "I";
        else if (type == wets) cout << "W";
	if (_condition < 100) printSpaces(1);
	if (_condition < 10) printSpaces(1);
	cout << _condition << " ";

	// Temperature in C
	if (temperature < 100) printSpaces(1);
	cout << temperature << "^C";

	// Grip (out of 10)
	cout << " Grip:";
	if ((grip < 10) && (grip >= 0)) cout << " " << grip;
	else cout << grip;
}

