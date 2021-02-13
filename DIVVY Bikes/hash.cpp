/*hash.cpp*/

/*
 * Daniela Chavez - My hash function
 * University of Ilinois at Chicago
 * CS251
 * */

#include <iostream>
#include <string>
#include <cctype>  /*isdigit*/
#include <regex>   /*regular expressions*/

#include "hash.h"

using namespace std;

//
// isNumeric
//
// Returns true if the given string is numeric (all digits), false
// if not.  If the string is empty, false is returned since there 
// are no digits present.
//
bool isNumeric(string s)
{
	//
	// A string is numeric if it contains 1 or more digits, so let's
	// use a regular expression to check that.
	//
	// we are using POSIX basic notation for regular expressions, see
	//   https://en.cppreference.com/w/cpp/regex/ecmascript
	// where [:d:] means digit, [[:d:]] means match a single digit.
	// The + means match the preceding sub-expression 1 or more times.
	//
	regex pattern("[[:d:]]+", regex::ECMAScript);

	smatch matchResults;  // provides more details on the match

	if (regex_match(s, matchResults, pattern))
		return true;
	else
		return false;
}

/*********************************************************************************************/
/*This hash function will return the number ID of the stations as
 * an integer*/
int Hash1(string Id, int N)
{
	if (isNumeric(Id) == true){
		int index = stoi(Id);
		return index % N;
	}
	return -1;
	
}
/*********************************************************************************************/
/*Daniel J. Bernstein created a popular version of a multiplicative string hash function that 
 * uses an initial value of 5381 and a multiplier of 33. Bernstein's hash function performs well
 * for hashing short English strings. - Zybooks 9.4
 * 
 * Will be using this for command 2*/
int Hash2(string abbrev, int N){
	
	unsigned long long hash = 5381;
	
	for(char c : abbrev){
		hash = ((hash << 5) + hash) + c;
	}
	return hash % N;
}
/*********************************************************************************************/
/*This hash function will identify is the first two characters of the strint are
 * equal to 'Tr'. Once identified, it will remove those 2 characters and convert the
 * remaining string into an integer.
 * index is the result of that conversion % 10400000*/
int Hash3(string tripId, int N){
	int index = 0;
	if(tripId[0] == 'T' && tripId[1] == 'r'){
		tripId.erase(0,2); //Getting rid of "Tr" in front of the string
		if(isNumeric(tripId) == true){
			index = stoi(tripId) % 10400000;
			return index % N;
		}
	return -1;
	}
  return -1;
}

/*********************************************************************************************/
/*This hash function will be used for command 4. The function identifies if the first
 * character of the string is equal to 'B'. If true, then It will erase the first character
 * and will convert the remaining string into numeric.
 * The index is the result % N (size of hashtable)*/
int Hash4(string bikeId, int N){
	int index = 0;
	if(bikeId[0] == 'B'){
		bikeId.erase(0,1);
		if(isNumeric(bikeId) == true){
			index = stoi(bikeId);
			return index % N; 
		}
	  return -1;
	}
	return -1;
}
/*********************************************************************************************/