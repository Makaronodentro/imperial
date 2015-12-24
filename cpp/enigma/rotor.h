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
#ifndef ROTOR_H
#define ROTOR_H
 
class Rotor{
 private:
  int pos; // Pos
  int count; // Size of source file
  int nCount; // Number of notches
  int *notch; // Notch location array
  int map[26]; // Array of mappings 
  int mapRev[26]; // Array of reverse mappings

 public:
  // Constructs rotor using configuration file and the initial position
  Rotor(char *_source, int _pos);
  // Destructor
  ~Rotor();

  // Bool to check if next rotor should be rotated too
  bool rotNext();
  // Rotates the rotor by one position
  void rotate();
  
  // Encrypts the character forward
  char encrypt(char c);
  // Encryots the character backwards
  char encryptRev(char c);
};
// -----END OF ROTOR ----- //
#endif