#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<utility>
#include<algorithm>

using namespace std;

typedef struct position{
	pair<int, int> start;
	pair<int, int> end;
} position;

map<char, pair<int, int>> direction = {{'r', make_pair(0, 1)},
											            		{'l', make_pair(0, -1)},
									             				{'u', make_pair(-1, 0)},
								            					{'d', make_pair(1, 0)}};

bool DFS(vector<vector<int>> mat, int row_size, int col_size,
			vector<vector<bool>> &isVisited, char dir,
			position &cord, int x, int y, bool &isFound){

	if (x < 0 || y < 0  || x >= row_size || y >= col_size
		 || mat[x][y] == 1 || isVisited[x][y]){
		return false;
	}

	if (x == cord.end.first && y == cord.end.second){
		isFound = true;
		return true;
	}

	isVisited[x][y] = true;
	if (!isFound){
		pair<int, int> next_cord = direction[dir];
		x += next_cord.first;
		y += next_cord.second;
		// Continue in given direction.
		bool ret = DFS(mat, row_size, col_size, isVisited,
						   dir, cord, x, y, isFound);
		x -= next_cord.first;
		y -= next_cord.second;
		if (!ret){
			// Change direction and explore all other direction.
			string dirs = "rlud";
			for (int i = 0 ; i < dirs.length() ; ++i){
				next_cord = direction[dirs[i]];
				x += next_cord.first;
				y += next_cord.second;
				DFS(mat, row_size, col_size, isVisited, dirs[i],
					 cord, x, y, isFound);
				x -= next_cord.first;
				y -= next_cord.second;
			}
		}
	}

	return false;
}

bool canReachToTarget(vector<vector<int>> mat, position cord){

	int row_size = mat.size();
	int col_size = mat[0].size();

	if (cord.start.first < 0 || cord.start.first >= row_size || 
		 cord.start.second < 0 || cord.start.second >= col_size ||
		 cord.end.first < 0 || cord.end.first >= row_size ||
		 cord.end.second < 0 || cord.end.second >= col_size){
		return false;
	}

	vector<vector<bool>> isVisited(row_size, vector<bool>(col_size, false));
	bool isFound = false;

	DFS(mat, row_size, col_size, isVisited, 'r', cord, cord.start.first,
		 cord.start.second, isFound);
	return isFound;
}

int main(){

	vector<vector<int>> mat = {{1, 1, 0, 0},
									        	{1, 0, 0, 0},
							        			{1, 0, 1, 1},
						        				{1, 0, 0, 0}};
	position cords;
	cords.start = make_pair(0, 3);
	cords.end = make_pair(3, 3);

	bool res = canReachToTarget(mat, cords);

	if (res){
		cout << "Path exist from start to end." << endl;
	} else{
		cout << "Path doesn't exist to target." << endl;
	}

	return 0;
}
