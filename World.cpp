#include "World.h"

Country World::create_country()
{
	string s1,s2;
    	short s3;
	cout << "Country name: ";
    	cin >> s1;
    	cout << "Country nationality: ";
    	cin >> s2;
    	cout << "Country size: ";
	cin >> s3;
	Country country(s1,s2,s3);
	return country;
}

Circuit World::create_circuit()
{
	string s1;
	short att[4];
	unsigned short lapLength;
    	cout << "Circuit name: ";
	cin >> s1;
	cout << "Total laps: ";
	cin >> att[0];
	cout << "Lap length(m): ";
	cin >> lapLength;
	cout << "Circuit location: ";
	cin >> att[1];
	cout << "Circuit speed (1-5): ";
	cin >> att[2];
	cout << "Overtaking (1-5): ";
	cin >> att[3];
	Circuit circuit(s1,lapLength,att);
	return circuit;
}

void World::edit_world()
{
    	char c;
	short s,s2;
	//display_world();
	cout << "~~~~~~ EDIT WORLD ~~~~~~" << endl;
    	cout << "1. Edit one country" << endl;
	cout << "2. Add countries" << endl;
	cout << "3. Remove countries" << endl;
	cout << "4. Edit one circuit" << endl;
    	cout << "5. Add circuits" << endl;
    	cout << "6. Remove circuits" << endl;
	cout << "7. View world" << endl;
    	cout << "Choose an option (1-7): ";
    	cin >> c;
    	s = cha2sho(c);
    	while ((s >= 1) && (s <= 7))
    	{
		if (s == 1)
		{
			cout << "Select country: ";
            		cin >> s2;
            		if (s2 < countries) nation[s2] = create_country();
		}
        	if (s == 2)
        	{
			cout << "ADD how many?: ";
            		cin >> c;
            		s2 = cha2sho(c);
            		int i=countries;
            		countries += s2;
            		while (i<countries)
            			{nation[i] = create_country(); i++;}
		}
        	if (s == 3)
        	{
			cout << "REMOVE how many?: ";
            		cin >> c;
            		s2 = cha2sho(c);
            		countries -= s2;
		}
        	if (s == 4)
        	{
			cout << "Select circuit: ";
            		cin >> s2;
            		if (s2 < circuits) track[s2] = create_circuit();
		}
        	if (s == 5)
        	{
			cout << "ADD how many?: ";
            		cin >> c;
            		s2 = cha2sho(c);
            		int i=circuits;
            		circuits += s2;
            		while (i<circuits)
            			{track[i] = create_circuit(); i++;}
		}
        	if (s == 6)
        	{
			cout << "REMOVE how many?: ";
            		cin >> c;
            		s2 = cha2sho(c);
            		circuits -= s2;
		}
		if (s == 7) display_world();
        	cout << "Choose an option (1-7): ";
        	cin >> c;
        	s = cha2sho(c);
	}
}

void World::load_world (char world_file[])
{
	ifstream myfile (world_file);
	cout << "Loading " << world_file << endl;

	// Loading countries
	myfile >> countries;
    	for (short n=0; n < countries; n++)
    	{
		// Load country name
		myfile >> nation[n].name;

		// Load country nationality
		myfile >> nation[n].nationality;

		// Load country size
		myfile >> nation[n].size;
    	}
	// Loading circuits
	myfile >> circuits;
	for (short n=0; n < circuits; n++)
	{
		myfile >> track[n].name;
		myfile >> track[n].totalLaps;
		myfile >> track[n].lapLength;
		myfile >> track[n].countryID;
	}
    	myfile.close();
}

void World::save_world(char world_file[])
{
	cout << "Saving world... " << endl;
	ofstream myfile (world_file);
	char c;
	char * buffer;

	// Saving countries
	myfile << countries << endl;
	for (short n=0; n < countries; n++)
	{
		myfile << nation[n].name << endl;
		myfile << nation[n].nationality << endl;
		myfile << nation[n].size << endl;
	}
	// Saving circuits
	myfile << circuits << endl;
    	for (short n=0; n < circuits; n++)
    	{
		myfile << track[n].name << endl;
		myfile << track[n].totalLaps << endl;
		myfile << track[n].lapLength << endl;
		myfile << track[n].countryID << endl;
	}
	myfile.close();
}

void World::init_countries(Country country[],short total)
{
	countries = total;
       	for (int i=0; i<total; i++)
		{nation[i]=country[i];}
}

void World::init_circuits(Circuit circuit[],short total)
{
	circuits = total;
       	for (int i=0; i < total; i++)
		{track[i]=circuit[i];}
}

void World::add_countries(Country country[],short total)
{
	countries += total;
       	for (int i=(countries-total); i<countries; i++)
		{nation[i]=country[i];}
}

void World::add_circuits(Circuit circuit[],short total)
{
	circuits += total;
       	for (int i=(circuits-total); i<circuits; i++)
		{track[i]=circuit[i];}
}

void World::display_world()
{
	short j;
	cout << "Countries and Circuits:" << endl;
	cout << "Total countries: " << countries << endl;
	for (short i=0; i<countries; i++)
	{
		display_rank(i);
		nation[i].display_name(MAX_CHARS);
		cout << ", " << nation[i].nationality << "  " << nation[i].size << endl;
	}
	cout << "Total circuits: " << circuits << endl;
	for (short i=0; i<circuits; i++)
	{
		display_rank(i);
		track[i].display_name(MAX_CHARS);	cout << ", ";
		j = track[i].countryID;
		nation[j].display_name(MAX_CHARS);
		cout << "  " << track[i].lapLength << "m  ";
		cout << track[i].totalLaps << " laps  ";
		cout << track[i].total_distance() << "m \n";
	}
	cout << endl;
}

