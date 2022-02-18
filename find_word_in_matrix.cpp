/*
What is the longest word in the board, starting at any position, using each tile a maximum of one time?

board = {{"A", "B", "C"},
         {"X", "O", "T"},
         {"Y", "Z", "P"}}

dictionary = string["AXY", "BOX", "BOXY", "CTPZ"]
Constraints: You can traverse matrix in four direction,
			    up, down, left, right.

Output: BOXYZ
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isPresent(vector<string> dictionary, string word){
	for (auto curr_word : dictionary){
		if (curr_word == word){
			return true;
		}
	}
	return false;
}

void TraverseBoard(vector<vector<char>> board, vector<string> dictionary, int row, int col,
		vector<vector<bool>> isVisited, string &temp, string &res){

	if (row < 0 || col < 0){
		return ;
	}

	if (row >= (int)board.size() || col >= (int)board[0].size()){
		return ;
	}

	if (isVisited[row][col]){
		return ;
	}

	isVisited[row][col] = true;
	temp.push_back(board[row][col]);

	if (isPresent(dictionary, temp)){
		if (temp.size() > res.size()){
			res = temp;
		}
	}

	TraverseBoard(board, dictionary, row + 1, col, isVisited, temp, res);
	TraverseBoard(board, dictionary, row, col + 1, isVisited, temp, res);
	TraverseBoard(board, dictionary, row - 1, col, isVisited, temp, res);
	TraverseBoard(board, dictionary, row, col - 1, isVisited, temp, res);

	temp.pop_back();
}

string getLongestWord(vector<vector<char>> board, vector<string> dictionary){

	if (board.empty()){
		return "";
	}

	int row_size = (int)board.size();
	int col_size = (int)board[0].size();
	int max_length = row_size*col_size;

	string result = "";

	for (int i = 0 ; i < row_size ; ++i){
		for (int j = 0 ; j < col_size ; ++j){
			vector<vector<bool>> isVisited(row_size, vector<bool>(col_size, false));
			string temp = "";
			/* scope for optimization,
			// If there is no string which starts with char at board[i][j],
			// Do not call this function and continue.
			*/
			TraverseBoard(board, dictionary, i, j, isVisited, temp, result);
		}
	}

	return result;
}

int main() {

	vector<vector<char>> board = {{'A', 'B', 'C'},
											{'X', 'O', 'T'},
											{'Y', 'Z', 'P'}};

	vector<string> dictionary = {"AXY", "BOX", "BOXYZ", "CTPZ"};

	string result = getLongestWord(board, dictionary);

	cout << "Longest Word : " << result << endl;

	return 0;
}
