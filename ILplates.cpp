/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//
// << Bhavana Laxmi Radharapu >>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <string>
#include <sstream>

#include "ILplates.h"

using namespace std;



bool allDigits(string plate){   // function checks if the string has all digits
	for(size_t i=0;i<plate.size();i++){
		if(!isdigit(plate[i])){
			return false;
		}
	}

	return true;
}

bool allChars(string plate){  // function checks if the string has all characters
	for(size_t i=0;i<plate.size();i++){
		if(!isupper(plate[i])){
			return false;
		}
	}
	return true;
}

vector<string> tokenize(string line)  // breaks the license plate into sections by spaces between them
{
  vector<string> Tokens;
  stringstream stream(line);
  string token;

  while (getline(stream, token, ' '))
  {
    Tokens.push_back(token);
  }

  return Tokens;
}

//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//
int ILplates::Hash(string plate)
{
	unsigned long long int index = -1;
	vector<string> tokens = tokenize(plate); // tokenize the license place to perform hashing
	
	if(tokens.size() > 2){ // check for the valid string with length of utmost 2 
		return -1;
     }
//-----------------------------------------------------------------	
	else if(tokens.size()==1){ // checks for the vanity car plates
		string one = tokens.at(0); // variable to store licence plate
	 if(allDigits(one) && one.length() <= 3 ){
		index = stoi(tokens.at(0));

	}
	else if(allChars(one) && one.length() <=7){
		int stringHash = 9762; 
		for (size_t i = 0;i<one.length(); i++) {
			stringHash = (stringHash * 113) + (one[i]-'A');
		}
	}
	else 
	{
			return -1;
    }
	  }
//-----------------------------------------------------------------	
	else if(tokens.size() == 2){ // checks if the personalized license plates are in right format
		string one = tokens.at(0); // variable to store the first half of licence plate
		string two = tokens.at(1); // variable to store the second half of licence plate
		if(allChars(one) && allDigits(two))  
		{
			if( (one.size()<= 5 && two.size() <= 2) || (one.size() == 6 && two.size() == 1) ) // the length of alphabets is 5 and integer part is 2
			{
				int stringHash = 9762; 
				for (size_t i = 0;i<one.length(); i++) {
					stringHash = (stringHash * 113) + one[i]-'A';
				  }
				int num = stoi(two);
				index = num + stringHash;
			}
			else
				return -1;
		}
		else
		{
			return -1;
		}
	}

  return index  % HT.Size();
}

//-----------------------------------------------------------------

//
// Search
// 
// Hashes and searches for the given license plate; returns the 
// associated value for this plate if found, or -1 if not found.
//
int ILplates::Search(string plate)
{

    int record = Hash(plate);
	int probed = 0;
	int value = 0;
	string key;
	int i=0;
	bool empty;
	int c1 = 67; //random values for quadratic probing
    int c2 = 61; //random values for quadratic probing
	while(probed < HT.Size() ){
		HT.Get(record,empty, key,value); // Get function gives the status of the index

     if(empty)
		 return -1;
	 if(key == plate)
		 return value;
	 
      i++;
      record += (c1 * i) + (c2 * i * i) ;
	  record = record % HT.Size();
      ++probed;  // probing 
	
     
	 }
	return -1;
}

//-----------------------------------------------------------------
//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue)
{

  int i =0;
  int record = Hash(plate);
  int probed = 0;
  bool empty;
  int value;
  string key;
  int c1 = 67; //random values for quadratic probing 
  int c2 = 61; //random values for quadratic probing
	
  while(probed < HT.Size()){
	
	 HT.Get(record,empty,key,value); // Get function gives the status of the index
	 
	 if(empty || key == plate){
		 HT.Set(record, plate, newValue); // sets the key in the index
         break;
     }
     
	  i++;
      record += (c1 * i) + (c2 * i * i) ;
	  record = record % HT.Size();
      probed++; 
  }
}

			
