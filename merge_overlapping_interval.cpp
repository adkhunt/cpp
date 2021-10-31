#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<utility>
using namespace std;

bool compare(pair<int, int> p1, pair<int, int> p2){
	return p1.first < p2.first;
}

void mergeIterval(vector<pair<int, int>> interval){

	if (interval.size() <= 0){
		cout << "Given interval array is empty." << endl;
		return;
	}

	sort(interval.begin(), interval.end(), compare);

	pair<int, int> temp = interval[0];
	for (int i = 1 ; i < interval.size() ; ++i){
		if (temp.second < interval[i].second){
			temp.second = interval[i].second;
		} else{
			cout << temp.first << " " << temp.second << endl;
			temp = interval[i];
		}
	}
}

int main(){

	vector<pair<int,int>> intervals = { {6,8}, {1,9}, {2,4}, {4,7}, {2, 12} };
	mergeIterval(intervals);

	return 0;
}
