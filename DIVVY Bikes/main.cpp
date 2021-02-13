/*main.cpp*/

/* Daniela Chavez
 * NetID: dchave29
 * U. of Illinois, Chicago
 * CS 251: Spring 2020 */

/*************************************PROJECT #6*************************************
 * Your program is going to input 2 types of data: stations in theDIVVY system, and 
 * bike trips that riders have taken on a DIVVY bike. Your program needs to lookup 
 * stations by their station id(integer) or their station abbreviation (string)
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

#include "hash.h"
#include "hashmap.h"


using namespace std;

/*This is going to be my Stations structure. In this struct I will be storing
 * information retrieved from the stations.csv file*/
struct Stations
{
	string Id; // Identification Number of the station
	string Abbrev; // Abbreviation of the station name
	string FullName; // Full name of Station
	string Latitude; 
	string Longitude;
	string Capacity; // Number of docks in station
	string OnlineDate; // the date the station came online in the DIVVY system
	
	Stations(); //Initializing variables in struct
};

//Initializing all my variables to "". This will change as information is stored.
Stations::Stations(){ 
	Id        = "";
	Abbrev    = "";
	FullName  = "";
	Latitude  = "";
	Longitude = "";
	Capacity  = "";
	OnlineDate= "";	
}

/*This is going to be my Trips structure. This is where I am going to store
 * all of the imformation from 'trips.csv'*/
struct Trips
{
	string TripId; //Identification number of the trip
	string StartTime; //Starting time of the trip
	string StopTime; //Stop time of the trip
	string BikeId; //Identification number of the bike
	string Duration; //Trip duration
	string From; //Location at beggining of trip
	string To;  //Location at end  of trip
	string Identifies; //Gender of person who took bike
	string BirthYear; // Birth year of person who took bike
	
	Trips(); //Initializer of variables
};

//Initializing all my variables to "". This will change as information is stored.
Trips::Trips(){
	TripId     = "";
	StartTime  = "";
	StopTime   = "";
	BikeId     = "";
	Duration   = "";
	From       = "";
	To         = "";
	Identifies = "";
	BirthYear  = "";
}

/*********************************************************************************************/
/*This is my input data function. This function will be used to store data in my first two
 * Hashtables. I will be opening a file in this function and storing all its data in
 * the Stations struct I created earlier*/ 
bool inputStationData(string filename, hashmap<string, Stations>& hmap, hashmap<string, int>& hmap2)
{
	ifstream  infile(filename);//opeining file
	if (!infile.good())
	{ //Checking is the file has sucessfully opened
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
	
	// file is open, start processing:
	string line;
	getline(infile, line);  // input and discard first row --- header row
	
	int count = 0; //This count integer will return the number of inserted stations
		
	while (getline(infile, line)) //traversing the file
	{
		stringstream s(line); //storing data in s
		string id, abbrev, fullName, latitude, longitude, capacity, onlineDate; //these string will hold retieved data
		
		getline(s, id, ',');     //retrieving ID of stations
		getline(s, abbrev, ','); //retrieving abbreviation
		getline(s, fullName, ','); //retieving full name of station
		getline(s, latitude, ','); //retrieving latitude
		getline(s, longitude, ','); //retrieving longitude
		getline(s, capacity, ','); //retrieving capacity
		getline(s, onlineDate, ','); //retrieving onlineDate

		//Storing information into S
		Stations S;
		
		S.Id = id;
		S.Abbrev = abbrev;
		S.FullName = fullName;
		S.Latitude = latitude;
		S.Longitude = longitude;
		S.Capacity = capacity;
		S.OnlineDate = onlineDate;

		hmap.insert(id, S, Hash1); //inserting data into first hashtable
		hmap2.insert(abbrev, stoi(id), Hash2); //inserting data into second hash table
		count++; //increment station number
	}
	
	cout << "# of stations: " << count << endl;
	return true;  //Data has been processed
}


/*********************************************************************************************/
/*This function purpose is to store information inside of the last two hash tables,
 * storing data from trips,csv into each one.*/
bool inputTripData(string filename, hashmap<string, Trips>& hmap, hashmap<string,int>& hmap2)
{
	ifstream  infile(filename); //storing data
	
	if (!infile.good())
	{ //making sure that the file has been opened sucessfully
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
	// file is open, start processing:
	string line;
	getline(infile, line);  // input and discard first row --- header row
	
	int count = 0; //meant to keep track of number of trips
	int countBikes = 0; //keaping track of number of bikes
	
	while (getline(infile, line)) //traversing through file
	{
		stringstream s(line);
		string tripId, startTime, stopTime, bikeId, duration, from, to, identifies, birthyear;
		
		//Storing file data into these strings
		getline(s, tripId, ',');  
		getline(s, startTime, ',');  
		getline(s, stopTime, ',');
		getline(s, bikeId, ',');
		getline(s, duration, ',');
		getline(s, from, ',');
		getline(s, to, ',');
		getline(s, identifies, ',');
		getline(s, birthyear, ',');


		Trips T; //Used to store data
		int BikeUsage = 1; //keeping track of bike usage
		//Storing data in struct	
		T.TripId = tripId;
		T.StartTime = startTime;
		T.StopTime = stopTime;
		T.BikeId = bikeId;
		T.Duration = duration;
		T.From = from;
		T.To = to;
		T.Identifies = identifies;
		T.BirthYear = birthyear;
		
		hmap.insert(tripId, T, Hash3); //inserting into first hashtable
		hmap2.bikeInsert(bikeId, BikeUsage, Hash4, countBikes); //insering into second hashtable
		count++;
		
	}
	cout << "# of trips: " << count << endl; //ptinting the total number of trips
	cout << "# of bikes: " << countBikes << endl; //total number of bikes
	return true;  // we have data processed:
}

/*********************************************************************************************/
/*This function will separate my user input into separate strings for
command 5.  */
void separateString(string source, string& one, string& two, string& three){
    source.erase(0,7); //This erases the word 'nearby + space
    one = source.substr(0, source.find(" ")); //first string
    source.erase(0, source.find(" ")+1); //deleting words from source

    two = source.substr(0, source.find(" "));//second string
    source.erase(0, source.find(" ")+1); //deleting words from source

    three = source.substr(0, source.find(" ")); //Thrird string is remaining words
}

/*********************************************************************************************/
/*This is my help function. This will output the help commands if needed*/
void help(){
	cout << "Available commands:" << endl;
	cout << " Enter a Station id (e.g. 341)" << endl;
    cout << " Enter a station abbreviation (e.g. Adler)" << endl;
    cout << " Enter a trip id (e.g. Tr10426561)" << endl;
    cout << " Enter a bike id (e.g. B5218)" << endl;
    cout << " Nearby stations (e.g. nearby 41.86 -87.62 0.5)" << endl;
    cout << " Similar trips (e.g. similar Tr10424639 0.3)" << endl;
}

/*********************************************************************************************/
/*Function outputs Stations data after being obtained by the search function.
 * Value is stored in Stations struct.*/
void StationsData(Stations S1){
	cout << "Station:" << endl;
	cout << " ID: " << S1.Id << endl;
	cout << " Abbrev: " << S1.Abbrev << endl;
	cout << " Fullname: " << S1.FullName << endl;
	cout << " Location: (" << setprecision(6) << stod(S1.Latitude) <<", "<< stod(S1.Longitude) <<")" << endl;
	cout << " Capacity: " << S1.Capacity << endl;
	cout << " Online date: " << S1.OnlineDate << endl;
}

/*********************************************************************************************/
/*This function will potput the trips intomation for command three*/
void TripsData(Trips T, Stations S1, hashmap<string, Stations>StationsById){
	cout<<"Trip: "<< endl;
	cout<<" ID: " << T.TripId << endl;
	cout<<" Starttime: " << T.StartTime <<endl;
	cout<<" Bikeid: " << T.BikeId << endl;
	
	//this part will help us putput the correct timing		
	int durationTrip = stoi (T.Duration);
	int seconds = durationTrip%60;
	int minutes = durationTrip/60;
    int hours = minutes/60;
	//Making sure that minutes is not over 9 minutes, else we have to re-adjust nours and mins			
	if(minutes > 59){
		hours += minutes/60;
		minutes = minutes%60;
	}
	//duration of the entire trip
	cout<<" Duration: ";
	if(hours > 0)
		cout << hours << " hours, ";
	if(minutes > 0)
		cout << minutes << " minutes, ";
	cout << seconds <<" seconds" << endl;
	
	//Searching for the abbreviation of the station it was from			
	StationsById.search(T.From, S1, Hash1);
	cout << " From station: " << S1.Abbrev << " (" << T.From << ")" << endl;
	//searching for the last destination of the trip
	StationsById.search(T.To, S1, Hash1);
	cout << " To station: " << S1.Abbrev << " (" << T.To << ")" << endl;
	//Last information about rider			
	cout <<" Rider identifies as: " << T.Identifies << endl;
	cout <<" Birthyear: " << T.BirthYear<< endl;		
}
/*********************************************************************************************/
	
int main(){
	
	int index1 = 10000; //size of first and second hashmap
	int index2 = 2500000; //size of third hashmap
	int index3 = 50000; //size of last hashmap
	int N = 0; //int to store ints in for later use
  //created hashtables in which we will store information int2;
	
	hashmap<string, Stations>StationsById(index1);
	hashmap<string, int>StationsByAbbrev(index1);
	hashmap<string,Trips>TripsById(index2);
	hashmap<string,int>BikesById(index3);
	
	Stations S1; //will hold information about first 2 hash tabless S1;
	Trips T; //holds info about tripsps T;
	
	cout << "** DIVVY analysis program **"<< endl;
	cout << endl;
	
	
	string filename1; //stations.csv;
	string filename2;//trips.csv;
	string userInput;
	
	cout << "Enter stations file> "; //Entering stations.csv
	getline(cin, filename1);
	
	cout << "Enter trips file> "; //Entering trips.csv
	getline(cin, filename2);
	cout << endl;
	
	cout << "Reading " << filename1 << endl;
	cout << "Reading " << filename2 << endl;
	cout << endl;
	
	//Inserting the users chosen files into hashtablesdl;
	bool success1 = inputStationData(filename1, StationsById, StationsByAbbrev);
	bool success2 = inputTripData(filename2, TripsById, BikesById);
	
	//error msg if the input doesnt works
	if(!success1 && !success2) {
		cout << "No data, no files found?" << endl;
		return 0;
	}
	
	cout << endl;
	cout << "Please enter a command, help, or #> ";
	getline(cin, userInput);
	
	//While loop will end exit if the user inputs a '#'
	while(userInput != "#"){
		/**************************SEARCHING STATIONS USING ID***************************************/
		if (isNumeric(userInput)){
			if (StationsById.search(userInput, S1, Hash1)) //If they found the data they were looking for
				StationsData(S1);
			else
				cout << "Station not found" << endl; //error msg
		}
		/*************************SEARCHING TRIPS**************************************************/	
		else if(userInput[0] == 'T' && userInput[1] =='r'){
			if(TripsById.search(userInput, T, Hash3) == true){
				TripsData(T,S1, StationsById); //Retrieveing data from this function			
			}
			else
				cout << "Trip not found" <<endl; //error msg
		}
		
		/***************************SEARCHING BIKE ID AND USAGE NUMBER******************************/
		//searching file for bike ID		  
		else if (userInput[0] == 'B'){
			if (BikesById.search(userInput, N, Hash4) == true){
				cout<<"Bike:"<< endl;
				cout <<" ID: " << userInput<<endl;
				cout <<" Usage: " << N << endl;
			}	
			else
				cout << "Bike not found" <<endl; //error msg			
	    }
		
		/******************************HELP: DISPLAY COMMANDS**************************************/
		else if(userInput == "help"){
			help(); //Function that will display commands
		}	
		
		/***************************SEACH ID USING ABBREVIATIONS***********************************/
		else{
			if (StationsByAbbrev.search(userInput, N, Hash2) == true){
				string tmp = to_string(N);
				if (StationsById.search(tmp, S1, Hash1) == true){
					StationsData(S1);	
				}
				else
					cout << "Station not found" << endl;	
			}
			else
				cout << "Station not found" << endl;
		}
		/**********************AFTER COMMAND, PLEASE ENTER NEW COMMAND****************************/
		cout << endl;
		cout << "Please enter a command, help, or #> ";
		getline(cin, userInput);
	}//closing while loop
	
	cout << endl;
	return 0;
} //closing main
	
	