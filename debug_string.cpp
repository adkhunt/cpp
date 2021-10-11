#include<iostream>

using namespace std;

void decode_string(string encoded_string, int row_size){

	if (row_size == 0 || encoded_string.length() == 0){
		cout << "Row size can't be zero." << endl;
	}

	int col_size = encoded_string.length()/row_size;
	int jump_size = col_size + 1;

	for (int i = 0 ; i < col_size ; ++i){
		int j = i, counter = 1;
		while(j < encoded_string.length()){
			cout << encoded_string[j];
			j += (counter*jump_size);
		}
	}

	cout << endl;
}

int main(){

	string str = "mnes--ya-----mi";
	decode_string(str, 3);

	return 0;
}
