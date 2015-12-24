#include <iostream>
#include <cstdio>
#include "sudoku.h"
#include <chrono>
#include <cstring>

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  /* This section tests the is_complete(board) function. */
  cout << "====================== Question 1 ======================" << endl << endl;


  // Attempt to load easy.dat (unsolved puzzle). Expected output "Board is NOT complete."
  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  // Attempt to load easy-solution.dat (solved puzzle). Expected output "Board is complete."
  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  /* This section tests the make_move(position, digit, board) function */
  cout << "====================== Question 2 ======================" << endl << endl;

  // load board easy to use for testing
  load_board("easy.dat", board);

         // GOOD tests 

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Should be OK
  cout << "Putting '3' into G8 is ";
  if (!make_move("G8", '3', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

	// BAD tests

  // Should NOT be OK - Random check
  cout << "Putting '1' into A1 is ";
  if (!make_move("A1", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Should NOT be OK - Testing Vertical Check
  cout << "Putting '7' into A2 is ";
  if (!make_move("A2", '7', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Should NOT be OK - Testing Horizontal Check
  cout << "Putting '3' into A2 is ";
  if (!make_move("A2", '3', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);
  
  // Should NOT be OK - Testing Sector Check
  cout << "Putting '4' into A1 is ";
  if (!make_move("A1", '4', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Should NOT be OK - Zero
  cout << "Putting '0' into A1 is ";
  if (!make_move("A1", '0', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Should NOT be OK - Not a digit
  cout << "Putting '!' into A1 is ";
  if (!make_move("A1", '!', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Should NOT be OK - Col out of bounds
  cout << "Putting '1' into A10 is ";
  if (!make_move("A10", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // Should NOT be OK - Row out of bounds
  cout << "Putting '1' into K1 is ";
  if (!make_move("K1", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  /* TASK 2 TESTS END */

  /* This section tests save_board(name, board) function */
  cout << "====================== Question 3 ======================" << endl << endl;

  // load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  /* This section tests the solve_board(board) function */
  cout << "====================== Question 4 ======================" << endl << endl;

  /* Difficulty Measurement Variables */
  
  // Creates a variable t1 that records the time right before the solve_board call
  chrono::high_resolution_clock::time_point t1;
  // Creates a variable t2 that records the time right after the solve_board call
  chrono::high_resolution_clock::time_point t2;

  performance *easy = new performance; 
  performance *med = new performance; 
  performance *mys1 = new performance; 
  performance *mys2 = new performance; 
  performance *mys3 = new performance; 

  /* END OF DIFFICULTY VARIABLES */

  load_board("easy.dat", board);
  
  // Count initial digits as a measure of difficulty
  strcpy(easy->filename, "easy.dat");
  easy->digits = count_digits(board);
  
  // Initialize t1
  t1 = chrono::high_resolution_clock::now();
  if (solve_board(board)) {
    // Initialize t2
    t2 = chrono::high_resolution_clock::now();
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  } else{ 
    // Initialize t2
    t2 = chrono::high_resolution_clock::now();
    cout << "A solution cannot be found." << endl;
  }
  // Creates a variable duration that holds the difference between t2 and t1
  // That will be the execution time of solve_board 
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  
  record_diff(easy);
  easy->duration = duration;

  cout << endl;

  // Medium Solution

  load_board("medium.dat", board);
  strcpy(med->filename, "medium.dat");
  med->digits = count_digits(board);
  t1 = chrono::high_resolution_clock::now();
  if (solve_board(board)) {
    t2 = chrono::high_resolution_clock::now();
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
  } else {
    t2 = chrono::high_resolution_clock::now();
    cout << "A solution cannot be found." << endl;
  }
 
  duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  
  record_diff(med);
  med->duration = duration;

  cout << endl;

  /* This section tests the 3 mystery boards */
  cout << "====================== Question 5 ======================" << endl << endl;

  // Mystery 1 Solution

  load_board("mystery1.dat", board);
  strcpy(mys1->filename, "mystery1.dat");
  mys1->digits = count_digits(board);
  t1 = chrono::high_resolution_clock::now();
  if (solve_board(board)) {
    t2 = chrono::high_resolution_clock::now();
    cout << "The 'mystery1' board has a solution:" << endl;
    display_board(board);
  } else { 
    t2 = chrono::high_resolution_clock::now();
    cout << "A solution cannot be found." << endl;
  }

  duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  
  record_diff(mys1);
  mys1->duration = duration;

  cout << endl;

  // Mystery 2 Solution

  load_board("mystery2.dat", board);
  strcpy(mys2->filename, "mystery2.dat");
  mys2->digits = count_digits(board);
  t1 = chrono::high_resolution_clock::now();
  if (solve_board(board)) {
    t2 = chrono::high_resolution_clock::now();
    cout << "The 'mystery2' board has a solution:" << endl;
    display_board(board);
  } else {
    t2 = chrono::high_resolution_clock::now();
    cout << "A solution cannot be found." << endl;
  }

  duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  
  record_diff(mys2);
  mys2->duration = duration;

  cout << endl;

  // Mystery 3 Solution

  load_board("mystery3.dat", board);
  strcpy(mys3->filename, "mystery3.dat");
  mys3->digits = count_digits(board);
  t1 = chrono::high_resolution_clock::now();
  if (solve_board(board)) {
    t2 = chrono::high_resolution_clock::now();
    cout << "The 'mystery3' board has a solution:" << endl;
    display_board(board);
  } else {
    t2 = chrono::high_resolution_clock::now();
    cout << "A solution cannot be found." << endl;
  }

  duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  
  record_diff(mys3);
  mys3->duration = duration;

  cout << endl;

	// write more tests

  /* Printing Difficulty and Performance Statistics */

  table_header();
  display_performance(easy);
  display_performance(med);
  display_performance(mys1);
  display_performance(mys2);
  display_performance(mys3);
  table_footer();

  
  delete easy;
  delete med;
  delete mys1;
  delete mys2; 
  delete mys3;

  return 0;
}
