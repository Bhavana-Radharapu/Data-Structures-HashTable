/*main.cpp*/

//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in 
// sorted order.
//
// Original author: Prof. Joe Hummel
// Modified by:     << Bhavana Laxmi Radharapu>>
//
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "ILplates.h"

using namespace std;


//
// hashInput:
//
void hashInput(string basename, ILplates& hashplates)
{
  string infilename = basename + ".txt";
  ifstream infile(infilename);

  if (!infile.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
    cout << endl;
    exit(-1);
  }

  //
  // input the plates and fines:
  //
  cout << "Reading '" << infilename << "'..." << endl;

  string fine;
  string plate;

  getline(infile, fine);

  //
  // for each pair (fine, license plate), hash and store/update fine:
  //
  while (!infile.eof())
  {
    getline(infile, plate);

    //cout << fine << endl;
    //cout << plate << endl;

    // 
    // is plate valid?  Only process valid plates:
    //
    if (hashplates.Hash(plate) >= 0)  // yes:
    {
      int amount = hashplates.Search(plate);

      if (amount < 0)  // not found:
      {
        hashplates.Insert(plate, stoi(fine));
      }
      else  // we found it, so update total in hash table:
      {
        amount += stoi(fine);
        hashplates.Insert(plate, amount);
      }

    }//valid

    getline(infile, fine);
  }
}
void swap2(int &x, int &y)   // swaps two integers
{  
    int temp = x;  
    x = y;  
    y = temp;  
}

void swap1(string &s1, string &s2)   // swaps two strings
{  
    string temp = s1;  
    s1 = s2;  
    s2 = temp;  
}

void bubbleSort(vector<string> &V1, vector<int> &V2)   // bubble sort 
{  
    size_t i, j;  
    for (i = 0; i < V1.size()-1; i++)      
	{
		for (j = 0; j < V1.size()-i-1; j++) 
		{
		  if (V1[j] > V1[j+1]) 
		  {
		    swap1(V1[j], V1[j+1]);   // swaps plates
			swap2(V2[j],V2[j+1]);   // swaps fines on respective plates
		  }
		}
	}
}  


int main()
{
  int    N;        // = 10000;
  string basename; // = "tickets1";

  cout << "Enter hashtable size> ";
  cin >> N;

  hashtable<string, int>  ht(N);
  ILplates hashplates(ht);

  cout << "Enter base filename> ";
  cin >> basename;
  cout << endl;

  //
  // process input file of fines and license plates:
  //
  
  hashInput(basename, hashplates);   
  
  //
  // debugging:
  //
  
  vector<string> plates = ht.Keys();   // vector of license plates
  vector<int> amounts = ht.Values();   // vector of fines
  cout << "Sorting..." << endl;
  bubbleSort(plates, amounts); // Bubble sort

	
  string outfilename = basename +"-output.txt";  // naming the output file 
  ofstream outfile(outfilename);     // creating an object to write the data 

  cout << "Writing '" << outfilename << "'..." << endl;  
  for(size_t j=0;j<plates.size();j++)
  {
	string plate = plates.at(j);
	int amount = amounts.at(j);
	outfile << "\"" << plate << "\"" << " $" <<amount << endl;  // writing on to a file 
  }

  //
  // done:
  //
  
  return 0;
}