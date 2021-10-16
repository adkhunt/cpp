#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<set>

using namespace std;

bool DFS(char cur_package, map<char, vector<char>> graph,
			set<char> &isVisited, vector<char> &result){

	if (find(result.begin(), result.end(), cur_package) != result.end()){
		return true;
	}

	if (isVisited.size() != 0 &&
		 isVisited.find(cur_package) != isVisited.end()){
		cout << "Depedency found for node : " << cur_package << endl;
		return false;
	}

	if (graph[cur_package].size() == 0){
		result.push_back(cur_package);
		return true;
	}

	isVisited.insert(cur_package);
	for (auto j : graph[cur_package]){
		auto it = find(result.begin(), result.end(), j);
		if (it == result.end()){
			bool res = DFS(j, graph, isVisited, result);
			if (!res){
				return res;
			}
		}
	}

	result.push_back(cur_package);
	return true;
}

vector<char> resolve_dep(map<char, vector<char>> graph){

	set<char> isVisited;
	vector<char> result;

	for (auto i : graph){
		bool res = DFS(i.first, graph, isVisited, result);
		if (!res){
			return vector<char>();
		}
	}

	return result;
}

int main(){

	map<char, vector<char>> graph;
	graph.insert(pair<char, vector<char>>('a', {'b', 'c'}));
	graph.insert(pair<char, vector<char>>('b', {'e', 'f'}));
	graph.insert(pair<char, vector<char>>('c', {'o', 'e'}));
	graph.insert(pair<char, vector<char>>('d', {'b'}));
	graph.insert(pair<char, vector<char>>('e', {'o', 'm'}));
	graph.insert(pair<char, vector<char>>('f', {'o'}));
	graph.insert(pair<char, vector<char>>('m', {}));
	graph.insert(pair<char, vector<char>>('o', {}));

	vector<char> result = resolve_dep(graph);
	for (auto i : result){
		cout << i << ",";
	}
	cout << endl;

	return 0;
}
