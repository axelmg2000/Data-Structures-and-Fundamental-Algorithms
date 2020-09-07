// Developed by: Axel Mercado Gasque
// Date: August 28th, 2020

/*--------------
You are handed a scenic black-and-white photo of the skyline of a city. The photo is n-pixels tall and m-pixels wide, and in the photo, buildings appear as black (pixel value 0) and sky background appears as white (pixel value 1). In any column, all the black pixels are below all the white pixels. In this problem, you will design an efficient algorithm that finds the location of a tallest building in the photo.
The input is an n × m matrix, where the buildings are represented with 0s, and the sky is represented by 1s. The output is an integer representing the location of a tallest building. For example, for the input 5 × 6 matrix below, a tallest building has height 5 and is in location 3 (assuming we are 0-indexing). Thus the output is 3.

| 1 1 1 0 1 1 |
| 1 1 0 0 0 1 |
| 0 1 0 0 0 1 |
| 0 1 0 0 0 1 |
| 0 0 0 0 0 1 |

a) Find and implement an algorithm that finds a tallest building in time O(mlog(n))
b) Find and implement an algorithm that finds a tallest building in time O(m + n)
----------------*/



// Declaration of utilized libraries
#include <iostream>
using namespace std;


// Code start

// 1. Algorithm that finds tallest building 
// Time Complexity: O(mlog(n))
template <size_t rows, size_t cols> 
int tallestBuildingEff(int (&matrix) [rows][cols]) {
  int firstColumnWithBuildingInCurrentRow = 0;
  bool currentRowHasBuildings = true;
  bool tallestBuildingFound = false;
  int delta = rows;
  int i = rows;  // current row (starting at the bottom)

  while (!tallestBuildingFound) {
    delta /= 2; if (delta < 1) delta = 1;
			if (currentRowHasBuildings) 
				i -= delta;
		  else 
				i += delta;

    currentRowHasBuildings = false;
			for (int j=0; j<cols; j++) {
				if (matrix[i][j] == 0) {
					firstColumnWithBuildingInCurrentRow = j;
					currentRowHasBuildings = true;
					if (i == 0 || matrix[i-1][j] == 1) {  // top of building found
						tallestBuildingFound = true; // if no other buildings present in this row
						for (int k=j+1; k<cols; k++) {
							if (matrix[i][k] == 0) {
								tallestBuildingFound = false; // there are still other buildings in same row    ...fails if two buildings are tallest of same height
							}
						}
					}
					break;
				}
			}
  }
  return firstColumnWithBuildingInCurrentRow;
}

// 2. Algorithm that finds tallest building (O(mn))
template <size_t rows, size_t cols> 
int tallestBuilding(int (&matrix) [rows][cols]) { // Matrix passed by reference; rows, cols previously declared
  int iLevels = 0, iCol = 0, iRow = rows - 1, iMax = 0, iPosition;
  bool conditionRow = true;
  bool conditionCol = true;

  while(conditionCol && iCol < cols) { // Loop through every column
    iLevels = 0; // Number of levels in every column starts at 0
    conditionRow = true; // Condition set true for every column
    iRow = rows - 1; // Index iRow set to last element to search from bottom to top

    while(conditionRow && iRow >= 0) { 
      if(matrix[iRow][iCol] == 0) {
        iLevels += 1; 
        --iRow;
      }
      else // If we find a 1 we exit the column loop
        conditionRow = false;
    }
    if(conditionRow) { // If condition is true, it means the entire column was 0s
      iPosition = iCol;
      conditionCol = false; // Exit the column loop
    } 
    else {
      if(iLevels > iMax) { // if 0s in current column is higher than the registered max
        // There is a new max, and the position is updated to current column
        iMax = iLevels;
        iPosition = iCol;
      }
    }

    ++iCol;
  }

  return iPosition;
}



int main() {

 int mat[5][6] = {{1,1,1,0,1,1}, {1,1,0,0,0,1}, {0,1,0,0,0,1}, {0,1,0,0,0,1}, {0,0,0,0,0,1}};

 cout << tallestBuildingEff(mat) << endl;
 cout << tallestBuilding(mat) << endl;
 
 

}
