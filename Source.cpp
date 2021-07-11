#include <iostream>
#include <unordered_set>

using namespace std;

//functions which takes in an int array, 
//finds an int a in the array s.t. a+b = sum
//where b is in the array. Returns -1 if it fails.
//
//naive implementation
void pairs_naive(int* p, int len, int sum) {
	int i = 0;
	int j = 1;
	for (i = 0; i < len - 1; i++) {
		for (j = i+1; j < len; j++) {
			if (p[i] + p[j] == sum) {
				cout << p[i] << " and " << p[j] << " sum to " << sum << endl;
				return;
			}
		}
	}
	cout << "no pair summing to " << sum << " found" << endl;
}

//sorts p and then performs binary search to find the complement
//void pairs_sort(int* p, int len, int sum) {}

//uses an unordered set to do the pairs in linear time
void pairs_unordered_set(int *p,int len, int sum) {
	
	unordered_set<int> values_so_far;
	//this is the return type of uset.find
	unordered_set<int>::const_iterator iter;
	int complement = 0;
	for (int i = 0; i < len; i++) {
		//value which sums with p[i] to be sum
		complement = sum - p[i];
		iter = values_so_far.find(complement);
		//if its complement is not in the set, add p[i]
		if (iter == values_so_far.end()) {
			values_so_far.insert(p[i]);
		}
		else {
			cout << p[i] << " and " << complement << " sum to " << sum << endl;
			return;
		}
	}
	cout << "no elements sum to " << sum << endl;
	
}


int main() {
	int x[] = { 1,7,3,4,12 };
	//get the length of x 
	int len = sizeof(x) / sizeof(x[0]);
	cout << "x is " << len << " ints long" << endl;
	int sums[]{ 7,0,13,10};
	int pair0 = 0;
	int lensums = sizeof(sums) / sizeof(sums[0]);
	for (int i = 0; i < lensums; i++) {
		pairs_unordered_set(x, len, sums[i]);
	}
	return 0;
}





