#include<iostream>
#include<vector>

using namespace std;

class node{

	public:
		int data;
		node *left, *right;
		node(int data){
			this->data = data;
			this->left = NULL;
			this->right = NULL;
		}
};

class tree{

	private:
		node *_root;
		node* get_new_node(int data){
			return new node(data);
		}

		void _print_tree(node *root){
			if (root == NULL){
				return;
			}

			_print_tree(root->left);
			cout << root->data << " ";
			_print_tree(root->right);
		}

		int _get_height(node *root){
			if(root == NULL)
				return 0;

			int lh = _get_height(root->left) + 1;
			int rh = _get_height(root->right) + 1;

			return lh > rh ? lh : rh;
		}

		int _print_leaf_util(node *root, vector<vector<int>> &res){
			if (root == NULL){
				return -1;
			}

			int lv = _print_leaf_util(root->left, res) + 1;
			int rv = _print_leaf_util(root->right, res) + 1;

			int max = lv > rv ? lv : rv;
			res[max].push_back(root->data);
			return max;
		}

	public:
		tree(){
			this->_root = NULL;
		}

		void prepare_tree(void){
			this->_root = get_new_node(1);
			this->_root->left = get_new_node(2);
			this->_root->right = get_new_node(3);
			this->_root->left->left = get_new_node(4);
			this->_root->left->right = get_new_node(5);
			this->_root->left->left->left = get_new_node(6);
		}

		void print_tree(void){
			_print_tree(this->_root);
			cout << endl;
		}

		int get_height(void){
			return _get_height(this->_root);
		}

		vector<vector<int>> print_leaf(void){
			int height = _get_height(this->_root);
			vector<vector<int>> res(height);

			_print_leaf_util(this->_root, res);
			return res;
		}
};

int main(){

	tree *root = new tree();
	root->prepare_tree();
	root->print_tree();
	vector<vector<int>> res = root->print_leaf();

	for (auto i : res){
		for (auto j : i){
			cout << j << " ";
		}
		cout << endl;
	}

	return 0;
}
