/*
 * Positions Class
 *------------------------------------------------------------
 * Description: a class that contains the initial positions of the rotors.
 *              for more rotors it simply repeats these positions
 *
 * Attributes: count -> number of positions
 *             pos -> array of rotor starting positions
 *
 * Methods: Position:Description -> constructs position array using the provided 
 *                                  configuration file.
 *                   Parameters  -> string of the configuration file name,
 *                                  int of number of rotors.
 *                   Return      -> Does not return.
 *          
 *          getPos : Description -> Returns the position of the specified rotor
 *                   Parameters  -> the index of a rotor
 *                   Return      -> initial position of the rotor (int).
 */
#include "positions.h"
#include "errors.h"
#include <iostream>
#include <fstream> // ifstream
#include <cstring> // strchr

using namespace std;
 
Positions::Positions(char *_source, int n){
  
  // Check the file extension
  char *ext = strrchr(_source, '.') + 1;
  
  if(strcmp("pos", ext) != 0){
    cerr<<"No rotor starting position file provided"<<endl;
    
    // Return to Enigma()
    throw(NO_ROTOR_STARTING_POSITION);
  }
  
  // Open configuration file
  ifstream in;
  in.open(_source);

  if(in.fail()){
    cerr<<"File: "<<_source<<" could not be opened. throwing..."<<endl;
    
    // Return to Enigma()
    throw(ERROR_OPENING_CONFIGURATION_FILE);
  }

  // Initialize count and pos
  count = 0;
  int _pos[n];

  // Read the first 3 integers and place them in an array
  while(count < n && in>>_pos[count]){ // Care for precedence otherwise segfault.
    // IF a number is < 0 || > 25
      // throw with INVALID_INDEX
    if(_pos[count] < 0 || _pos[count] > 25){
      cerr<<"Invalid index at position: "<<count<<endl;
      
      // Return to Enigma()
      throw(INVALID_INDEX);
    }
    
    count++;
  }

  // Scan through the rest of the file for any invalid chars
  int scrap;
  while(in>>scrap){
    // IF a number is < 0 || > 25
      // throw with INVALID_INDEX
    if(scrap < 0 || scrap > 25){
      cerr<<"Invalid index at position: "<<count<<endl;
      
      // Return to Enigma()
      throw(INVALID_INDEX);
    }
  }
  
  // IF file contains any characters other than numeric characters
    // throw with NON_NUMERIC_CHARACTER
  if(in.fail() && !in.bad() && !in.eof()){
    cerr<<"Non-numeric character in rotor positions file rotor.pos"<<endl;
    
    // Return to Enigma()
    throw(NON_NUMERIC_CHARACTER);
  }
  
  // IF count < n
    // throw
  if(count != n){
    cerr<<"No starting position for rotor "
        <<count
        <<" in rotor position file: rotor.pos"
        <<endl;

    // Return to Enigma()
    throw(NO_ROTOR_STARTING_POSITION);
  }
  
  // Close ifstream
  in.close();
  
  // If all good copy to pos array and return to Enigma()
  // Placing new here reduces the number of manual deletes.
  pos = new int[n];
  for(int i = 0; i < n; i++){
    pos[i] = _pos[i];
  }
}

// Destructor -> needed to destroy the array
Positions::~Positions(){
  delete [] pos;
}
 
// Returns the initial position of a rotor
int Positions::getPos(int rotorNo){
  // rotorNo is zero indexed
  return pos[rotorNo];
}
// END OF POSITIONS //