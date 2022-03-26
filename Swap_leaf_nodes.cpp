#include<iostream>
#include<vector>

using namespace std;

struct node{
	int data;
	node *left, *right;

	node(int num){
		this->data = num;
		this->left = NULL;
		this->right = NULL;
	}
};

node* get_new_node(int num){

	return new node(num);
}

node* get_complete_tree(void){

	node *root = get_new_node(1);
	root->left = get_new_node(2);
	root->right = get_new_node(3);
	root->left->left = get_new_node(4);
	root->left->right = get_new_node(5);
	root->left->left->left = get_new_node(8);
	root->left->left->right = get_new_node(9);
	root->left->right->left = get_new_node(10);
	root->left->right->right = get_new_node(11);
	root->right->left = get_new_node(6);
	root->right->left->left = get_new_node(12);
	root->right->left->right = get_new_node(13);
	root->right->right = get_new_node(7);
	root->right->right->left = get_new_node(14);
	root->right->right->right = get_new_node(15);

	return root;
}

bool is_leaf_node(node *root){
	if (root->left == NULL && root->right == NULL){
		return true;
	}

	return false;
}

void print_tree_with_addr(node *root){

	if (root == NULL){
		return;
	}

	bool leaf = is_leaf_node(root);
	cout << root << " - " << root->data << ", leaf = " << leaf << endl;
	print_tree_with_addr(root->left);
	print_tree_with_addr(root->right);
}

void fill_node_array(node *root, vector<node*> &arr){

	if (root == NULL){
		return;
	}

	fill_node_array(root->left, arr);
	arr.emplace_back(root);
	fill_node_array(root->right, arr);
}

node* construct_tree_from_arr(vector<node*> arr, int start, int end){

	if (start > end){
		return NULL;
	}

	int mid = (start+end)/2;
	cout << "Start = " << start << ", End = " << end << ", Root = " << arr[mid]->data << endl;

	node *root = arr[mid];
	root->left = construct_tree_from_arr(arr, start, mid-1);
	root->right = construct_tree_from_arr(arr, mid+1, end);

	return root;
}

node* swap_leaf_nodes(node *root){

	vector<node*> arr;
	fill_node_array(root, arr);

	if (arr.empty()){
		return NULL;
	}

	for(int i = 1 ; i < arr.size() ; i+=2){
		node *temp = arr[i-1];
		arr[i-1] = arr[i];
		arr[i] = temp;
	}

	return construct_tree_from_arr(arr, 0, arr.size()-1);
}

int main(){

	node *root = get_complete_tree();
	print_tree_with_addr(root);
	node *new_root = swap_leaf_nodes(root);
	cout << "After Swap" << endl;
	print_tree_with_addr(new_root);

	return 0;
}
