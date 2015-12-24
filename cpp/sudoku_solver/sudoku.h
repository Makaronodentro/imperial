#ifndef SUDOKU_H
#define SUDOKU_H

// Predefined functions
void load_board(const char *filename, char board[9][9]);

void display_board(const char board[9][9]);

 /********************
 *  GK513 Functions  *
 ********************/

// Struct to measure performance
struct performance{
  char filename[13]; // longest name has 12 chars + null
  int digits; // initial digits
  int reps; // calls to solve_board
  int mmreps; // calls to make_move
  int duration; // solve_board running time
};

// Task 1: is_complete function 
bool is_complete(const char board[9][9]);

// Task 2: make_move function
bool make_move(const char *position, const char digit, char board[9][9]); 
// Helper function for make_move
bool check_valid(int r, int c, const char digit, const char board[9][9]);

// Task 3: save_board function
bool save_board(const char *filename, const char board[9][9]);

// Task 4: solve_board function
bool solve_board(char board[9][9]);

//Task 5: helper functions to measure difficulty
int count_digits(const char board[9][9]);
void record_diff(performance *x);
void display_performance(performance *x);
void table_header();
void table_footer();

#endif
