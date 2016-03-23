#include "Car.h"

// Returns whether chassi, engine and tyres are fully assembled
bool Car::assembled()
{
	return chassi.assembled();
}

// Returns car's maximum speed in cm per second
// ranging from 4000 (Monaco), 6000 (Melbourne) to 6700 (Monza)
unsigned short Car::speed(short circuit_speed, TrackCondition cond)
{
	// Influence of chass and tyres
	unsigned short total = 2*chassi.speed;
	total += 2*tyre->grip;

	// Influence of engine power is based on circuit speed (1-5) and weather
	if (cond == dry) total += (circuit_speed-1) * engine->power;
	else if (cond == damp) total += ((circuit_speed-1)/2) * engine->power;

	// Negative influence of fuel load
	total -= tankLevel/19000;

	// Total : 286-402
	total += 230 + circuit_speed*20;

	// Total : 4800-6700
	total *= 16;
	return total;
}

// Prepare car for GP weekend
void Car::get_ready_for_GP(bool newCar, bool newEngine)
{
	if (newCar) chassi.new_condition();
	if (newEngine) engine->new_condition();
}

// Pre-race setup and strategy
void Car::get_ready_for_race(unsigned int race_distance, Tyre *options[4], TrackCondition cond)
{
	stops = 0;

	// Select setup and fresh tyres based on initial track conditions
	setup = cond;
	if (cond == dry) tyre = options[SOFT];
	else if (cond == damp) tyre = options[INTERS];
	else if (cond == wet) tyre = options[WETS];
	else if (cond == flood) tyre = options[WETS];
        tyre->new_condition();

	// Plan pit stop strategy
	plannedStops = 1 + randNumber(0,2);
	tankLevel = race_distance/(plannedStops+1);
	tankLevel += 1000*randNumber(0,35) - 17000;
	for (short i=int_zero; i<plannedStops; i++)
		{ refuel[i]=(race_distance-tankLevel+7010)/plannedStops; }
}

// FOR DEBUGGING
void Car::display_strategy()
{
	cout << " PlannedStops:" << plannedStops;
	for (short i=0; i<plannedStops; i++) cout << "  " << refuel[i];
}

// Updates component wear based on distance traveled and track conditions.
// Wear reduced in slower wetter conditions.
void Car::update_condition(unsigned short distance, TrackCondition cond)
{
	chassi.update_condition(distance,cond);
	engine->update_condition(distance,cond);
}

// Probability of mechanical failure using probability calculated from part wear.
bool Car::part_failure(short probability, TrackCondition cond)
{
	short chance = 1180 + 2*probability;
	short dice = randNumber(0,1200);
	if (dice > chance) return true;
	else return false;
}

// Finds out if failure has occured based on component wear
// and returns failure type
short Car::any_failure(unsigned short distance, TrackCondition cond)
{
	update_condition(distance,cond);

	if (part_failure(chassi.drivetrain.condition_ok(), cond)) return DRIVETRAIN_FAIL;
	else if (part_failure(chassi.gearbox.condition_ok(), cond)) return GEARBOX_FAIL;
	else if (part_failure(chassi.suspension.condition_ok(), cond)) return SUSPENSION_FAIL;
	else if (part_failure(engine->condition_ok(), cond)) return ENGINE_FAIL;
	else if (part_failure(tyre->condition_ok(), cond)) return TYRE_FAIL;
	else return NO_FAIL;
}

// Update fuel and tyre status, and decide whether to pit
bool Car::next_lap(unsigned short lapLength, TrackCondition cond)
{
	// Update fuel level and tyre condition
	tankLevel -= int(lapLength);
	tyre->update_condition(lapLength,cond);

	// Decide whether to pit
	if (tankLevel < int(lapLength)) return true;

	// Unscheduled decision
	else if (setup != cond) {
		if ((cond == flood || cond == wet) && setup == dry) {
			unscheduled = true;
			return true;
		}
		else if (cond == dry && (setup == flood || setup == wet)) {
			unscheduled = true;
			return true;
		}
		else return false;
	}
	else return false;
}

// Display fuel, tyres and pit-stops made
void Car::display_status()
{
	cout << "F:";
	if (tankLevel < 100000) printSpaces(1);
	if (tankLevel < 10000) printSpaces(1);
	cout << tankLevel;
	tyre->display_tyre();
	//chassi.display_condition();

	// Display pit-stops completed
	if (stops > 0) cout << "  " << stops << " stops";
	//for (char i=0; i<stops; i++) cout <<" "<< refuel[i];
}

// Calculates and returns pit stop time in milliseconds.
short Car::pit_stop(Tyre *options[4], TrackCondition cond)
{
	stops++;
	setup = cond;

	// Change tyres
	if (cond == dry) tyre = options[SOFT];
	else if (cond == damp) tyre = options[INTERS];
	else if (cond == wet) tyre = options[WETS];
	else if (cond == flood) tyre = options[WETS];
        tyre->new_condition();
	if (unscheduled) {
		unsigned int remaining_distance = tankLevel;
		for (short a=(stops-1); a<plannedStops; a++) remaining_distance += refuel[a];
		if (stops > plannedStops) refuel[stops-1] = 100;
		else if (tankLevel > int(refuel[stops-1]/2)) {
			plannedStops++;
			for (short b=(stops-1); b<plannedStops; b++)
				{ refuel[b] = remaining_distance/(plannedStops-stops+1); }
		}
		else {
			for (short b=(stops-1); b<plannedStops; b++)
				{ refuel[b] = remaining_distance/(plannedStops-stops+1); }
			if (refuel[stops-1] > tankCapacity) {
				plannedStops++;
				for (short b=(stops-1); b<plannedStops; b++)
					{ refuel[b] = remaining_distance/(plannedStops-stops+1); }
			}
		}
		unscheduled = false;
	}
	// Scheduled refuel
	tankLevel += refuel[stops-1];
	if (tankLevel > tankCapacity) tankLevel = tankCapacity;
	return short(100*refuel[stops-1]/REFUEL_RATE);
}

