/* ---------------------------------------------------------------------------
 *  
 *   | / / /  |\    |  |  | / / / /  |\    /|      /\
 *   |        | \   |  |  |          | \  / |     /  \
 *   | / /    |  \  |  |  |          |  \/  |    /    \
 *   |        |   \ |  |  |       |  |      |   /______\
 *   | / / /  |    \|  |  |/ / / /|  |      |  /        \
 * 
 * Description: A simulation of a simplified Enigma machine
 * Author: Georgios Kontogiannis, gk513@ic.ac.uk
 * Last Updated: 19th November 2015
 * 
 * Comments: The program has been checked for memory leaks using valgrind
 *           for both erroneous scenarios and smooth execution.
 *
 * -------------------------------------------------------------------------*/
#include <iostream>
#include <string>

#include "errors.h" // Error Codes
#include "enigma.h" // Enigma Class
#include "helper.h" // User Input function

using namespace std;

int main(int argc, char **argv) {

    
  // IF insufficient parameters. == 4 implies only pos or rot was provided
    // exit with INSUFFICIENT_NUMBER_OF_PARAMETERS
  if(argc < 3 || argc == 4){
    cerr<<"usage: enigma plugboard-file reflector-file (<rotor-file>* "
        <<"rotor-positions)?"<<endl; // Break to keep within 80 chars
    return(INSUFFICIENT_NUMBER_OF_PARAMETERS);
  }
  
  // Declare a pointer for the machine
  Enigma *machine;
    
  // Try to construct the machine by loading and checking the config files
  try{
   machine = new Enigma(argc, argv);
  } catch (int ret){
    // If one of the checks throws an exception, catch it and return it.
      /* Note: if an exception is thrown by the constructor
       *       "new" fails to allocate memory, so no need for a delete. */
    return ret;
  }

  // Empty string to hold input
  string str("");

  // Get user input
  str = getInput();

  // Encrypt the string and output
  try{
    machine->encrypt(str);
  } catch(int ret) {
    // If the encryption function throws an exception delete the machine
    delete machine;
    // Return error code
    return ret;
  }
  
  // If everything runs smoothly deallocate the memory reserved by the machine
  delete machine;
  
  return NO_ERROR;
}