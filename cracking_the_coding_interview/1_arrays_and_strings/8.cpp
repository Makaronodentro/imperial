/* 1.8 | Zero Matrix
 * -----------------------------------------------------------------------------
 * Desc  : given a MxN image, if an el is zero, set entire row and col to zero
 *
 * Notes : Read first, zero after. Doesn't work otherwise!
 *         Keep track only of rows and col, not individual cells
 */

#include <bitset>
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

void createMatrix(int***, int, int);

void zeroMatrix(int**, const int, const int);

int main(int argc, char* argv[]){

  int m = 5, n = 5;

  int** matrix;

  createMatrix(&matrix, m, n);

  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      cout<<setw(2)<<matrix[i][j]<<" ";
    }
    cout<<endl;
  }

  for(int i = 0; i < n; i++){
    cout<<"---";
  }
  cout<<endl;

  zeroMatrix(matrix, m, n);

  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      cout<<setw(2)<<matrix[i][j]<<" ";
    }
    cout<<endl;
  }

  for(int i = 0; i < m; i++){
    delete matrix[i];
  }

  delete [] matrix;

  return 0;
}

void createMatrix(int*** matrix, int m, int n){
  int** temp = (int**)malloc(m * sizeof(int*));
  *matrix = temp;

  for(int i = 0; i < m; i++){
    temp[i] = new int[n];
  }

  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      temp[i][j] = rand() % 5;
    }
  }
}

void zeroMatrix(int** matrix, const int m, const int n){

  int rows[m];
  int cols[n];

  // determine where the zeroes are
  for(int r = 0; r < m; r++){
    for(int c = 0; c < n; c++){
      if(matrix[r][c] == 0){
          rows[r] = 1;
          cols[c] = 1;
      }
    }
  }

  // Set marked rows to zero
  for(int r = 0; r < m; r++){
    if(rows[r] == 1){
      for(int c = 0; c < n; c++){
        matrix[r][c] = 0;
      }
    }
  }

  // Set marked cols to zero
  for(int c = 0; c < n; c++){
    if(cols[c] == 1){
      for(int r = 0; r < m; r++){
        matrix[r][c] = 0;
      }
    }
  }

  return;
}
