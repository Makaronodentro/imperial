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
#ifndef REFLECTOR_H
#define REFLECTOR_H

class Reflector{
 private:
  // Struct to hold connected pairs
  struct RfPair{
    char a;
    char b;
  };

  RfPair *rfPairs; // Array of pairs
  int count; // Size of configuration file
  
 public:
  // Constructs the class using a configuration file
  Reflector(char* source);
  // Frees the allocated rfPairs
  ~Reflector();
  
  // Encrypts char c and returns it
  char encrypt(char c);
};

// ----- END OF REFLECTOR ----- //
#endif