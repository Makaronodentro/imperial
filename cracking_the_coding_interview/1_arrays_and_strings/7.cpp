/* 1.7 | Rotate Matrix
 * -----------------------------------------------------------------------------
 * Desc  : given a NxN image, rotate it 90 degrees clockwise. Do it in place.
 *
 * Notes : Avoid multiple concatenations as they are inefficient.
 */

#include <bitset>
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

void createMatrix(int***, int);

void rotateMatrix(int**, int n);

int main(int argc, char* argv[]){

  int n = 5;

  int** matrix;

  createMatrix(&matrix, n);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cout<<setw(2)<<matrix[i][j]<<" ";
    }
    cout<<endl;
  }

  for(int i = 0; i < n; i++){
    cout<<"---";
  }
  cout<<endl;

  rotateMatrix(matrix, n);

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

void rotateMatrix(int** matrix, int n){
  for(int layer = 0; layer < n / 2; layer++){
    int first = layer;
    int last = n - layer - 1;
    for(int i = first; i < last; i++){

      int offset = i - first;

      // get top
      int top = matrix[first][i];
      // Set top = left
      matrix[first][i] = matrix[last - offset][first];
      // Set left  = bottom
      matrix[last - offset][first] = matrix[last][last - offset];
      // Set bottom  =  right
      matrix[last][last - offset] = matrix[i][last];
      // Set right = top
      matrix[i][last] = top;
    }
  }
}
