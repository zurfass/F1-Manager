#include "Season.h"
#include <valarray>

Driver Season::create_driver()
{
    	string s;
    	char c = 'y';
    	short att[4];
	cout << "Name: ";
	cin >> s;
	cout << "Age: ";
	cin >> att[0];
	cout << s << " aged " << att[0] << ". Speed (1-10): ";
	cin >> att[1];
	cout << " Reliability (0-10): ";
	cin >> att[2];
	cout << " Wet Weather (0-10): ";
	cin >> att[3];
	cout << "Which team? ";
	cin >> att[4];
	Driver driver(s,att[0],att[1],att[2],att[3],att[4]);
    	return driver;
}

// New team is created from data entered by user
Constructor* Season::create_constructor()
{
	string name;
	short att[2], en;
	cout << "Team name: ";
	cin >> name;
	cout << "Car speed: ";
	cin >> att[0];
	cout << "Car reliability: ";
	cin >> att[1];
	cout << "Engine: ";
	cin >> en;
	Constructor *team = new Constructor(name, att, engineSupplier[en], tyreSupplier[int_zero]);
	return team;
}

// Manage season data (engines, teams and drivers)
void Season::edit_season()
{
    	char c,c2,change,max;
	char newfile[20];
	short s,d;

	cout << "~~~~~~ EDIT SEASON ~~~~~~" << endl;
	cout << "1. New season" << endl;
	cout << "2. New drivers" << endl;
	cout << "3. Edit one driver" << endl;
	cout << "4. Add drivers" << endl;
	cout << "5. Remove drivers" << endl;
	cout << "6. Edit one team" << endl;
	cout << "7. Add teams" << endl;
	cout << "8. Remove teams" << endl;
	cout << "9. View season" << endl;
	cout << "Choose an option (1-9): ";
	cin >> c;
	s = cha2sho(c);
	while ((s >= 1) && (s <= 9))
	{
		c = 0;
		switch (s) {
		case 1:
			cout << "Filename: ";
			cin >> newfile;
			cout << "Year: ";
			cin >> year;
			while ((c < 50) || (c > 58))
			{
				cout << "Total entries: ";
				cin >> c;
			}
			change = c - 48;
			totalEntries = change;
			save_season(newfile);
			break;
		case 2:
			cout << "New drivers:" << endl;
			for (c=0 ; c<totalEntries; c++)
			{
				entry[c] = create_driver();
			}
			break;
		case 3:
			d = totalEntries + 1;
			while ((d < 0) || (d > totalEntries))
			{
				cout << "Which driver to edit? ";
				cin >> d;
			}
			entry[d] = create_driver();
			break;
		case 4:
			cout << "How many? ";
			cin >> c;
			while ((c < 48) || (c > 57)) {cin >> c;}
			max = totalEntries;
			totalEntries = totalEntries + c - 48;
			for (c=max; c<totalEntries; c++)
			{
				entry[c] = create_driver();
			}
			break;
		case 5:
			cout << "How many? ";
			cin >> c;
			while ((c < 48) || (c > 57)) {cin >> c;}
			totalEntries = totalEntries - c + 48;
			break;
		case 6:
			d = totalTeams + 1;
			while ((d < 0) || (d > totalTeams))
			{
				cout << "Which team to edit? ";
				cin >> c2;
				d = cha2sho(c2);
			}
			team[d] = create_constructor();
			break;
		case 7:
			cout << "How many? ";
			cin >> c;
			while ((c < 48) || (c > 57)) {cin >> c;}
			max = totalTeams;
			totalTeams = totalTeams + c - 48;
			for (c=max; c<totalTeams; c++)
				team[c] = create_constructor();
			break;
		case 8:
			cout << "How many? ";
			cin >> c;
			while ((c < 48) || (c > 57)) {cin >> c;}
			totalTeams = totalTeams - c + 48;
			break;
		case 9:
			display_season();
			break;
		default:
			;
		}
		cout << "Choose an option (1-9): ";
		cin >> c;
		s = cha2sho(c);
	}
}

// Loads engine suppliers, teams and drivers from data file
void Season::load_season(char file_name[])
{
	// Team constructor parameters
	string name;
	short att[4], engineID;

	// Load from specified data file
	ifstream myfile (file_name);
	cout << "Loading" << file_name << endl;

	// Load year
	myfile >> year;

	// Load engine suppliers
	myfile >> totalEngines;
	for (short i=int_zero; i<totalEngines; i++)
	{
		myfile >> name;
		myfile >> att[int_zero]; // Efficiency
		myfile >> att[1];	// Reliability
		myfile >> att[2];	// Power
		myfile >> att[3];	// Fuel efficiency
		engineSupplier[i] = new EngineSupplier(name, att);
	}
	// Load teams
	myfile >> totalTeams;
	for (short i=int_zero; i<totalTeams; i++)
	{
		myfile >> name;
		myfile >> att[int_zero];
		myfile >> att[1];
		short c_att[] = {att[int_zero],att[1]};
		myfile >> engineID;
		team[i] = new Constructor(name, c_att, engineSupplier[engineID], tyreSupplier[int_zero]);
	}
	// Load drivers
	myfile >> totalEntries;
    	for (short i=int_zero; i<totalEntries; i++)
    	{
		myfile >> entry[i].name;
		myfile >> entry[i].age;
		myfile >> entry[i].speed;
		myfile >> entry[i].reliability;
		myfile >> entry[i].wetWeather;
		myfile >> entry[i].teamID;
		entry[i].team = team[entry[i].teamID];
    	}
    	myfile.close();
}

// Saves engine suppliers, teams and drivers to data file
void Season::save_season(char file_name[])
{
	// Save to specified data file
	cout << "Saving... " << endl;
	ofstream myfile (file_name);

	// Save year
	myfile << year << endl;

	// Save engine suppliers
	myfile << totalEngines << endl;
     	for (short i=int_zero; i<totalEngines; i++)
     	{
           	myfile << engineSupplier[i]->name << endl;
		myfile << engineSupplier[i]->engine->efficiency << endl;
		myfile << engineSupplier[i]->engine->reliability << endl;
		myfile << engineSupplier[i]->engine->power << endl;
		myfile << engineSupplier[i]->engine->fuelEfficiency << endl;
	}
	// Save teams
	myfile << totalTeams << endl;
     	for (short i=int_zero; i<totalTeams; i++)
     	{
           	myfile << team[i]->name << endl;
		myfile << team[i]->car[int_zero]->chassi.speed << endl;
		myfile << team[i]->car[int_zero]->chassi.reliability << endl;
		myfile << team[i]->engineID << endl;
     	}
	// Save drivers
	myfile << totalEntries << endl;
	for (short i=int_zero; i<totalEntries; i++)
     	{
           	myfile << entry[i].name << endl;
		myfile << entry[i].age << endl;
		myfile << entry[i].speed << endl;
		myfile << entry[i].reliability << endl;
		myfile << entry[i].wetWeather << endl;
		myfile << entry[i].teamID << endl;
     	}
     	myfile.close();
}

// Assign a car to each driver
void Season::assign_cars()
{
	// Assuming drivers are sorted by teams
	for (short i=int_zero; i<totalEntries; i++)
	{
		entry[i].teamCar = i % 2;
	}
}

// Reset point tallies for new season
void Season::new_season()
{
	for (short i=int_zero; i<totalEntries; i++) {entry[i].points=int_zero;}
	for (short i=int_zero; i<totalTeams; i++) {team[i]->points=int_zero;}
}

// Summarize drivers, teams and engines
void Season::display_season()
{
	cout << "Season: " << year << endl;
	cout << "Total drivers: " << totalEntries << endl;
	for (short i=int_zero; i<totalEntries; i++)
	{
		entry[i].display_driver(i);
	}
	cout << "Total teams: " << totalTeams << endl;
	for (short i=int_zero; i<totalTeams; i++)
	{
		display_rank(i);
		team[i]->display_name(MAX_CHARS);
		cout << team[i]->car[int_zero]->chassi.speed << ","
		<< team[i]->car[int_zero]->chassi.reliability << " "
		<< team[i]->engineSupplier->name << endl;
	}
	cout << "Total engines: " << totalEngines << endl;
	for (short i=int_zero; i<totalEngines; i++)
	{
		engineSupplier[i]->display_attributes(i);
	}
}

// Display driver race information, aligning data for the table
/*void Season::display_driver_position_and_status(Driver *driver,short rank,short this_lap,int total_gap)
{
	// Print position, driver and team
	display_rank(rank);
	driver->display_name(MAX_CHARS);
        driver->team->display_name(MAX_CHARS);

	// Print lap time and time gap to leader
	display_time(driver->lap[this_lap]);	printSpaces(2);
	display_time(total_gap);		printSpaces(2);

	// Print any other exceptional information
	driver->team->car[driver->teamCar]->display_status();
	if (driver->ranOff) cout << "  RAN OFF!!!";
	if (driver->spun) cout << "  SPUN!!!";
	if (driver->pitting)
	{
		cout << "  IN PIT:";
		display_time(driver->stop);
		cout << "s";
	}
	cout << endl;
}*/

// Prints Drivers Championship table
void Season::display_driver_championship(short round)
{
	cout << year << " DRIVERS CHAMPIONSHIP - ROUND " << round << endl;
	for (short i=int_zero; i<totalEntries; i++) {
		display_rank(i+1);
		entry[i].display_name(MAX_CHARS);
		entry[i].team->display_name(10);
		cout << entry[i].points << endl;
	}
}

// Prints Constructors Championship table
void Season::display_constr_championship(short round)
{
	cout << year << " CONTRUCTORS CHAMPIONSHIP - ROUND " << round << endl;
	for (short i=int_zero; i<totalTeams; i++) {
		display_rank(i+1);
		team[i]->display_name(MAX_CHARS);
		team[i]->engineSupplier->display_name(10);
		cout << team[i]->points << endl;
	}
}

// Prints a table of all drivers and their race finishes this season
void Season::display_driver_results(short totalRaces)
{
	cout << " FULL RESULTS" << endl;
	for (short i=0; i<totalEntries; i++) {entry[i].display_results(totalRaces); cout<<endl;}
}

// Prints a table of all drivers and their grid positions this season
void Season::display_grid_positions(short totalRaces)
{
	cout << " GRID POSITIONS" << endl;
	for (short i=0; i<totalEntries; i++) {entry[i].display_grids(totalRaces); cout<<endl;}
}

// Compute qualifying times for all drivers
void Season::qualifying(short Actives, Circuit *circuit)
{
	unsigned short lapLength = circuit->lapLength;
	short trackSpeed = circuit->speed;
	TrackCondition cond = circuit->cond;
	for (short i=int_zero; i<Actives; i++)
	{
		// Find this driver's team and car index
		short teamCar = entry[i].teamCar;

		// Compute qualifying lap times
		for (unsigned short qLapNumber=0; qLapNumber<MAX_Q_LAPS; qLapNumber++)
		{
			entry[i].current_speed(qLapNumber, lapLength, trackSpeed, cond);
			entry[i].fastest_lap(qLapNumber);
		}
		// Record fastest qualifying lap
		entry[i].qLap = entry[i].fastestLap;
	}
}

// Sort drivers in order of qualifying times
void Season::sort_drivers_by_qualifying(short Actives)
{
	Driver *Temp;
	for (short j=Actives; j>1; j--)
	{
		for (short i=1; i<j; i++)
		{
			if (Act[i]->qLap < Act[i-1]->qLap)
			{
				Temp = Act[i];
				Act[i] = Act[i-1];
				Act[i-1] = Temp;
			}
		}
	}
}

// Updates each car in the race and decides whether it needs to pit
void Season::pit_stops(short Actives,short lapLength,TrackCondition cond)
{
	Tyre *options[4];
	for (short i=int_zero; i<Actives; i++)
	{
		// Find this driver's team and car index
	    	short teamCar = Act[i]->teamCar;

		// Update fuel and tyre status, and decide whether to pit
		Act[i]->pitting = Act[i]->team->car[teamCar]->next_lap(lapLength,cond);
		if (Act[i]->pitting)
		{
			// Find sets of tyres assigned to this driver
			for (short tyreID=0; tyreID<4; tyreID++)
				options[tyreID] = Act[i]->team->tyre[tyreID+4*teamCar];

			// Compute pit stop
			Act[i]->stop = Act[i]->team->car[teamCar]->pit_stop(options, cond);
			Act[i]->distance -= 900+int(Act[i]->lapSpeed * Act[i]->stop/100);
		}
	}
}

// Sort drivers in order of distance traveled
void Season::sort_drivers_by_distance(short Actives,Circuit *circuit)
{
	Driver *Temp;
	int distGap;
	for (short j=Actives; j>1; j--)
	{
		for (short i=1; i<j; i++)
		{
			// Find gap in meters
			distGap = Act[i-1]->distance - Act[i]->distance;

			// If driver has successfully overtaken, swap positions
			if (circuit->overtake(distGap))
			{
				Temp = Act[i];
				Act[i] = Act[i-1];
				Act[i-1] = Temp;
			}
		}
	}
}

// Make sure each car is at least 25 meters behind car ahead
void Season::alignment(short Actives)
{
	int distGap;
	for (short i=1; i<Actives; i++)
	{
		// Find gap in meters
		distGap = Act[i-1]->distance - Act[i]->distance;
		if (distGap < 25) {
			Act[i]->distance = Act[i-1]->distance - 25;
			distGap = 25;
		}
		Act[i]->timeGap = int(100*float(distGap)/Act[i]->lapSpeed);
	}
}

// Assign championship points to drivers and teams
void Season::race_results(short round)
{
	// Assign 10-6-4-3-2-1 points system
	Act[0]->points += 10;
	Act[0]->team->points += 10;
	Act[0]->wins++;
	Act[1]->points += 6;
	Act[1]->team->points += 6;
	Act[2]->points += 4;
	Act[2]->team->points += 4;
	Act[3]->points += 3;
	Act[3]->team->points += 3;
	Act[4]->points += 2;
	Act[4]->team->points += 2;
	Act[5]->points += 1;
	Act[5]->team->points += 1;
}

// Sort drivers in order of points
void Season::rank_drivers()
{
	Driver Temp;
	for (short j=totalEntries; j>1; j--)
	{
		for (short i=1; i<j; i++)
		{
			if (entry[i].points > entry[i-1].points)
			{
				Temp = entry[i];
				entry[i] = entry[i-1];
				entry[i-1] = Temp;
			}
		}
	}
}

// Sort teams in order of points
void Season::rank_constr()
{
	Constructor *Temp;
	for (short j=totalTeams-1; j>1; j--)
	{
		for (short i=0; i<j; i++)
		{
			if (team[i]->points < team[i+1]->points)
			{
				Temp = team[i];
				team[i] = team[i+1];
				team[i+1] = Temp;
				team[i]->update_rank(i);
				team[i+1]->update_rank(i+1);
			}
		}
	}
}

// Sort teams and drivers based on points, and display
void Season::post_race(short round)
{
	race_results(round);
	rank_drivers();
	display_driver_championship(round);
	rank_constr();
	display_constr_championship(round);
}

// ------------------------ THE GRAND PRIX -----------------------------

void Season::grand_prix(Circuit *circuit,short round)
{
	char c;

	// Circuit info
	unsigned short totalLaps = circuit->totalLaps;
	unsigned short lapLength = circuit->lapLength;
	unsigned int totalDistance = totalLaps*lapLength;
	circuit->display_info(round);

	// Driver info
	short Actives = totalEntries;
	short Retirements = int_zero;
	unsigned short R_lap[MAX_ENTRIES];
	short teamCar;

	// Assign pointers and assemble cars
	for (short i=int_zero; i<Actives; i++) {
		Act[i] = &entry[i];
		Act[i]->get_ready_for_GP();
	}

	// QUALIFYING
	short wea = randNumber(WEATHER_RANGE);
	wea = circuit->track_weather(wea);
	circuit->track_conditions(0);
	circuit->display_status();
	cout << endl;
	qualifying(Actives, circuit);
	sort_drivers_by_qualifying(Actives);
	Act[0]->poles++;
	short Q_107 = short(float(Act[0]->qLap)*1.07);

	// LINING UP THE GRID
	cout << "Qualifying Results / Grid Positions" << endl;
	TrackCondition hedge = dry;
	for (short i=int_zero; i<Actives; i++)
	{
		// Find this driver's car index
		teamCar = Act[i]->teamCar;

		// Find sets of tyres assigned to this driver
		Tyre *options[4];
		for (short tyreID=0; tyreID<4; tyreID++)
			options[tyreID] = Act[i]->team->tyre[tyreID+4*teamCar];

		// Pre-race setup and strategy
		Act[i]->get_ready_for_race(i, round, totalDistance, options, circuit->cond);
		Act[i]->display_qual(i);
	}
	cout << " 107% Time: ";	display_time(Q_107); cout << endl;
	cin >> c;

	// THE RACE
	short lapNumber = int_zero;
	unsigned int currentDistance = Act[0]->distance;
	short totalTimeSeconds = 0;
	float time_inc; // In split seconds

	// Keep racing until leader reaches total distance
    	while (Act[0]->distance < totalDistance)
    	{
		wea = circuit->track_weather(wea);
		circuit->track_conditions(0);
		circuit->display_status();

		// NEXT LAP
		lapNumber++;
		currentDistance += lapLength;

		// FIRST DRIVER SPEED/PROGRESS UPDATE
		// Find this driver's car index
		teamCar = Act[0]->teamCar;

		// Compute current lap time
		Act[0]->current_speed(lapNumber, lapLength, circuit->speed, circuit->cond);
		time_inc = float(lapLength)/Act[0]->lapSpeed;
		totalTimeSeconds += short(time_inc);

		// OTHER DRIVERS SPEED/PROGRESS UPDATE
		for (short i=1; i<Actives; i++)
		{
			// Find this driver's car index
			teamCar = Act[i]->teamCar;

			// Compute current speed and subsequent theoretical lap time
			Act[i]->current_speed(time_inc, lapNumber, lapLength, circuit->speed, circuit->cond);
		}

		// DRIVER ERRORS/SPINS
		for (short i=0; i<Actives; i++) {Act[i]->error_update(lapNumber,circuit->cond);}

		// FUEL UPDATE/PITSTOPS
		pit_stops(Actives,lapLength,circuit->cond);

		// POSITION CHANGES
		sort_drivers_by_distance(Actives,circuit);

		// ALIGNMENT
		alignment(Actives);

		// RETIREMENTS
		for (short i=int_zero; i<Actives; i++)
		{
			// Find this driver's car index
			teamCar = Act[i]->teamCar;

			// Check for mechanical problems
			short failure_status = Act[i]->team->car[teamCar]->any_failure(lapLength,circuit->cond);

			// Check for driver errors
			if (Act[i]->collision_update(lapNumber,circuit->cond)) failure_status = ACCIDENT;
			if (Act[i]->spin_update(lapNumber,circuit->cond)) failure_status = SPUN_OFF;

			// Retire driver if car failure or stall has occurred
			if (failure_status > 0)
			{
				Act[i]->retReason = failure_status;

				// Assign driver to list of retirements
				Ret[Retirements] = Act[i];
				R_lap[Retirements] = lapNumber - 1;

				// Store time gap of this driver
				short retiredTimeGap = Act[i]->timeGap;

				// Adjust number of drivers left in the race
				Retirements++;
				Actives--;

				// Sort remaining drivers
				Driver *Temp = Act[i];
				for (short rem=i; rem < Actives; rem++)
				{
					Act[rem] = Act[rem+1];
				}
				Act[Actives] = Temp;

				// Set new time gap for driver now in this position
				if (i < Actives) Act[i]->timeGap += retiredTimeGap;
			}
		}
		// IF THERE IS A CHANGE IN FIRST PLACE, need to make some corrections
		if (Act[int_zero]->distance != currentDistance)
		{
			short Correction = Act[0]->distance - currentDistance;
			for (short i=0; i<Actives; i++) {Act[i]->distance -= Correction;}
			time_inc = float(Correction)/Act[0]->lapSpeed;
			totalTimeSeconds += short(time_inc);
		}
		// DISPLAY THE RACE WITH UPDATE
		if (lapNumber < 10) cout << "   " << lapNumber;
		else cout << "  " << lapNumber;
		cout << "/" << totalLaps << "laps " << endl;
		cout << "    Clock ";
		display_clock(totalTimeSeconds);

		// Display leader
		Act[0]->display_driver_position_and_status(1,lapNumber,0);

		// Display rest of the field
		int Total_gap = 0;
		for (short i=1; i<Actives; i++)
		{
			Total_gap += Act[i]->timeGap;
			Act[i]->display_driver_position_and_status(i+1,lapNumber,Total_gap);
			//display_driver_position_and_status(Act[i],i+1,lapNumber,Total_gap);
		}

		// Display retirements
		for (short i=(Retirements-1); i>=0; i--) {
			cout << " R. ";
			Ret[i]->display_name(MAX_CHARS);
			Ret[i]->team->display_name(MAX_CHARS);
			if (R_lap[i] < 10) cout << "  " << R_lap[i];
			else cout << " " << R_lap[i];
			cout << " laps   " << retirement_reason[Ret[i]->retReason] << endl;
		}
		cin >> c;
	}
	// Record race finish for end of season summary
	for (short i=0; i<Actives; i++) Act[i]->finish[round-1] = i+1;
	for (short i=0; i<Retirements; i++) Ret[i]->finish[round-1] = MAX_ENTRIES;

	// Assign championship points and re-sort drivers and teams
	post_race(round);
}

