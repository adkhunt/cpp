#include<iostream>
#include<vector>

using namespace std;

typedef struct tree_node{
	int data;
	struct tree_node *left, *right;

	tree_node(int i){
		data = i;
		left = NULL;
		right = NULL;
	}
} tree_node;

typedef struct ll_node{
	int data;
	struct ll_node *next;

	ll_node(int i){
		data = i;
		next = NULL;
	}
} ll_node;

int getTreeHeight(tree_node *root){

	if (root == NULL){
		return 0;
	}

	int lh = getTreeHeight(root->left) + 1;
	int rh = getTreeHeight(root->right) + 1;

	return lh > rh ? lh : rh;
}

void create_ll(tree_node *root, int cur_level, vector<ll_node*> &res,
					vector<ll_node*> &last_visited){

	if (root == NULL){
		return;
	}

	if (res[cur_level] != NULL){
		last_visited[cur_level]->next = new ll_node(root->data);
		last_visited[cur_level] = last_visited[cur_level]->next;
	} else{
		res[cur_level] = new ll_node(root->data);
		last_visited[cur_level] = res[cur_level];
	}

	create_ll(root->left, cur_level+1, res, last_visited);
	create_ll(root->right, cur_level+1, res, last_visited);
}

vector<ll_node*> create_ll_from_bt_level(tree_node *root){

	int treeHeight = getTreeHeight(root);
	vector<ll_node*> res(treeHeight, NULL), last_visited(treeHeight, NULL);
	create_ll(root, 0, res, last_visited);
	return res;
}

void print_list(ll_node *hptr){
	while(hptr){
		cout << hptr->data << " ";
		hptr = hptr->next;
	}
	cout << endl;
}

int main(){

	tree_node *root = new tree_node(1);
	root->left = new tree_node(2);
	root->right = new tree_node(3);
	root->left->left = new tree_node(4);
	root->left->right = new tree_node(5);
	root->right->left = new tree_node(6);
	root->right->right = new tree_node(7);
	root->left->left->left = new tree_node(8);
	root->left->left->right = new tree_node(9);
	root->left->right->left = new tree_node(10);
	root->left->right->right = new tree_node(11);
	root->right->left->left = new tree_node(12);
	root->right->left->right = new tree_node(13);

	vector <ll_node*> res = create_ll_from_bt_level(root);

	for (auto i : res){
		print_list(i);
	}

	return 0;
}
