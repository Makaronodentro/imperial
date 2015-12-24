#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"
#include <iomanip>

using namespace std;

// Global variable to count recursive calls and make move calls
int reps = 0, mmreps = 0; 

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* -------------------------------------------------*/
/* GK513 Functions                                  */

/*
 * Task 1
 * -------------------------------------------------
 * Name: is_complete(const char board[9][9]);
 * Description: Checks whether the board is populated solely by digits (except 0)
 * Parameters: Receives a 9x9 array of chars.
 * Returns: True if the board array is fully occupied by digits (excluding 0), false otherwise.
 *
 * NOTES: Assumes character encoding is ASCII or UTF-8
*/

bool is_complete(const char board[9][9]){

  // Use for loops to traverse the entire array
  // r for rows, c for columns
  for(int r = 0; r < 9; r++){
    for(int c = 0; c < 9; c++){
      // check if the cell contains something other than an ASCII digit (excluding 0)
      // return FALSE if NOT
      if(board[r][c] < 49 || board[r][c] > 57)
	return false;
    }
  }
  
  // if cells contained digits ONLY
  return true;
}

/* END OF TASK 1 */

/*
 * Task 2
 * -------------------------------------------------
 * Name: make_move(const char *position, const char digit, char board[9][9]);
 * Description: Attempts to place a digit into the specified position of the sudoku board.
 * Parameters: String of coordinates (1 letter from A to I, 1 digit from 1 - 9)
 *             Char digit, the digit to be inserted (49 - 57).
 *             Character array 9x9, the sudoku board.
 * Returns: True if move is valid, false otherwise.
 *          Move must be within the range A1 - I9.
 *          Digit must be within the range 1 - 9.
 *          Move must abide to sudoku rules.
 *
 * NOTES: Assumes character encoding is in ASCII or UTF-8
 *        Assumes coordinates is given in latin letters.
 *        Accepts lowercase too for coordinates.
*/

bool make_move(const char *position, const char digit, char board[9][9]){

  /* Ensure proper position input */
  // Reject values such as "A91"
  // Also prevents bad acces when checking range, in case length < 2
  if(strlen(position) != 2) 
    return false;

     // Check coordinate range

  // Check y coordinate (A (ASCII: 64) - I (ASCII: 73) / (a (ASCII: 97) - i (ASCII: 105))
  if((*position < 64 || *position > 73) && (*position < 97 || *position > 105))
    return false;
  // Check x coordinate (1 (ASCII: 49) - 9 (ASCII: 57))
  // Note +1 to access the next char in the string
  if(*(position + 1) < 49 || *(position + 1) > 57)
    return false;
  
  /* Check if digit is valid */
  if(digit < 49 || digit > 57)
    return false;

  /* Ensure move abides to sudoku rules*/
  // convert position to ints to be used as indices to access the board
  int r = *position - 65, c = *(position + 1) - 49;

  // Check_valid traverses through the row, col and 3x3 sector and checks if digit exists already.
  if(!check_valid(r, c, digit, board)){
    return false;
  }


  // If none of the checks returns false insert digit and return true.
  board[r][c] = digit;

  return true;
}

/*
 * Helper function for make_move. Checks if the row, col or 3x3 sector already contain the digit.
 * Parameters: Row index, column index, digit, board
 * Returns: False if the digit already exists in row, col or sector, true otherwise.
 */
bool check_valid(int r, int c, const char digit, const char board[9][9]){
    /* Check if digit exists in the same row */
    // Loop through the columns of the row
    for(int i = 0; i < 9; i++){
      // If the digit exists return false 
      if(board[r][i] == digit)
	return false;
    }

    // Check if digit exists in the same column
    // Loop through the rows of the column
    for(int i = 0; i < 9; i++){
      // If the digit exists return false
      if(board[i][c] == digit)
	return false;
    }
    
    // Check if digit exists in the sector
    // Determine cell position
    r = (r / 3) * 3; // Will set r = 0 for rows A-C, r = 3 for rows D - F, r = 6 for rows G - I
    c = (c / 3) * 3; // Will set c = 0 for cols 1-3, c = 3 for cols 4 - 6, c = 6 for cols 7 - 9

    // Loop through the sector
    for(int i = r; i < r + 3; i++){
      for(int j = c; j < c + 3; j++){
	// If the digit exists return false
	if(board[i][j] == digit)
	  return false;
      }
    }
    
    // If none of the row, cols and sector tests fail return true
    return true;
}

/* END OF TASK 2 */

/*
 * Task 3
 * -------------------------------------------------
 * Name: save_board(const char *filename, const char board[9][9]);
 * Description: Outputs the two-dimentional char array board to a file with the name filename.
 * Parameters: String of the filename in which the output will be saved.
 *             Character array 9x9, the sudoku board.
 * Returns: True if writting was successful, false otherwise.
 *
*/

bool save_board(const char *filename, const char board[9][9]){
  
  // Open output file stream
  ofstream out;
  out.open(filename);
  // If opening fails return false
  if(out.fail()){
    cout<<"File openning failed, could not save board"<<endl;
    return false;
  }

  // Traverse through the board and save each char in the file
  for(int r = 0; r < 9; r++){
    for(int c = 0; c < 9; c++){
      out.put(board[r][c]);
    }
    // Place a newline char at the end of every row
    out.put('\n');
  }

  // Close the stream
  out.close();

  /*
  // Optional Check of save file for future use, uncomment to use

  // open in file stream
  ifstream in;
  in.open(filename);
  // If opening fails return false
  if(in.fail()){
    cout<<"File openning failed, could not verify save state"<<endl;
    return false;
  }

  
  // Traverse through the file and compare to board
  char ch;
  for(int r = 0; r < 9; r++){
    for(int c = 0; c < 9; c++){
      // Get next char
      in.get(ch);
      // If not equal to board, return false
      if(ch != board[r][c])
	return false;
    }
    // Skip newline chars
    in.get(ch);
  }
  in.close();
  */

  return true;
}

/* END OF TASK 3 */

/*
 * Task 4
 * -------------------------------------------------
 * Name: solve_board(char board[9][9]);
 * Description: Attempts to complete the sudoku board.
 * Parameters: Character array 9x9, the sudoku board.
 * Returns: True if a solution is found and the board is complete.
 *          False otherwise and the board is reset.
 *
 * NOTES: Assumes character encoding is in ASCII or UTF-8
 *        Assumes coordinates input is in latin characters
*/

bool solve_board(char board[9][9]){
  
  // Variable used to estimate the number of recursive calls.
  reps++;

  // Check if board is complete
  if(is_complete(board)){
    return true;
  }
  
  // Find the next unsolved cell
  int r = 0; // row index
  int c = 0; // col index
  while((board[r][c] >= 49 && board[r][c] <= 57) && r < 9){
    // If not at the end of the row get the next col.
    if(c < 8){ 
      c++;
    }
    else{ // If at the end of the row get next row and reset col to 0.
      c = 0;
      r++;
    }
  }

  char position[3];
  
  position[0] = r + 65 ;
  position[1] = c + 49 ;
  position[2] = '\0';

  // Test for possible moves
  // Setting i = '1' to effortlessly pass it to make_move
  for(int i = '1'; i <= '9'; i++){
    mmreps++;  
    if(make_move(position, i, board)){ 
      
      // Check if the board has been solved.
      if(solve_board(board)){
	return true;
      }
    }
  }
 
  // After trying to input 1-9 in the empty cell
  // No moves can be made, so reset the cell and return false
  board[r][c] = '.';
  return false;
}
/* END OF TASK 4 */

/*
 * Name: difficulty(const char board[9][9])
 * Description: Counts the number of digits in a board
 * Parameters: a 9x9 board of chars
 * Returns: Returns an integer with the count of digits in the board
 */

int count_digits(const char board[9][9]){
  int count = 0;
  for(int r = 0; r < 9; r++){
    for(int c = 0; c < 9; c++){
      if(board[r][c] >= 49 && board[r][c] <= 57){
	count++;
      }
    }
  }
  
  return count;
}

void record_diff(performance *x){
  // Assign current rep count to struct
  x->reps = reps;
  // Reset count
  reps = 0;

  // Assign current mmrep count to struct
  x->mmreps = mmreps;
  // Reset
  mmreps = 0;
}

void display_performance(performance *x){
  
  cout<<"------------------------------------------------------------------------------------------"<<endl;
  cout<<"| "<<setw(13)<<x->filename;
  cout<<" | "<<setw(13)<<x->digits;
  cout<<" | "<<setw(13)<<x->reps;
  cout<<" | "<<setw(13)<<x->mmreps;
  cout<<" | "<<setw(13)<<x->duration;
  cout<<" | \033[1;31m"<<setw(7)<<setprecision(4)<<static_cast<float>(x->reps)/x->duration<<"\033[0m |"<<endl;
}

void table_header(){
  
  cout<<"------------------------------------------------------------------------------------------"<<endl;
  cout<<"| "<<setw(13)<<"FILENAME";
  cout<<" | "<<setw(13)<<"No. DIGITS";
  cout<<" | "<<setw(13)<<"No. CALLS";
  cout<<" | "<<setw(13)<<"No. ATTEMPTS";
  cout<<" | "<<setw(13)<<"MICROSECONDS";
  cout<<" | "<<setw(7)<<"CAL/DUR"<<" |"<<endl;
  
}

void table_footer(){
   cout<<"------------------------------------------------------------------------------------------"<<endl;
}
