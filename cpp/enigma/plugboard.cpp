/*
 * Plugboard Class
 *------------------------------------------------------------
 * Description: a class representing a plugboard. Contains an array 
 *              of Plugcables used to encrypt characters
 * 
 * Attributes: Plugcable -> A struct symbolizing a connection between 2 chars 
 *             Plugcables -> An array of plugcables to hold all mappings 
 *             Count -> The number of plugcables
 *
 * Methods: Plugboard : Description -> constructs the plugboard using the 
 *                                     provided configuration file
 *                   Parameters  -> string with the name of the config file.
 *                   Return      -> Does not return.
 *          
 *          Encrypt: Description -> encrypts a char by finding its cable
 *                                  and switching it with its pair.
 *                   Parameters  -> char to be encrypted.
 *                   Return      -> the encrypted char.
 */
#include "plugboard.h"
#include "errors.h" // error codes
#include <iostream>
#include <fstream> // ifstream
#include <cstring> // strchr

using namespace std;

Plugboard::Plugboard(char *_source){

  // Check the file extension
  char *ext = strrchr(_source, '.') + 1;
  
  if(strcmp("pb", ext) != 0){
    cerr<<"File: "
        <<_source
        <<" is not a plugboard configuration file. throwing..."
        <<endl;
    
    // Return to Enigma()
    throw(ERROR_OPENING_CONFIGURATION_FILE);
  }

  // Open Configuration file
  ifstream in;
  in.open(_source);

  if(in.fail()){
    cerr<<"File: "<<_source<<" could not be opened. throwing..."<<endl;
    
    // Return to main
    throw(ERROR_OPENING_CONFIGURATION_FILE);
  }
  
  /* Temporary array "a" to hold mappings
   * Int type makes error checking less demanding for the CPU
   * (no conversions from int to char) 
   * (no need for manual deletes in case of errors)*/
  // More than 26 ints will throw INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
  int a[27];  // +1 to avoid segfaults
  
  // Initializes count
  count = 0;

  // Traverse the configuration file and add the pairs to the array
  while(in>>a[count]){
    // IF more than 26 parameters in plugboard
      // throw INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
    if(count > 25){
      cerr<<"Incorrect number of parameters in plugboard file plugboard.pb"
          <<endl;
      
      // Return to main
      throw(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    }
    // IF a number is < 0 || > 25
      // throw INVALID_INDEX
    if(a[count] < 0 || a[count] > 25){
      cerr<<"Invalid Index at position: "<<count<<endl;
      
      // Return to main
      throw(INVALID_INDEX);
    }
    
    // IF connection int appears twice (i.e. 23 23 || 16 7 7 9)
      // throw IMPOSSIBLE_PLUGBOARD_CONFIGURATION
    for(int i = 0; i < count; i++){
      if(a[count] == a[i]){
	      cerr<<"Incorrect number of parameters in plugboard file plugboard.pb"
	          <<endl;
	      
	      // Return to main
	      throw(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
      }
    }   
    count++;
  }
  
  // IF file contains any characters other than numeric character
      // throw NON_NUMERIC_CHARACTER
  /* NOTE: Error checking is done by checking if the failbit has been
   *       marked true AND if the eofbit and badbit haven't.
   *       If this is the case the i/o operation in>>a[count] has
   *       encountered a logical error. */
  if(in.fail() && !in.bad() && !in.eof()){
    cerr<<"Non-numeric character in plugboard file plugboard.pb"<<endl;
    
    // Return to main
    throw(NON_NUMERIC_CHARACTER);
  }

  // Close the filestream. No further need for it.
  in.close();

  // IF odd number of indexes
    // throw INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
  if(count % 2 != 0 || count > 26){
    cerr<<"Incorrect number of parameters in plugboard file plugboard.pb"<<endl;
    
    // Return to main
    throw(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
  }

  // Set count equal to number of plugcables
  count /= 2;

  // If all good place data into plugcables array and return to Enigma()
  // Allocate enough memory to hold the plugcables.
  plugcables = new Plugcable[count];

  // Place the pairs in the plugcables array
  for(int i = 0; i < count; i ++){
    plugcables[i].a = a[i*2] + 65;
    plugcables[i].b = a[i*2+1] + 65;
  }
}

// Destructor
Plugboard::~Plugboard(){
  delete [] plugcables;
}

// Encrypts char c and returns it
char Plugboard::encrypt(char c){
  // Traverse through all the plugcables
  for(int j = 0; j < count; j++){
    // If c == to char a, switch it with b
    if(c == plugcables[j].a)
      c = plugcables[j].b;
    // If c == to char b, switch it with a
    else if(c == plugcables[j].b)
      c = plugcables[j].a;
  }

  // Return char to Enigma()
  return c;
}
// END OF PLUGBOARD //