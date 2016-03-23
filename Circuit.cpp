#include "Circuit.h"

// Initialize attributes at object creation
void Circuit::init(string a,short b,unsigned short c,short d,short e,short f)
{
	name = a;
	totalLaps = b;
	lapLength = c;
	countryID = d;
	speed = e;
	overtaking = f;
}

// Prints extra spaces after the name to maintain alignment
void Circuit::display_spaces(short maxSpaces)
{
	short a = maxSpaces-name.length();
	printSpaces(a);
}

// Prints name in specified number of spaces
void Circuit::display_name(short maxSpaces)
{
	if (name.length() > maxSpaces) cout << name.substr(int_zero,maxSpaces);
	else {
		cout << name;
		display_spaces(maxSpaces);
	}
}

// Return total race distance in meters
unsigned int Circuit::total_distance()
{
	return (totalLaps*lapLength);
}

// Summarize circuit information
void Circuit::display_info(short round)
{
	cout << "ROUND " << round << ": " << name;
	cout << ", " << countryID << endl;
	cout << "Lap length: " << lapLength << "  Total distance: ";
	cout << total_distance() << endl;
	cout << "Speed: " << speed << "  Overtaking: " << overtaking << endl;
}

// Display weather and track conditions
void Circuit::display_status()
{
	cout << "Current weather: ";
	if (weather == sunny) cout << "Sunny";
	else if (weather == cloudy) cout << "Overcast";
	else if (weather == drizzle) cout << "Light rain";
	else if (weather == rain) cout << "Rain";
	else if (weather == pouring) cout << "Heavy rain";
	cout << endl << "Track conditions: ";
	if (cond == dry) cout << "Dry ";
	if (cond == damp) cout << "Damp";
	if (cond == wet) cout << "Wet ";
	if (cond == flood) cout << "Very wet";
	cout << "  Grip: " << grip;
}

// Probability of precipitation at any given time
short Circuit::track_weather(short climate)
{
	short dice = randNumber(0,100);

	// Weather is getting brighter
	if (dice >= 90) climate++;
	if (dice >= 97) climate++;

	// Weather is getting darker
	if (dice < 10) climate--;
	if (dice < 3) climate--;
	if (climate < 0) climate = 0;
	if (climate > (WEATHER_RANGE-1)) climate = WEATHER_RANGE-1;
	switch(climate)
	{
	case 0:
	case 1:
		weather = pouring; break;
	case 2:
	case 3:
		weather = rain; break;
	case 4:
	case 5:
		weather = drizzle; break;
	case 6:
	case 7:
		weather = cloudy; break;
	default:
		weather = sunny;
	}
	return climate;
}

// Determine track conditions based on weather and activity
void Circuit::track_conditions(short activity)
{
	grip = activity;
	if (weather == sunny) cond = dry;
	if (weather == cloudy) cond = dry;
	if (weather == drizzle) cond = damp;
	if (weather == rain) cond = wet;
	if (weather == pouring) cond = flood;
}

// Return whether driver overtakes, given gap in meters
bool Circuit::overtake(int gap)
{
	bool o_take = false;
	if (overtaking == 1) {
		if (gap < -125) o_take = true;
	}
	else if (overtaking == 2) {
		if (gap < -100) o_take = true;
	}
	else if (overtaking == 3) {
		if (gap < -75) o_take = true;
	}
	else if (overtaking == 4) {
		if (gap < -50) o_take = true;
	}
	else {
		if (gap < -25) o_take = true;
	}
	return o_take;
}

