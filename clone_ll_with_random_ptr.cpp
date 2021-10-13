#include<iostream>
#include<map>

using namespace std;

typedef struct ll_node{
	int data;
	struct ll_node *next, *random;

	ll_node(int i){
		data = i;
		next = NULL;
		random = NULL;
	}

} ll_node;

ll_node* get_new_node(int data){

	ll_node *new_node = new ll_node(data);
	return new_node;
}

ll_node* create_clone(ll_node *hptr){

	if (hptr == NULL){
		return NULL;
	}

	map<ll_node*, ll_node*> hashTable;
	ll_node *temp = hptr;

	while(temp){
		hashTable[temp] = get_new_node(temp->data);
		temp = temp->next;
	}

	temp = hptr;
	ll_node *_clone = NULL;

	while(temp){
		_clone = hashTable[temp];
		_clone->next = temp->next ? hashTable[temp->next] : NULL;
		_clone->random = temp->random ? hashTable[temp->random] : NULL;
		temp = temp->next;
	}

	return hashTable[hptr];
}

void print_ll(ll_node *hptr){

	while(hptr){
		cout << "cur : " << hptr << ", data: " << hptr->data << ", Next: " << hptr->next <<
				", Random: " << hptr->random <<endl;
		hptr = hptr->next;
	}
}

int main(){

	ll_node *hptr = get_new_node(1);
	hptr->next = get_new_node(2);
	hptr->next->next = get_new_node(3);
	hptr->next->next->next = get_new_node(4);
	hptr->next->next->next->next = get_new_node(5);

	hptr->random = hptr->next->next;
	hptr->next->random = hptr;
	hptr->next->next->random = hptr->next->next->next;
	hptr->next->next->next->random = hptr->next->next->next->next;
	hptr->next->next->next->next->random = hptr->next;

	print_ll(hptr);
	ll_node *new_hptr = create_clone(hptr);
	cout << "\n================================\n";
	print_ll(new_hptr);

	return 0;
}
