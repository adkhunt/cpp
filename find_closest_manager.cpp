#include<iostream>
#include<vector>
using namespace std;

typedef struct emp_detail{
	string emp_name;
	int emp_id;
	vector<emp_detail*> child;

	emp_detail(string name, int id){
		emp_name = name;
		emp_id = id;
	}
} emp_detail;

class Hierarchy{

	private:
		emp_detail *root;

		void find_util(emp_detail *cur_emp, vector<emp_detail*> &path,
							int reporter_id, bool &isFound){
			if (cur_emp == NULL || isFound){
				return;
			}

			path.push_back(cur_emp);
			if (cur_emp->emp_id == reporter_id){
				isFound = true;
			}

			for (auto i : cur_emp->child){
				find_util(i, path, reporter_id, isFound);
				if (isFound){
					break;
				}
				path.pop_back();
			}
		}

		void print_recur(emp_detail *cur_emp){
			if (cur_emp == NULL){
				return;
			}

			cout << "Manager : " << cur_emp->emp_name << endl;

			for (auto i : cur_emp->child){
				cout << i->emp_name << ", ";
			}

			cout << endl;
			for (auto i : cur_emp->child){
				print_recur(i);
			}
		}

	public:
		Hierarchy(string name, int id){
			root = new emp_detail(name, id);
		}

		void add_emp(int reporter_id, string cur_emp, int cur_id){
			vector<emp_detail*> path;
			bool isFound = false;
			find_util(root, path, reporter_id, isFound);
			if (path.size() == 0){
				cout << "No reporter found with id : " << reporter_id << endl;
				return;
			}

			emp_detail *reporter = path.back();
			emp_detail *new_emp = new emp_detail(cur_emp, cur_id);
			(reporter->child).push_back(new_emp);
		}

		void print_hierarchy(void){
			print_recur(root);
		}

		emp_detail* find_closest_manager(int emp_id1, int emp_id2){
			vector<emp_detail*> path1, path2;
			bool isFound = false;
			find_util(root, path1, emp_id1, isFound);
			isFound = false;
			find_util(root, path2, emp_id2, isFound);

			for (auto i : path1){
				cout << i->emp_id << " ";
			}
			cout << endl;

			for (auto i : path2){
				cout << i->emp_id << " ";
			}
			cout << endl;

			emp_detail *pre = NULL;

			for (int i = 0 ; i < path1.size() && i < path2.size() ; ++i){
				if (path1[i] != path2[i]){
					return pre;
				}
				pre = path1[i];
			}

			return pre;
		}
};

int main(){

	Hierarchy obj = Hierarchy("abc", 1);

	obj.add_emp(1, "def", 2);
	obj.add_emp(1, "gho", 3);
	obj.add_emp(1, "ijn", 4);
	obj.add_emp(1, "kl", 5);
	obj.add_emp(2, "mn", 6);
	obj.add_emp(6, "op", 7);
	obj.add_emp(6, "qr", 8);
	obj.add_emp(2, "st", 9);
	obj.add_emp(3, "uv", 10);
	obj.add_emp(3, "wx", 11);
	obj.add_emp(10, "yz", 12);
	obj.add_emp(11, "ab", 13);
	obj.add_emp(4, "bc", 14);
	obj.add_emp(4, "cd", 15);
	obj.add_emp(5, "ef", 16);
	obj.add_emp(8, "gh", 17);
	obj.add_emp(14, "ij", 18);

	emp_detail *common_manager = obj.find_closest_manager(12, 13);

	if (common_manager){
		cout << "Common closest managet : " << common_manager->emp_name
			<< ", " << common_manager->emp_id << endl;
	} else{
		cout << "No common manager found." << endl;
	}

	return 0;
}
