#include<iostream>
#include<vector>
using namespace std;

int binary_search(vector<int> arr, int start, int end, int k){

	while(start<=end){
		int mid = (start+end)/2;

		if (arr[mid] == k){
			return mid;
		}

		if (arr[mid] > k){
			end = mid - 1;
		} else {
			start = mid + 1;
		}
	}

	return -1;
}

void print_k_nearest(vector<int> arr, int n, int k){

	int size = arr.size();

	if (k > size){
		cout << "K should be in range of array size." << endl;
		return;
	}

	int index = binary_search(arr, 0, size-1, n);

	if (index == -1){
		cout << "Given element is not present in array." << endl;
		return;
	}

	if (k == size){
		for (auto i : arr){
			cout << i << " ";
		}
		cout << endl;
		return;
	}

	int i = index - 1, j = index + 1;
	int left_diff, right_diff;

	while(k > 0){
		if (i < 0 && j < size){
			cout << arr[j] << " ";
			++j;
			goto CONTINUE;
		} else if (j >= size && i >= 0){
			cout << arr[i] << " ";
			--i;
			goto CONTINUE;
		}

		left_diff = arr[index] - arr[i];
		right_diff = arr[j] - arr[index];

		if (left_diff <= right_diff){
			cout << arr[i] << " ";
			--i;
		} else if (right_diff < left_diff){
			cout << arr[j] << " ";
			++j;
		}

		CONTINUE:
			--k;
  }

	cout << endl;
}

int main(){

	vector<int> arr = {1, 2, 4, 6, 7, 9, 10};
	int k, n;

	cout << "Enter value of n: ";
	cin >> n;

	cout << "Enter value of k: ";
	cin >> k;

	print_k_nearest(arr, n, k);

	return 0;
}
