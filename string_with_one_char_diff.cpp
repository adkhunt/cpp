#include<iostream>
#include<vector>

using namespace std;

vector<string> string_with_one_char_diff(vector<string> strs, string target){

	vector<string> res;

	if (strs.empty()){
		cout << "Given list of string is empty." << endl;
      return res;
	}

	for (auto cur_str : strs){
		int count = 0;
		if (cur_str.size() != target.size()){
			continue;
		}

		for (int i = 0 ; i < target.size() ; ++i){
			if (cur_str[i] != target[i]){
				++count;
			}

			if (count > 1){
				break;
			}
		}

		if (count == 1){
			res.emplace_back(cur_str);
		}
	}

	return res;
}

void print_vector(vector<string> res){

	for (auto i : res){
		cout << i << endl;
	}
}

int main(){

	vector<string> strs = {"tip", "top", "hop", "dog", "gog", "cop", "hip", "sip", "tog"};
   string cur_str;

	cout << "Enter string to search." << endl;
	cin >> cur_str;

	vector<string> res = string_with_one_char_diff(strs, cur_str);

	print_vector(res);

	return 0;
}
