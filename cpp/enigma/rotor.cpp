/*
 * Rotor Class
 *------------------------------------------------------------
 * Description: a class representing a rotor. Contains an array of integers
 *              that determine which char points to which.
 *
 * Attributes: count -> count of mappings, should be 26
 *             pos -> holds current position by counting the rotations from the
 *                    rotors default position(A=0). [0, 25]
 *             nCount -> int representing number of notches
 *             notch -> array of the positions of the rotor's notches [0, 25]
 *             map -> the mappings when inserting the char from the front(pass1)
 *             mapRev -> the mappings when inserting the char from back(pass2)
 *             Note: having a mapRev consumes double the memory but speeds up
 *                   encryption. (no need to search the char in map)
 *
 * Methods: Rotor  : Description -> constructs the rotor using the provided 
 *                                  configuration file.
 *                   Parameters  -> string of the configuration file name,
 *                                  int of initial position.
 *                   Return      -> Does not return.
 *          
 *          Encrypt: Description -> encrypts the char by accessing the map array
 *                                  and switching it with its mapped char.
 *                   Parameters  -> char to be encrypted.
 *                   Return      -> encrypted char.
 *          EncryptRev: Description -> encrypts the char by accessing the map 
 *                                  array and switching it with its mapped char.
 *                   Parameters  -> char to be encrypted.
 *                   Return      -> encrypted char.
 *          
 *          rotNext: Description -> Checks if the next char to be on top is the
 *                                  notch
 *                   Parameters  -> none.
 *                   Return      -> true if pos + 1 == notch.
 *          rotate : Description -> rotates the rotor by increasing pos by 1.
 *                                  Keeps pos within [0, 25]
 *                   Parameters  -> none.
 *                   Return      -> void.
 */
#include "rotor.h"
#include "errors.h"
#include <iostream>
#include <fstream> // ifstream
#include <cstring> // strchr

using namespace std;
 
Rotor::Rotor(char *_source, int _pos){
  
  // Check the file extension
  char *ext = strrchr(_source, '.') + 1;
  
  if(strcmp("rot", ext) != 0){
    cerr<<"File: "
        <<_source
        <<" is not a rotor configuration file. throwing..."
        <<endl;
    
    // Return to Enigma()
    throw(ERROR_OPENING_CONFIGURATION_FILE);
  }
  
  // Open configuration file
  ifstream in;
  in.open(_source);

  // Check for opening errors.
  if(in.fail()){
    cerr<<"File: "<<_source<<" could not be opened. throwing..."<<endl;
    
    // Return to Enigma()
    throw(ERROR_OPENING_CONFIGURATION_FILE);
  }

  // Initialize count;
  count = 0;

  // Read through the file and place the mappings into the map array
  // Stop at 26th int as the 27th is the notch
  while(count < 26 && in>>map[count]){
    // IF a number is < 0 || > 25
      // throw INVALID_INDEX
    if(map[count] < 0 || map[count] > 25){
      cerr<<"Invalid index at position: "<<count<<endl;
      
      // Return to Enigma()
      throw(INVALID_INDEX);
    }
    
    // IF connection 23 23 || 16 7 7 9 -> map * to 1 output
      // throw INVALID_ROTOR_MAPPING
    for(int i = 0; i < count; i++){
      if(map[count] == map[i]){
        
        cerr<<"Invalid mapping of input "
            <<count
            <<" to output "
            <<map[count]
            <<" (output "
            <<map[count]
            <<" is already mapped to from input "
            <<i
            <<") in rotor file: rotor.rot"
            <<endl;
            
        // Return to Enigma()
	      throw(INVALID_ROTOR_MAPPING);
      }
    }
    
    count++;
  }
  
  // IF file contains any characters other than numeric characters
  // AND if error wasn't caused by the eof character
    // throw NON_NUMERIC_CHARACTER
  if(in.fail() && !in.bad() && !in.eof()){
    cerr<<"Non-numeric character for mapping in rotor file rotor.rot"<<endl;
    
    // Return to Enigma()
    throw(NON_NUMERIC_CHARACTER);
  }
  
  // IF eof has been reached and mappings != 26 invalid mapping
    // throw INVALID ROTOR MAPPING
  if(count != 26) {
    cerr<<"Not all inputs mapped in rotor file: rotor.rot"<<endl;
    
    // Return to Enigma()
    throw(INVALID_ROTOR_MAPPING);
  }
  
  // Map the backside of the rotor
  for(int i = 0; i < count; i++){
    mapRev[map[i]] = i;
  }
  
  //-------------------------//
  /* <-- Get the notches --> */
  
  // Read the notches
  int _notch[26]; // Temporary array, can't have more than 26 notches
  nCount = 0; // Initialize notch count
  while(in>>_notch[nCount]){
    // IF too many notches found throw INVALID_ROTOR_MAPPING
    if(nCount > 26){
      cerr<<"Too many notches in file: "<<_source<<endl;
      
      // Return to Enigma()
      throw(INVALID_ROTOR_MAPPING);
    }
    
    // IF a notch is < 0 || > 25
      // throw INVALID_INDEX
    if(_notch[nCount] < 0 || _notch[nCount ] > 25){
      cerr<<"Invalid index at position: "<<count<<endl;
      
      // Return to Enigma()
      throw(INVALID_INDEX);
    }
    
    // IF double notch
      // throw INVALID_ROTOR_MAPPING
    for(int i = 0; i < nCount; i++){
      if(_notch[nCount] == _notch[i]){
        
        cerr<<"Invalid mapping of input "
            <<count
            <<" to output "
            <<_notch[nCount] + 26
            <<" (output "
            <<_notch[nCount] + 26
            <<" is already mapped to from input "
            <<i
            <<") in rotor file: rotor.rot"
            <<endl;
            
        // Return to Enigma()
	      throw(INVALID_ROTOR_MAPPING);
      }
    }
    
    nCount++;
  }
  
  // IF no notch
    // throw INVALID_ROTOR_MAPPING
  if(in.eof() && nCount == 0) {
    cerr<<"No notches in file: "<<_source<<endl;
    
    // Return to Enigma()
    throw(INVALID_ROTOR_MAPPING);
  }
  
  // If error not caused by eof char or bad read -> non-numeric char
  if(in.fail() && !in.bad() && !in.eof()){
    cerr<<"Non-numeric character for mapping in rotor file rotor.rot"<<endl;
    
    // Return to Enigma()
    throw(NON_NUMERIC_CHARACTER);
  }
  
  // If notches pass all tests assign to notch array
  // Places new here eliminates the need for manual deletes
  notch = new int[nCount];
  for(int i = 0; i < nCount; i++){
    notch[i] = _notch[i];
  }
  
  // Initialize position. Which letter is on top.
  pos = _pos;
}

// Destructor
Rotor::~Rotor(){
  delete [] notch;
}

// Encrypts forwards
char Rotor::encrypt(char c){
  int mip; // map index

  // Assuming letters are mapped clockwise
  // ENTRY position moved has counter-clockwise by pos
  // i.e. pos == 1, c = A (65), mip = 1 (Entry through B)
  mip = (c - 65 + pos) % 26;
  

  //encrypt
  c = map[mip];
  
  // Assuming letters on back are mapped counter-clockwise
  // EXIT position moved clockwise by pos
  // i.e. pos == 1, c = A (0), mip = 25 (Exit through Z)
  c = (c - pos + 26) % 26 + 65;

  return c;
}

// Encrypts backwards
char Rotor::encryptRev(char c){
  int mip;
  // Assuming letters on back are mapped counter-clockwise
  // ENTRY position for the reverse map is moved clockwise by pos
  // i.e. pos == 1, c = A (65), mip = 1 (Entry through B)
  mip = (c - 65 + pos) % 26;
  
  // Ecnrypt
  c = mapRev[mip];
  
  // Assuming letters on front are mapped clockwise
  // EXIT position for the reverse map is moved counter-clockwise by pos
  // i.e. pos == 1, c = A (0), mip = 25 (Exit through Z)
  c = (c - pos + 26) % 26 + 65;

  // Return char to Enigma()
  return c;
}

// Checks if the next rotor should turn as well
bool Rotor::rotNext(){
  // Return to Enigma::Rotate()
  for(int i = 0; i < nCount; i++){
     if(pos + 1 == notch[i])
      return true;
  }
  
  return false;
} 

// Rotates the rotor
void Rotor::rotate(){
  // Increases relPos by one and the restricts it to the range [0, 25]
  ++pos %= 26;
  // Return to Enigma::Rotate()
}

// END OF ROTOR //