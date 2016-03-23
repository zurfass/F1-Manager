#include "Driver.h"

// Initialize attributes at object creation
void Driver::init(string a, short b, short c, short d, short e)
{
		name = a;
		age = b;
		speed = c;
		reliability = d;
		wetWeather = e;
		points = 0;
		wins = 0;
		poles = 0;
}

// Assign the driver's name and age
void Driver::set_values(string a,short b)
{
	name = a;
	age = b;
	speed = 5;
	reliability = 5;
	points = 0;
}

// Display driver name, attributes and team
void Driver::display_driver(short rank)
{
	display_rank(rank);
	display_name(MAX_CHARS);
	cout << " " << age << " " << speed << ",";
	cout << reliability << "," << wetWeather << "  ";
	team->display_name(MAX_CHARS);
	cout << endl;
}

// Display all race finishes this season
void Driver::display_results(short totalRaces)
{
	display_name(MAX_CHARS);
	for (short i=0; i<totalRaces; i++) {
		printSpaces(1);
		if (finish[i] == MAX_ENTRIES) cout << " R";
		else {
			if (finish[i] < 10) printSpaces(1);
			cout << finish[i];
		}
	}
	if (wins > 0) {
		if (wins == 1) cout << "   " << wins << " win";
		else if (wins >= 10) cout << "  " << wins << " wins";
		else cout << "   " << wins << " wins";
	}
}

// Display all grid positions this season
void Driver::display_grids(short totalRaces)
{
	display_name(MAX_CHARS);
	for (short i=0; i<totalRaces; i++) {
		printSpaces(1);
		if (grid[i] < 10) printSpaces(1);
		cout << grid[i];
	}
	if (poles > 0) {
		if (poles == 1) cout << "   " << poles << " pole";
		else if (poles >= 10) cout << "  " << poles << " poles";
		else cout << "   " << poles << " poles";
	}
}

// Displays qualifying result including fastest of three timed laps determining grid position
void Driver::display_qual(short i)
{
	display_rank(i+1);
	display_name(MAX_CHARS);
	team->display_name(MAX_CHARS);
	display_time(qLap);   printSpaces(3);
	display_time(lap[0]); printSpaces(1);
	display_time(lap[1]); printSpaces(1);
	display_time(lap[2]); cout << "\n";
}

// Display driver race information, aligning data for the table
void Driver::display_driver_position_and_status(short rank,short this_lap,int total_gap)
{
	// Print position, driver and team
	display_rank(rank);
	display_name(MAX_CHARS);
        team->display_name(MAX_CHARS);

	// If leading, print distance completed
	if (rank == 1) {
		if (distance < 100) printSpaces(1);
		if (distance < 1000) printSpaces(1);
		if (distance < 10000) printSpaces(1);
		if (distance < 100000) printSpaces(1);
		cout << distance << "m";
	}

	// Otherwise print time gap to leader
	else display_time(total_gap);

	// Print current lap time and fastest lap
	printSpaces(2);
	display_time(lap[this_lap]);	printSpaces(2);
	display_time(fastestLap);	printSpaces(2);

	// Print any other exceptional information
	team->car[teamCar]->display_status();
	if (ranOff) cout << "  RAN OFF!!!";
	if (spun) cout << "  SPUN!!!";
	if (pitting)
	{
		cout << "  IN PIT:";
		display_time(stop);
		cout << "s";
	}
	cout << endl;
}

// Current speed in m/s (race speed for non-leaders)
void Driver::current_speed(float time_inc, unsigned short lapNumber, unsigned short lapLength,
				short trackSpeed, TrackCondition c)
{
	// Calculate average speed this lap in cm/second where
	// maxCarSpeed{chassi,engine,tyres} = 4000-6700 cm/second
	current_speed(lapNumber,lapLength,trackSpeed,c);

	// Update distance traveled (using time not lap length)
	distance += int(time_inc*lapSpeed) - lapLength;
}

// Current speed in m/s (for qualifying and race leaders)
void Driver::current_speed(unsigned short lapNumber,unsigned short lapLength,short trackSpeed,TrackCondition c)
{
	// Find the car's maximum speed in cm/s
	unsigned short maxCarSpeed = team->car[teamCar]->speed(trackSpeed,c);

	// Driver influence ranges from 384 to 410
	unsigned short driverInfluence;
       	if (c == dry) driverInfluence = 380 + 2*speed;
	else if ((c == moist) || (c == damp))
		driverInfluence = 380 + speed + wetWeather;
	else if ((c == wet) || (c == flood))
		driverInfluence = 380 + 2*wetWeather;

	// Random influence
	driverInfluence += randNumber(1,6);
	driverInfluence += randNumber(1,6);

	// Percentage of maximum car speed - aiming for ~ 95% to 105%
	float fraction = float(driverInfluence)/400.0;

	// Average speed this lap in meters/second where
	// maxCarSpeed{chassi,engine,tyres} = 4000-6700 cm/second
	lapSpeed = float(maxCarSpeed) * fraction / 100.0;

	// Store lap time in hundredths of a second
	lap[lapNumber] = int(100*float(lapLength)/lapSpeed);
	fastest_lap(lapNumber);

	// Update distance traveled
	distance += lapLength;
}

// Checks if driver has collided with other driver
bool Driver::collision_update(short this_lap, TrackCondition current_conditions)
{
	if (timeGap < 100) {
		short chance = 1090 + reliability;
		if (this_lap == 1) chance -= 40;
		if (current_conditions == flood) chance += wetWeather*4 - 40;
		if (current_conditions == wet) chance += wetWeather*2 - 20;
		if (current_conditions == damp) chance += wetWeather - 10;
		if (current_conditions == moist) chance -= 2;
		short dice = randNumber(1,1100);
		if (dice > chance) return true;
		else return false;
	}
	else return false;
}

// Checks if driver spun and stalled
bool Driver::spin_update(short this_lap, TrackCondition current_conditions)
{
	short chance = 1090 + reliability;
	if (this_lap == 1) chance -= 20;
	if (current_conditions == flood) chance += wetWeather*4 - 40;
	if (current_conditions == wet) chance += wetWeather*2 - 20;
	if (current_conditions == damp) chance += wetWeather - 10;
	if (current_conditions == moist) chance -= 2;
	short dice = randNumber(1,1100);
	if (dice > chance) return true;
	else return false;
}

// Calculate probability of driver error and distance lost (in meters) if error occurs
void Driver::error_update(short this_lap, TrackCondition current_conditions)
{
	unsigned short chance = 970 + 3*reliability;
	if (this_lap == 1) chance -= 35;
	if (current_conditions == flood) chance += wetWeather*3 - 29;
	if (current_conditions == wet) chance += wetWeather*2 - 19;
	if (current_conditions == damp) chance += wetWeather - 9;
	if (current_conditions == moist) chance -= 2;
	unsigned short dice,dice2;
	dice = randNumber(1,1000);

	// If error has occurred, find type of error and distance lost
	short distance_lost;
	if (dice > chance)
	{
		dice2 = randNumber(1,100);

		// 60% chance of small off-track excursion
		if (dice2 < 60)
		{
			distance_lost = 900;
			ranOff = true;
			spun = false;
		}
		// 20% chance of major off-track excursion
		else if (dice2 >= 60)
		{
			distance_lost = 1800;
			ranOff = true;
			spun = false;
		}
		// 20% chance of spinning off
		else if (dice2 >= 80)
		{
			distance_lost = 4000;
			spun = true;
			ranOff = false;
		}
	}
	else
	{
		distance_lost = 0;
		ranOff = false;
		spun = false;
	}
	distance -= distance_lost;
}

// Prepare for grand prix weekend
// TO DO:  base decisions on team resources
void Driver::get_ready_for_GP()
{
	team->car[teamCar]->get_ready_for_GP(true,true);
}

// Pre-race setup and strategy
void Driver::get_ready_for_race(short gridPosition,short round,unsigned int raceDistance,
				Tyre *options[4],TrackCondition cond)
{
	// Store grid position for season-end summary
	grid[round-1] = gridPosition+1;
	lapped = false;
	ranOff = false;
	spun = false;
	pitting = false;
	distance = -20*gridPosition;
	team->car[teamCar]->get_ready_for_race(raceDistance,options,cond);
}

// Calculate driver's fastest lap so far
/*unsigned int Driver::fastest_lap(unsigned short totalLaps) {
	unsigned int runningMin = lap[0];
	for (short i=1; i<totalLaps; i++) {
		runningMin = min(lap[i], runningMin);
	}
	return runningMin;
}*/

// Calculate driver's fastest lap so far
void Driver::fastest_lap(unsigned short thisLap)
{
	// First check if this is first lap
	if (thisLap == 0) fastestLap = lap[0];
	else fastestLap = min(fastestLap,lap[thisLap]);
}

double Driver::total_time(short laps) {
	double total;
	for (short i=0; i<laps; i++) {total += lap[i];}
	return total;
}

