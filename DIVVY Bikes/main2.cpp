/*main.cpp*/

//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Lab Week 11: hashing of dates and lottery numbers (SOLUTION)
// 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>

#include "hash.cpp"
#include "hash.h"
#include "hashmap.h"

using namespace std;


//
// LotteryData
// 
// Mega millions lottery winning numbers which is 
// 5 numbers + mega ball number + possible multiplier.
// 
struct LotteryData
{
	string Numbers;
	string MegaBall;
	string Multiplier;
	
	LotteryData()
	{
		Numbers = "";
		MegaBall = "";
		Multiplier = "";
	}
};

//
// string2int
// 
// Converts a string to an integer, unless string is empty, in
// which case 0 is returned.
// 
int string2int(string s)
{
	if (s == "")
		return 0;
	else
		return stoi(s);
}

//
// inputData
// 
// Given a filename denoting lottery winning numbers,
// inputs that data into the given hash table.
// 
bool inputData(string filename, hashmap<string, LotteryData>& hmap)
{
	ifstream  infile(filename);
	
	cout << "Reading " << filename << endl;
	
	if (!infile.good())
	{
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
	
	// file is open, start processing:
	string line;
	
	getline(infile, line);  // input and discard first row --- header row
	
	int count = 0;
	
	while (getline(infile, line))
	{
		stringstream s(line);
		
		string thedate, numbers, megaball, multiplier;
		
		//
		// format: date,xx xx xx xx xx,yy,z
		// 
		// NOTE: z may be missing (the multiplier)
		// 
		getline(s, thedate, ',');  // first value => region
		getline(s, numbers, ',');   // second value => country
		getline(s, megaball, ',');
		getline(s, multiplier, ',');
		
		// we have input the 4 values, and since we are not
		// doing any arithmetic, we can just store them as
		// strings.  If the multiplier is missing then the
		// string is "", which is fine.
		
		//
		// store into hash table
		// 
		LotteryData ld;
		
		ld.Numbers = numbers;
		ld.MegaBall = megaball;
		ld.Multiplier = multiplier;

		hmap.insert(thedate, ld, Hash);
		
		count++;
	}
	
	cout << "# data lines: " << count << endl;
	
	return true;  // we have data to be processed:
}


int main()
{
	cout << "** Mega millions lottery data **" << endl;
	cout << endl;

	//
	// Allocate our hash table: 12 * 31 * 100 = 37,200
	// possible permutations:
	// 
	const int N = 37200;
	hashmap<string, LotteryData> hmap(N);

	//
	// input the winning numbers:
	// 
	string filename = "mega_millions.csv";
	
	bool success = inputData(filename, hmap);
	
	//
	// did we input anything?
	// 
	if (!success)
	{
		cout << "No data, file not found?" << endl;
		return 0;
	}
	
	//
	// allow the user to lookup winning numbers by date:
	// 
	string thedate;
	
	cout << endl;
	cout << "Enter a date 'mm/dd/yyyy' or # to exit> ";
	cin >> thedate;

	//
	// user testing:
	//
	while (thedate != "#")
	{
		//
		// we have a date, let's look in hash table and
		// see if we have any data:
		// 
    LotteryData ld;

    bool found = hmap.search(thedate, ld, Hash);

    if (!found)
    {
      cout << "Sorry, no data for this date" << endl;
    }
    else
    {
      cout << "Winning numbers: " << ld.Numbers << endl;
      cout << "Mega ball: " << ld.MegaBall << endl;
      cout << "Multiplier: " << ld.Multiplier << endl;
    }

		cout << endl;
	  cout << "Enter a date 'mm/dd/yyyy' or # to exit> ";
	  cin >> thedate;
	}
	
	//
	// done!
	// 
	cout << endl;
	cout << "** Done **" << endl;
	
	return 0;
}
