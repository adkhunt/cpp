/*
 * Write a function that finds anyone who badged into the room three or more
 * times in a one-hour period. Your function should return each of the
 * employees who fit that criteria, plus the times that they badged in during
 * the one-hour period. If there are multiple one-hour periods where this was
 * true for an employee, just return the earliest one for that employee.
**/

#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

// Method which converts unsorted pairs to map which stores name and their
// access time in sorted order.
map<string, vector<int>> preprocess_data(vector<pair<string, string>> badge_times){

	map<string, vector<int>> processed_data;

	for (auto i : badge_times){
		processed_data[i.first].push_back(stoi(i.second));
	}

	for (auto i : processed_data){
		// Skip those entries whose length is less then 3.
		if (i.second.size() < 3){
			processed_data.erase(i.first);
			continue;
		}
		vector<int> temp = i.second;
		sort(temp.begin(), temp.end());
		processed_data[i.first] = temp;
	}

	return processed_data;
}

map<string, vector<int>> get_eligible_emp(vector<pair<string, string>> badge_times){

	map<string, vector<int>> processed_data = preprocess_data(badge_times);
	map<string, vector<int>> result;

	for (auto i : processed_data){
		int start_index = 0, end_index = 2;
		bool is_found = false;
		while(end_index < i.second.size()){
			if (i.second[start_index] + 100 >= i.second[end_index]){
				++end_index;
				is_found = true;
			} else if (!is_found){
				++start_index;
				end_index = start_index + 2;
			} else {
				break;
			}
		}
	
		if(is_found){
			vector<int> res;
			for (int it = start_index ; it < end_index ; ++it){
				res.push_back(i.second[it]);
			}
			result[i.first] = res;
		}
	}

	return result;
}

int main(){

	vector<pair<string, string>> badge_times = {
    		{"Paul", "1355"}, {"Jennifer",  "1910"}, {"Jose",    "835"},
		{"Jose",       "830"}, {"Paul",      "1315"}, {"Chloe",     "0"},
		{"Chloe",     "1910"}, {"Jose",      "1615"}, {"Jose",   "1640"},
		{"Paul",      "1405"}, {"Jose",       "855"}, {"Jose",    "930"},
		{"Jose",       "915"}, {"Jose",       "730"}, {"Jose",    "940"},
		{"Jennifer",  "1335"}, {"Jennifer",   "730"}, {"Jose",   "1630"},
		{"Jennifer",     "5"}, {"Chloe",     "1909"}, {"Zhang",     "1"},
 		{"Zhang",       "10"}, {"Zhang",      "109"}, {"Zhang",   "110"},
		{"Amos",         "1"}, {"Amos",         "2"}, {"Amos",    "400"},
		{"Amos",       "500"}, {"Amos",       "503"}, {"Amos",    "504"},
		{"Amos",       "601"}, {"Amos",       "602"}
	};

	map<string, vector<int>> result = get_eligible_emp(badge_times);

	for (auto i : result){
		cout << i.first << ": ";
		for (auto j : i.second){
			cout << j << " ";
		}
		cout << endl;
	}

	return 0;
}
