// F1_Project.cpp : Defines the entry point for the console application.
//

/* Need:
		lapped drivers
		remove obsolete functions

		ALWAYS save new code
		WATCH OUT when saving char = 10
*/

// ------------------------------- OBJECTS -------------------------------------

#include "World.cpp"
#include "Season.cpp"

// --------------------------- GLOBAL VARIABLES ---------------------------------


// --------------------------- GLOBAL FUNCTIONS ---------------------------------

// Function storing sample data. Not needed once data file is created.
void Season::load_data() {
	year = 1999;
	totalEngines = 8;    // EngineSupplier("Name",	 effi,relia,power,fuelEff)
	engineSupplier[0] = new EngineSupplier("Mercedes",9,7,9,9);
	engineSupplier[1] = new EngineSupplier("Ferrari",8,9,8,9);
	engineSupplier[2] = new EngineSupplier("Honda",	 9,9,7,9);
	engineSupplier[3] = new EngineSupplier("Ford",	 7,6,8,7);
	engineSupplier[4] = new EngineSupplier("Supertec",8,9,6,9);
	engineSupplier[5] = new EngineSupplier("Peugeot",7,7,6,8);
	engineSupplier[6] = new EngineSupplier("Arrows", 6,7,6,7);
	engineSupplier[7] = new EngineSupplier("Petronas",7,9,6,8);
	totalTeams = 11;
	team[0] = new Constructor("McLaren",	9,7,engineSupplier[0],tyreSupplier[0]);
	team[1] = new Constructor("Ferrari",	8,9,engineSupplier[1],tyreSupplier[0]);
	team[2] = new Constructor("Jordan",	7,9,engineSupplier[2],tyreSupplier[0]);
	team[3] = new Constructor("Stewart",	6,6,engineSupplier[3],tyreSupplier[0]);
	team[4] = new Constructor("Williams",	6,8,engineSupplier[4],tyreSupplier[0]);
	team[5] = new Constructor("Benetton",	6,7,engineSupplier[4],tyreSupplier[0]);
	team[6] = new Constructor("Sauber",	5,7,engineSupplier[7],tyreSupplier[0]);
	team[7] = new Constructor("Arrows",	4,6,engineSupplier[6],tyreSupplier[0]);
	team[8] = new Constructor("Prost",	4,6,engineSupplier[5],tyreSupplier[0]);
	team[9] = new Constructor("BAR",	6,4,engineSupplier[4],tyreSupplier[0]);
	team[10]= new Constructor("Minardi",	3,5,engineSupplier[3],tyreSupplier[0]);
	totalEntries = 22;	//	{age,speed,rel,wet,team}
	entry[0] = Driver("Hakkinen",	31,9,7,6,team[0]);
	entry[1] = Driver("Coulthard",	29,8,7,6,team[0]);
	entry[2] = Driver("MSchumacher",30,9,9,9,team[1]);
	entry[3] = Driver("Irvine",	33,6,7,7,team[1]);
	entry[4] = Driver("Frentzen",	30,8,9,8,team[2]);
	entry[5] = Driver("Hill",	38,6,7,7,team[2]);
	entry[6] = Driver("Barrichello",27,8,8,7,team[3]);
	entry[7] = Driver("Herbert",	35,6,6,7,team[3]);
	entry[8] = Driver("RSchumacher",24,8,7,7,team[4]);
	entry[9] = Driver("Zanardi",	32,5,6,5,team[4]);
	entry[10] = Driver("Fisichella",28,8,7,8,team[5]);
	entry[11] = Driver("Wurz",	29,5,9,6,team[5]);
	entry[12] = Driver("Alesi",	36,6,8,8,team[6]);
	entry[13] = Driver("Diniz",	31,6,7,7,team[6]);
	entry[14] = Driver("DeLaRosa",	28,5,7,5,team[7]);
	entry[15] = Driver("Takagi",	29,7,8,6,team[7]);
	entry[16] = Driver("Trulli",	25,7,5,5,team[8]);
	entry[17] = Driver("Panis",	32,6,7,6,team[8]);
	entry[18] = Driver("Villeneuve",28,8,6,5,team[9]);
	entry[19] = Driver("Zonta",	23,5,6,5,team[9]);
	entry[20] = Driver("Gene",	25,5,7,6,team[10]);
	entry[21] = Driver("Badoer",	28,6,6,6,team[10]);
}

void World::load_data() {
	countries = 30;
	nation[0] = Country("UK","British",65);
	nation[1] = Country("France","French",65);
	nation[2] = Country("Germany","German",82);
	nation[3] = Country("Italy","Italian",60);
	nation[4] = Country("Spain","Spanish",40);
	nation[5] = Country("Belgium","Belgian",10);
	nation[6] = Country("Austria","Austrian",8);
	nation[7] = Country("Switzerland","Swiss",8);
	nation[8] = Country("Japan","Japanese",126);
	nation[9] = Country("Australia","Australian",20);
	nation[10] = Country("Brazil","Brazilian",200);
	nation[11] = Country("Canada","Canadian",35);
	nation[12] = Country("Hungary","Hungarian",10);
	nation[13] = Country("Malaysia","Malaysian",22);
	nation[14] = Country("China","Chinese",1400);
	nation[15] = Country("India","Indian",1200);
	nation[16] = Country("Korea","Korean",50);
	nation[17] = Country("Singapore","Singaporian",7);
	nation[18] = Country("Russia","Russian",144);
	nation[19] = Country("Turkey","Turkish",78);
	nation[20] = Country("Poland","Polish",38);
	nation[21] = Country("Netherlands","Dutch",16);
	nation[22] = Country("Sweden","Swedish",9);
	nation[23] = Country("Finland","Finnish",5);
	nation[24] = Country("Ireland","Irish",4);
	nation[25] = Country("Portugal","Portuguese",10);
	nation[26] = Country("USA","American",310);
	nation[27] = Country("Mexico","Mexican",119);
	nation[28] = Country("Argentina","Argentine",43);
	nation[29] = Country("Chile","Chilean",18);
	circuits = 17;	//{"Name",laps,lapLength,countryID,speed,overtaking}
	track[0] = Circuit("Melbourne",58,5280,9,4,3);
	track[1] = Circuit("Interlagos",70,4600,10,3,2);
	track[2] = Circuit("Imola",63,5000,3,3,3);
	track[3] = Circuit("Monte-Carlo",78,3337,1,1,1);
	track[4] = Circuit("Catalunya",66,4655,4,3,2);
	track[5] = Circuit("Montreal",56,5300,11,4,5);
	track[6] = Circuit("Magny-Cours",72,4412,1,3,3);
	track[7] = Circuit("Silverstone",60,5050,0,3,3);
	track[8] = Circuit("A1-Ring",71,4326,6,4,3);
	track[9] = Circuit("Hochenheim",45,6200,2,5,4);
	track[10] = Circuit("Hungaroring",77,3975,12,1,2);
	track[11] = Circuit("Spa-Francorchamps",44,6500,5,4,5);
	track[12] = Circuit("Monza",51,5800,3,5,4);
	track[13] = Circuit("Nurburgring",67,4900,2,3,4);
	track[14] = Circuit("Kuala-Lumpur",55,5800,13,4,5);
	track[15] = Circuit("Suzuka",53,6000,8,3,4);
	track[16] = Circuit("Jerez",68,4550,4,3,3);
}


// ------------------------------ MAIN FUNC -------------------------------------

int main ()
{
    	char c;
	short total_races;
	srand(time(NULL));

	// Loading data
	char season_file[] = "f1season.txt";
	char world_file[] = "f1world.txt";
	//Season season(season_file);
	//World world (world_file);
	Season season;
	World world;
	season.assign_cars();
	season.edit_season();
	world.edit_world();

	// Start new season
	season.new_season();
	cout << "How many races?" << endl;
	cin >> total_races;
	for (short round=1; round<=total_races; round++)
	{
		cout << "Ready to race?" << endl;
		cin >> c;
		season.grand_prix(&world.track[round-1],round);
	}
	// Display season results
	season.display_grid_positions(total_races);
	cin >> c;
	season.display_driver_results(total_races);

	// Save game data
	season.save_season(season_file);
	world.save_world(world_file);
    	cin >> c;
    	return 0;
}

