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
#ifndef POSITIONS_H
#define POSITIONS_H

class Positions{
 private:
  int *pos; // Array of rotor positions
  int count; // Size of the configuration file

 public:
  // Constructs the class using a configuration file
  Positions(char *_source, int n);
  ~Positions();

  // Returns the position of a specific rotor
  int getPos(int rotorNo);
};

// END OF POSITIONS //
#endif