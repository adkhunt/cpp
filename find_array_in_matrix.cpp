#include<iostream>
#include<vector>

using namespace std;

#define ROW 4
#define COL 5

typedef struct res{

	pair<int, int> start_index;
	pair<int, int> end_index;
	bool isFound;
} result;

void BFS(vector<vector<int>> mat, int row_size, int col_size,
			int cur_row, int cur_col, vector<int> array,
			int index, result &res, vector<vector<bool>> isVisited){

	if (cur_row >= row_size || cur_col >= col_size ||
		 cur_row < 0 || cur_col < 0){
		res.isFound = false;
		return;
	}

	if (index == array.size()-1){
		res.end_index.first = cur_row;
		res.end_index.second = cur_col;
		res.isFound = true;
		return;
	}

	if (isVisited[cur_row][cur_col]){
		res.isFound = false;
		return;
	}

	isVisited[cur_row][cur_col] = true;
	vector<pair<int, int>> neighbours = {{-1, 0},
													 {0, 1},
													 {1, 0},
													 {0, -1}};

	int row_to_explore, col_to_explore;
	for (auto i : neighbours){
		row_to_explore = cur_row + i.first;
		col_to_explore = cur_col + i.second;
		if (row_to_explore >= 0 && col_to_explore >= 0 &&
			 row_to_explore < row_size && col_to_explore < col_size){
			if(mat[row_to_explore][col_to_explore] == array[index+1] &&
				!isVisited[row_to_explore][col_to_explore]){
				BFS(mat, row_size, col_size, row_to_explore, col_to_explore,
					 array, index+1, res, isVisited);
				if (res.isFound){
					return;
				}
			}
		}
	}
}

result findArrayInMat(vector<vector<int>> mat, int row,
							 int col, vector<int> array){

	result res = {.isFound = false};
	for (int i = 0 ; i < row ; ++i){
		for(int j = 0 ; j < col ; ++j){
			if (mat[i][j] == array[0]){
				vector<vector<bool>> isVisited(row, vector<bool> (col, false));
				BFS(mat, row, col, i, j, array, 0, res, isVisited);

				if (res.isFound){
					res.start_index.first = i;
					res.start_index.second = j;
					return res;
				}
			}
		}
	}

	return res;
}

int main(){

	vector<vector<int>> matrix = {{1, 2, 3, 5, 8},
											{6, 5, 10, 22, 47},
											{20, 21, 1, 47,33},
											{45, 8, 6, 5, 1}};

	vector<int> array = {1, 10, 22, 47, 33, 47};

	result res = findArrayInMat(matrix, ROW, COL, array);

	if (res.isFound){
		cout << "Start index = " << res.start_index.first << ", " <<
				res.start_index.second << endl << "End Index = " <<
				res.end_index.first << ", " << res.end_index.second << endl;
	} else{
		cout << "Array is not present in matrix." << endl;
	}

	return 0;
}
