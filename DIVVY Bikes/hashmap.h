/*hashmap.h*/

//
// Daniela Chavez
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #06: hashing
//
// References: original non-collision code written by Prof. Hummel (UIC)
// 
// hashmap implements a hash table assuming an imperfect hash function;
// the class is designed to handle collisions.  The class provides
// the underlying hash table along with insert() and search() functions;
// the user of this class must provided a Hash(key, N) function that 
// hashes the given key and returns an integer in the range 0..N-1, 
// inclusive, if the key is valid.  If the key is invalid, the Hash() 
// function must return a negative value.
//
// The hash function is provided in the calls to insert and search.
// Pass the name of your hash function as the 3rd parameter.  Example:
//
//   int myHash(string key, int N)
//   { ... }
//
//   int N = 10000;
//   hashmap<string, double>  hmap(N);  
//
//   if (hmap.insert("deep-dish pizza", 19.99, myHash))
//     cout << "inserted" << endl;
//   else
//     cout << "not inserted?!" << endl;
// 

#pragma once

#include <iostream>
#include <functional>

using namespace std;

template<typename KeyT, typename ValueT>
class hashmap
{
private:
  struct HashEntry
  {
    bool   ContainsData;  // false => empty, true => contains data
    KeyT   Key;           // (key, value)
    ValueT Value;

    HashEntry()
    {
      ContainsData = false;
    }
  };

  HashEntry* HT;  // hash table array of structs
  int        N;   // capacity of hash table (# of locations or array size)

public:
  //
  // constructor: N is the size of the underlying hash table
  //
  hashmap(int N)
  {
    this->N = N;
    this->HT = new HashEntry[N];
  }
  
/*******************************************************************************************************/ 
  
 /*This is my copy constrictor, heavily based on the copy constructor from Project 2, MyMatrix.
  * This will copy all the values */
  hashmap(const hashmap& other)
  {
	  this->N = other.N;
	  this->HT = new HashEntry[other.N];
	  
	  for(int i = 0; i < other.N; i++){ //Because this is an array, we just make a linear traverse
		  if (other.HT[i].ContainsData == true){
			  this->HT[i] = other.HT[i];
		  }
	  }
  }
/*******************************************************************************************************/  
  
  //
  //Operator =
  //
  /*This equal operatior will delete the current information of the first hashtable and
   * copy the information of the second hashtable into the first one*/
  hashmap& operator=(const hashmap& other){
	  delete[] this->HT;
	  this->N = other.N;
	  this->HT = new HashEntry[other.N];
	  
	  for(int i = 0; i < other.N; i++){
		  if (other.HT[i].ContainsData == true){
			  this->HT[i] = other.HT[i];
		  }
	  } 
	return *this;
 }
/*******************************************************************************************************/   
  
  //
  // destructor
  //
  virtual ~hashmap()
  {
    delete[] this->HT;
  }

  //
  // getN
  //
  // Returns the capacity of the hash table, i.e. the value N that
  // was passed to the constructor.
  //
  int getN() const
  {
    return this->N;
  }
/*********************************************************************************************/
  //
  // insert
  //
  // Inserts the given (key, value) pair into the hash table.
  // If the bin at the index contains data, it continues traversing the hashtable
  // until it find an empty bin to store information in.
  // If the insert was successful then true is returned, otherwise false is returned (meaning the key
  // was not hashed successfully, e.g. due to improper formatting).
  //
  // NOTE: the caller must provide a function Hash(key, N) that returns
  // an integer in the the range 0..N-1, inclusive, if the key is valid.
  // If the key is invalid, the hash function must return a negative
  // integer. The hash function is provided by simply calling insert
  // with the name of your hash function.  Example:
  //
  //   int myHash(string key, int N)
  //   { ... }
  //
  //   int N = 10000;
  //   hashmap<string, double>  hmap(N);  
  //
  //   if (hmap.insert("deep-dish pizza", 19.99, myHash))
  //     cout << "inserted" << endl;
  //   else
  //     cout << "not inserted?!" << endl;
  //
  
  bool insert(KeyT key, ValueT value, function<int(KeyT,int)> Hash)
  {
    //
    // Call the provided hash function with the key, and N, the size
    // of our hash table:
    //
    int index = Hash(key, N);
    //
    // insert:
    //
    if (index < 0 || index >= N)  // invalid key or hash function:
    {
      return false;
    }
    else  // valid array index, store into hash table:
    {
	  while(HT[index].ContainsData == true && HT[index].Key != key){
		  index++;
		  
		  index %= N;
	  }
	
      HT[index].Key = key;
      HT[index].Value = value;
      HT[index].ContainsData = true;  // array location now contains data

      return true;
    }
	
	return false;
  }
  /*********************************************************************************************/
  /*This is my insert for command 4. Will output the needed information for the number of bikes needed */
  bool bikeInsert(KeyT key, int value, function<int(KeyT,int)> Hash, int &count)
  {
    //
    // Call the provided hash function with the key, and N, the size
    // of our hash table:
    //
    int index = Hash(key, N);
    //
    // insert:
    //
    if (index < 0 || index >= N)  // invalid key or hash function:
    {
      return false;
    }
	
    else  // valid array index, store into hash table:
    {
	  
	  if (HT[index].ContainsData == true && HT[index].Key == key){
		  HT[index].Value++;
		  return true;
	  }
	  
      HT[index].Key = key;
      HT[index].Value = value;
      HT[index].ContainsData = true;  // array location now contains data
	  count++;
      return true;
    }
	
	return false;
  }
  
 /*********************************************************************************************/
 /*Obtains every key from a hashtable and stores them into a vector*/
    void pushKeys (vector<KeyT> &Vector){
	  int index = 0;
	  
	  while(index != N){
		  Vector.push_back(HT[index].Key);
		  index++;
	  }
  }
/*********************************************************************************************/
  //
  // search
  //
  // Searches the hash table for the matching key, and if found then
  // (1) the value is returned via the reference parameter and (2) true
  // is returned.  If the key could not be found at the given index, then it continues
  // traversing the hashmap until the value is found. If value is not found, then
  // the function returns FALSE.
  //
  // NOTE: the caller must provide a function Hash(key, N) that returns
  // an integer in the the range 0..N-1, inclusive, if the key is valid.
  // If the key is invalid, the hash function must return a negative
  // integer. The hash function is provided by simply calling search
  // with the name of your hash function.  Example:
  //
  //   int myHash(string key, int N)
  //   { ... }
  //
  //   int N = 10000;
  //   hashmap<string, double>  hmap(N);
  //   ...
  //   double price;
  //   if (hmap.search("deep-dish pizza", price, myHash))
  //     cout << "deep-dish piazza costs " << price << endl;
  //   else
  //     cout << "not found?!" << endl;
  //
  bool search(KeyT key, ValueT& value, function<int(KeyT,int)> Hash) const
  {
    int index = Hash(key, N);
    // search:
    //
    if (index < 0 || index >= N)  // invalid key or hash function:
    {
      return false;
    }
    else if (HT[index].ContainsData)  // hash table contains data:
    {
	  if(HT[index].Key != key){ //if the key at the current index is not found
	      //then increment the value of index to travers the hashtable until the matching key is found
		  while (HT[index].Key != key && HT[index].ContainsData == true){
			  index++;
			  index %= N;
		  }
	  }
	  
	  if(HT[index].ContainsData){
		  value = HT[index].Value;  // return value via reference parameter
		  return true;
	  }
      
    }
      return false;

  }
/*********************************************************************************************/
};
