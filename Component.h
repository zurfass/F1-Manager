#pragma once

#include "defines.cpp"

class Component
{
    protected:
	// Condition (out of 100)
	short _condition;

    public:
	// Part name or number
	string name;

	// Assembled into the chassi
	bool installed;

	// Attributes (out of 10)
	short efficiency, reliability;

	// Accumulated wear and tear (~1 per dry mile)
	unsigned short wear;

	// Member functions
	void setAttributes(short[2]);
	void new_condition();
	void update_condition(unsigned short,TrackCondition);
	short condition_ok();
	void display_condition();

	// Constructors
	Component()
	{
		new_condition();
	}
};

// Initialize attributes
void Component::setAttributes(short att[2])
{
	efficiency = att[0];
	reliability = att[1];
}

// New component
void Component::new_condition() {
	_condition = 100;
	wear = 0;
}

// Updates component wear based on mileage and reliability
void Component::update_condition(unsigned short distance,TrackCondition cond)
{
	// Convert distance traveled from m to miles
	if (cond == dry) wear += metersToMiles(distance);
	else wear += 1;
	_condition = 100 - wear/10;
}

// Returns probability (out of 10) of component NOT failing
short Component::condition_ok()
{
	if (_condition > 70) return 10;
	else if (_condition > 60) return (reliability+1);
	else if (_condition > 50) return reliability;
	else if (_condition > 40) return (reliability-1);
	else if (_condition > 30) return (reliability-2);
	else if (_condition > 20) return (reliability-3);
	else if (_condition > 13) return (reliability-4);
	else if (_condition > 7) return (reliability-5);
	else if (_condition > 3) return (reliability-6);
	else if (_condition > 0) return (reliability-7);
	else return -200;
}

// Display condition aligned
void Component::display_condition()
{
	if (_condition < 100) printSpaces(1);
	if (_condition < 10) printSpaces(1);
	cout << _condition;
}

