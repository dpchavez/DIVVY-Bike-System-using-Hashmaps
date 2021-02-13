/*hash.h*/

//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Lab Week 11: hashing of dates and lottery numbers (SOLUTION)
// 

#include <string>

using namespace std;

bool isNumeric(string s);
int Hash1(string Id, int N);
int Hash2(string abbrev, int N);
int Hash3(string tripId, int N);
int Hash4(string bikeId, int N);
