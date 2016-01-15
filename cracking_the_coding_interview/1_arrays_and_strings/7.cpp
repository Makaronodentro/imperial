/* 1.7 | Rotate Matrix
 * -----------------------------------------------------------------------------
 * Desc  : given a NxN image, rotate it 90 degrees. Do it in place.
 *
 * Notes : Avoid multiple concatenations as they are inefficient.
 */

#include <bitset>
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

void createMatrix(int***, int);

void rotateMatrix(int**);

int main(int argc, char* argv[]){

  int n = 9;

  int** matrix;

  createMatrix(&matrix, n);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cout<<setw(2)<<matrix[i][j]<<" ";
    }
    cout<<endl;
  }

  rotateMatrix(matrix);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cout<<setw(2)<<matrix[i][j]<<" ";
    }
    cout<<endl;
  }

  for(int i = 0; i < n; i++){
    delete matrix[i];
  }

  delete [] matrix;

  return 0;
}

void createMatrix(int*** m, int n){
  int** temp = (int**)malloc(n * sizeof(int*));
  *m = temp;

  for(int i = 0; i < n; i++){
    temp[i] = new int[n];
  }

  int k = 1;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      temp[i][j] = k++;
    }
  }
}

void rotateMatrix(int** m){

}
