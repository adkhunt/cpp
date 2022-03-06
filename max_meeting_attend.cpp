#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<pair<int, int>> find_max_meeting(vector<int> start_time, vector<int> end_time){

    vector<pair<int, int>> result;

    if (start_time.empty() || end_time.empty() ||
        (start_time.size() != end_time.size())){
        cout << "One of the array is empty." << endl;
        return result;
    }

    vector<pair<int, int>> meeting_data;

    for (int i = 0 ; i < start_time.size() ; ++i){
        meeting_data.emplace_back(make_pair(end_time[i], start_time[i]));
    }

    sort(meeting_data.begin(), meeting_data.end());
    int cur_Etime = meeting_data[0].first;
    result.emplace_back(make_pair(meeting_data[0].second, meeting_data[0].first));

    for (int i = 1 ; i < meeting_data.size() ; ++ i){
        if (meeting_data[i].second >= cur_Etime){
            result.emplace_back(make_pair(meeting_data[i].second, meeting_data[i].first));
            cur_Etime = meeting_data[i].first;
        }
    }

    return result;
}

int main(){

    vector<int> start_time = {1, 3, 0, 5, 8, 5};
    vector<int> end_time = {2, 4, 6, 7, 9, 9};

    vector<pair<int, int>> result = find_max_meeting(start_time, end_time);

    if (!result.empty()){
        cout << "Total " << result.size() << " meetings can be attended." << endl;
        for (auto i : result){
            cout << "Start time " << i.first << ", End time " << i.second << endl;
        }
    } else{
        cout << "No meetings can be attended." << endl;
    }

    return 0;
}
