/*
 * Enigma Class
 *------------------------------------------------------------
 * Description: a class encompassing the entire machine. 
 * 
 * Attributes: Plugboard -> Constructed in Enigma::Enigma 
 *             Reflector -> Constructed in Enigma::Enigma
 *             Number of rotors -> Passed as an argument to the constructor
 *             Array of Rotors -> Constructed in Enigma::Enigma
 *
 * Methods: Enigma : Description -> constructs the machine using the provided 
 *                                  configuration files
 *                   Parameters  -> number of rotors, string array of 
 *                                  configuration files.
 *                   Return      -> Does not return .
 *          
 *          Encrypt: Description -> encrypts the string by calling the 
 *                                  individual encrypt functions of its 
 *                                  components
 *                   Parameters  -> string to be encrypted.
 *                   Return      -> void (changes passed by reference).
 *          
 *          Rotate : Description -> recursively rotates the rotors starting 
 *                                  with the specified rotor
 *                   Parameters  -> index of the rotor to be rotated (zero 
 *                                  indexed).
 *                   Return      -> void
 */
#include "enigma.h"
#include "errors.h"
#include <iostream>
#include <fstream> // ifstream
#include <string>

using namespace std;

/* class Enigma Methods
 *-------------------------------------------------
 */
 
Enigma::Enigma(int _n, char **_config){
  // Configure Plugboard
  pb = new Plugboard(_config[1]);
  // Configure Reflector
  try{
    rf = new Reflector(_config[2]);
  } catch (int ret){
    /* If an exception is thrown delete the plugboard then return to main
    * This has to be done manually because now the destructor is not called.
    * Note: No need to delete reflector since the constructor does not allocate
    *       memory if an exception is thrown during its execution.
    * Note 2: Calling delete calls the class's destructor taking care of its
    *         internal allocs
    */
    delete pb;
    
    // Return to main
    throw(ret);
  }
  
  // Configure Rotors
  n = _n - 4; // Number of rotors. (argc - ./enigma, pb, rf and pos)
  if(n > 0){

    // Configure rt Positions
    Positions *pos;
    try{
      pos = new Positions(_config[_n - 1], n);
    } catch (int ret) {
      // delete the allocated pb and rf
      delete pb;
      delete rf;
      
      // Return to main.
      throw(ret);
    }
    
    // Initialize n rotors and places them in the rt array
    int allocs = 0; // Variable to keep track of how many rotors were allocated.
    try{
      
      rt = new Rotor*[n];
      for(int i = 0; i < n; i++){
        rt[i] = new Rotor(_config[i+3], pos->getPos(i));
        allocs++;
      }
      
    } catch (int ret) {
        // Free everything that has been allocated thus far.
        delete pb;
        delete rf;
        delete pos;
        for(int i = 0; i < allocs; i++){
            delete rt[i];
          }
        delete [] rt;
        
        // Return to main
        throw(ret);
    }
    
    // If everything runs smoothly delete pos and return to main.
    delete pos;
  }
}

// Destructor to handle allocations
Enigma::~Enigma(){
  if(n > 0){
    delete pb;
    delete rf;
    for(int i = 0; i < n; i++){
      delete rt[i]; 
    }
    delete [] rt;
  } // If no rotors, prevent delete of uninitialized pointers
  else{
    delete pb;
    delete rf;
  }
}

void Enigma::encrypt(string str){

  // Note: puting the entire encryption cycle in an if results in more code
  //       but fewer CPU cycles (comparison is done once)
  
  // If there are rotors in place
  if(n > 0){
    // Assigning length - More memory but faster execution
    for(unsigned int i = 0, length = str.length(); i < length; i++){
      // IF chars other than capital letters in input
        // throw INVALID_CHARACTER_INPUT
      if(str[i] < 65 || str[i] > 90){
        // Output custom error
        cerr<<str[i]
            <<" is not a valid input character (input characters must "
            <<"be upper case letters A-Z)!"
            <<endl;
            
        // Return to main
        throw(INVALID_INPUT_CHARACTER);
      }
      
      // Rotate the rotors starting with the first in line
      rotate(n-1);
      // 1st pass through plugboard
      str[i] = pb->encrypt(str[i]);
      // 1st pass through rotors
      for(int j = n - 1; j >= 0; j--){
        str[i] = rt[j]->encrypt(str[i]); 
      }
      // Pass through reflector
      str[i] = rf->encrypt(str[i]);
      // 2nd pass through rotors (Reverse)
      for(int j = 0; j < n; j++){
       str[i] = rt[j]->encryptRev(str[i]); 
      }
      // 2nd pass through plugboard
      str[i] = pb->encrypt(str[i]);
      
      // Print letter
      cout<<str[i];
    }
  }
  else{
    for(unsigned int i = 0, length = str.length(); i < length; i++){
      
      // IF chars other than capital letters in input
        // throw with INVALID_CHARACTER_INPUT
      if(str[i] < 65 || str[i] > 90){
        cerr<<str[i]
            <<" is not a valid input character (input characters must be upper "
            <<"case letters A-Z)!"
            <<endl;
        throw(INVALID_INPUT_CHARACTER);
      }
      
      // Pass through plugboard 1
      str[i] = pb->encrypt(str[i]);
      // Pass through reflector
      str[i] = rf->encrypt(str[i]);
      // Pass through plugboard 2
      str[i] = pb->encrypt(str[i]);
      
      // Print letter
      cout<<str[i];
    }
  }

 // All done return to main
 return;
}

// Rotates the rotors recursively before each char is encrypted
void Enigma::rotate(int rti){
  // Check if the we have reached the notch
    // IF yes rotate the next rotor too.
  if(rt[rti]->rotNext() && rti > 0)
    rotate(rti - 1);
  
  // Rotate the rotor.
  rt[rti]->rotate();
  
  // Return to encrypt.
  return;
}