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
#ifndef PLUGBORAD_H
#define PLUGBORAD_H

class Plugboard{
private:
  // Struct to hold connected pairs
  struct Plugcable{
    char a;
    char b;
  };

  Plugcable *plugcables;// Array of connected pairs 
  int count; // Size of configurationg file

public:
  // Constructs the class using a configuration file
  Plugboard(char *_source);
  // Frees the allocated plugcables
  ~Plugboard();

  // Encrypts char c and returns it
  char encrypt(char c);
};
#endif