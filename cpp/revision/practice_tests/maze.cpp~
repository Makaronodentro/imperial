#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}


bool find_marker(char ch, char **m, int height, int width, int &row, int &col){
	
	for(row = 0; row < height; row++){
		for(col = 0; col < width; col++){
			if(m[row][col] == ch) return true; 
		}	
	}

	row = col = -1;

	return false;
}

bool check_move(char** maze, int height, int width, char dir, int &row, int &col){
	
	char validCh[5] = ">X M";

	// perform the step
	switch (dir){
	  case 'N':
	    row -= 1;
	    break;
	  case 'E':
	    col += 1;
	    break;
	  case 'S':
	    row += 1;
	    break;
	  case 'W':
	    col -= 1;
	    break;
	  default:
	    return false;
	}

	// Check boundaries to avoid segfaults
	if(row < 0 || row >= height) return false;
	if(col < 0 || col >= width) return false;

	// Check character at position
	for(int i = 0; i < 4; i++){
		if(maze[row][col] == validCh[i]) return true;	
	}

	return false;
}

bool valid_solution(const char* path, char **maze, int height, int width){
	int row, col;
	
	// get initial position
	if(!find_marker('>',maze,height,width,row,col)) return false;		

	// loop through the path
	while(path[0]){
		if(!check_move(maze, height, width, path[0], row, col)) return false;
		
		path++;
	}

	// Check if exit is at row col
	return (maze[row][col] == 'X');
}

bool recursive_path(char **m, int height, int width, int &row, int &col, char* path, char end){
  int tempRow, tempCol;
  char tempCh, directions[5] = {'N','E','S','W','\0'};
  
  //base case
  if (m[row][col] == end){
    m[row][col] = '#';
    *path = '\0';
    return true;
  }
    
  //loop directions
  for (int i = 0; i<4; i++){

    // save temporary values
    tempRow = row;
    tempCol = col;
    tempCh = m[row][col];

    // record route
    m[row][col] = '#';

    // check move allowavle then check onward route
    if (check_move(m,height,width,directions[i],row,col)){      
      if (recursive_path(m,height,width,row,col,path+1,end)){
	*path = directions[i];
	return true;
      }
    }

    //If no route revert temporary values
    row = tempRow;
    col = tempCol;
    m[row][col] = tempCh;
  }

  //if no direction exists return false
  return false;
}

const char* find_path(char **maze, int height, int width, char start, char end){
	int row, col;
	int rowEnd, colEnd;

	static char path[512] = "";

	// get initial position
	if(!find_marker(start,maze,height,width,row,col)) return "0";
	if(!find_marker(end,maze,height,width,rowEnd,colEnd)) return "0";

	if(!recursive_path(maze, height, width, row, col, path, end)) return "0";

	return path;
}
