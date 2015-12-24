/*
 * Reflector Class
 *------------------------------------------------------------
 * Description: a class representing a reflector. Contains an array 
 *              of reflector pairs used to encrypt characters
 * 
 * Attributes: RfPair -> A struct symbolizing a connection between 2 chars 
 *             rfPairs -> An array of reflector pairs to hold all mappings 
 *             Count -> The number of reflector pairs
 *
 * Methods: Reflector: Description -> constructs the reflector using the 
 *                                    provided configuration file
 *                   Parameters  -> string with the name of the config file.
 *                   Return      -> Does not return.
 *          
 *          Encrypt: Description -> encrypts a char by finding its rfPair
 *                                  and switching it with its pair.
 *                   Parameters  -> char to be encrypted.
 *                   Return      -> the encrypted char.
 */
#include "reflector.h"
#include "errors.h"
#include <iostream>
#include <fstream> // ifstream
#include <cstring> // strchr

using namespace std;

Reflector::Reflector(char *_source){
  
  // Check the file extension
  char *ext = strrchr(_source, '.') + 1;
  
  if(strcmp("rf", ext) != 0){
    cerr<<"File: "
        <<_source
        <<" is not a reflector configuration file. throwing..."<<endl;
    
    // Return to Enigma()
    throw(ERROR_OPENING_CONFIGURATION_FILE);
  }
  
  // Open configuration file
  ifstream in;
  in.open(_source);

  if(in.fail()){
    cerr<<"File: "<<_source<<" could not be opened. throwing..."<<endl;
    
    // Return to Enigma()
    throw(ERROR_OPENING_CONFIGURATION_FILE);
  }
  
  /* Temporary array "a" to hold mappings
   * Int type makes error checking less demanding for the CPU
   * (no conversions from int to char)
   * (no need for manual deletes in case of errors)*/
  // more than 26 ints will throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS
  int a[27]; // +1 to avoid segfaults

  // Initialize count
  count = 0;

  // Traverse the configuration file and add the pairs to the array
  while(in>>a[count]){
    
    // IF more than 26 parameters
      // throw
    if(count > 25){
      cerr<<"Incorrect (odd) number of parameters in " // cut to stay 
          <<"reflector file reflector.rf"<<endl;       // within 80 chars
      
      // Return to Enigma()
      throw(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    }
    
    // IF a number is < 0 || > 25
      // throw with INVALID_INDEX
    if(a[count] < 0 || a[count] > 25){
      cerr<<"Invalid index at position: "<<count<<endl;
      
      // Return to Enigma()
      throw(INVALID_INDEX);
    }
    
    // IF connection int appears twice (i.e. 23 23 || 16 7 7 9)
      // throw with INVALID_REFLECTOR_MAPPING
    for(int i = 0; i < count; i++){
      if(a[count] == a[i]){
        cerr<<"Invalid Reflector Mapping at position: "<<count<<endl;
        
        // Return to Enigma()
	      throw(INVALID_REFLECTOR_MAPPING);
      }
    }   
    count++;
  }
  
  
  // IF file contains any characters other than numeric characters
    // throw with NON_NUMERIC_CHARACTER
  /* NOTE: Error checking is done by checking if the failbit has been
   *       marked true AND if the eofbit and badbit haven't.
   *       If this is the case the i/o operation in>>a[count] has
   *       encountered a logical error. */
  if(in.fail() && !in.bad() && !in.eof()){
    cerr<<"Non-numeric character in reflector file reflector.rf"<<endl;
    
    // Return to Enigma()
    throw(NON_NUMERIC_CHARACTER);
  }
  
  // IF more odd number of parameters
      // throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS
    if(count % 2 != 0){
      cerr<<"Incorrect (odd) number of parameters in "
          <<"reflector file reflector.rf"<<endl;
      
      // Return to Enigma()
      throw(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    }

  // IF odd number of indexes
    // throw with INCORRECT NUMBER OF REFLECTOR PARAMETERS
  if(count != 26){ 
    cerr<<"Insufficient number of mappings in "
        <<"reflector file: reflector.rf"<<endl;
    
    // Return to Enigma()
    throw(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
  }
  
  // Close the filestream. No further need for it.
  in.close();
  
  // Set count equal to number of rfPairs
  count /= 2;
  
    // If all good place data into rfPairs and return to Enigma()
  // Allocate enough memory to hold the rfPairs
  rfPairs = new RfPair[count];

  // Place the pairs into the struct
  for(int i = 0; i < count; i ++){
    rfPairs[i].a = a[i*2] + 65;
    rfPairs[i].b = a[i*2+1] + 65;
  }
}

// Destructor
Reflector::~Reflector(){
  delete [] rfPairs;
}

// Encrypts char c and returns it
char Reflector::encrypt(char c){
  // Traverse through all the plugcables
  for(int j = 0; j < count; j++){
    // If c == to char a, switch it with b
    if(c == rfPairs[j].a)
      c = rfPairs[j].b;
    // If c == to char b, switch it with a
    else if(c == rfPairs[j].b)
      c = rfPairs[j].a;
  }
  
  // Return char to Enigma()
  return c;
}
// END OF REFLECTOR //