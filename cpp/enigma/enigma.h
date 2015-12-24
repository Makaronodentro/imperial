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
#ifndef ENIGMA_H
#define ENIGMA_H

#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"
#include "positions.h"

#include <string>

using namespace std;

class Enigma{
 private:
  Plugboard *pb; // Pointer to pb 
  Reflector *rf; // Pointer to rf
  
  int n; // number of rotors
  Rotor **rt; // rotors array 
  
 public:
  // Constructs the class using the constructors of the individual parts
  Enigma(int _n, char **_config);
  ~Enigma();
 
  // Encrypts a string of text
  void encrypt(string str);
  
  // Rotates the Enigma's rotors
  void rotate(int rti);
};
#endif
