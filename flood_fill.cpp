#include<iostream>
#include<queue>
#include<vector>

using namespace std;

bool isValidPixel(int cur_row, int cur_col,
                  int row_size, int col_size){

   if (cur_row < 0 || cur_row >= row_size ||
       cur_col < 0 || cur_col >= col_size){
      return false;
   }

   return true;
}

void flood_fill(vector<vector<int>> &pixels,
                pair<int,int> location,
                int new_colour){

   if (pixels.empty() || pixels[0].empty()){
      return;
   }

   int row_size = pixels.size();
   int col_size = pixels[0].size();

   if (!isValidPixel(location.first, location.second,
        row_size, col_size)){
      cout << "Given location is out of matrix." << endl;
      return;
   }

   int old_colour = pixels[location.first][location.second];
   queue<pair<int, int>> q;
   q.push(location);
   vector<pair<int, int>> directions = {{-1, -1}, {-1, 0}, {-1, 1},
                                        {0, -1}, {0, 1}, {1, -1},
                                        {1, 0}, {1, 1}};

   while (!q.empty()){
      location = q.front();
      q.pop();
      int cur_x = location.first;
      int cur_y = location.second;

      // fill current location with new colour.
      pixels[cur_x][cur_y] = new_colour;

      // Check all eight directions.
      for (auto i : directions){
         int x = cur_x + i.first;
         int y = cur_y + i.second;
         if (isValidPixel(x, y, row_size, col_size) &&
             pixels[x][y] == old_colour){
            q.push(make_pair(x, y));
         }
      }
   }
}

void print_screen(vector<vector<int>> pixels){

   for (auto i : pixels){
      for (auto j : i){
         cout << j << " ";
      }
      cout << endl;
   }
}

int main(){

   vector<vector<int>> pixels = {{1, 1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1, 0, 0},
                                 {1, 0, 0, 1, 1, 0, 1, 1},
                                 {1, 2, 2, 2, 2, 0, 1, 0},
                                 {1, 1, 1, 2, 2, 0, 1, 0},
                                 {1, 1, 1, 2, 2, 2, 2, 0},
                                 {1, 1, 1, 1, 1, 2, 1, 1},
                                 {1, 1, 1, 1, 1, 2, 2, 1}};

   int row, col;
   int new_colour;

   cout << "Enter the location of pixels." << endl;
   cin >> row;
   cin >> col;

   pair<int, int> location = make_pair(row, col);

   cout << "Enter new colour to replace." << endl;
   cin >> new_colour;

   print_screen(pixels);
   flood_fill(pixels, location, new_colour);
   cout << "Screen after flood fill" << endl;
   print_screen(pixels);
   return 0;
}
