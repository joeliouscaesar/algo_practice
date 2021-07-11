#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <chrono>
using namespace std;

////functions which takes in an int array, 
////finds an int a in the array s.t. a+b = sum
////where b is in the array. Returns -1 if it fails.
////
////naive implementation
//void pairs_naive(int* p, int len, int sum) {
//	int i = 0;
//	int j = 1;
//	for (i = 0; i < len - 1; i++) {
//		for (j = i+1; j < len; j++) {
//			if (p[i] + p[j] == sum) {
//				cout << p[i] << " and " << p[j] << " sum to " << sum << endl;
//				return;
//			}
//		}
//	}
//	cout << "no pair summing to " << sum << " found" << endl;
//}
//
////sorts p and then performs binary search to find the complement
////void pairs_sort(int* p, int len, int sum) {}
//
////uses an unordered set to do the pairs in linear time
//void pairs_unordered_set(int *p,int len, int sum) {
//	
//	unordered_set<int> values_so_far;
//	//this is the return type of uset.find
//	unordered_set<int>::const_iterator iter;
//	int complement = 0;
//	for (int i = 0; i < len; i++) {
//		//value which sums with p[i] to be sum
//		complement = sum - p[i];
//		iter = values_so_far.find(complement);
//		//if its complement is not in the set, add p[i]
//		if (iter == values_so_far.end()) {
//			values_so_far.insert(p[i]);
//		}
//		else {
//			cout << p[i] << " and " << complement << " sum to " << sum << endl;
//			return;
//		}
//	}
//	cout << "no elements sum to " << sum << endl;
//	
//}

/*Triplets:
	Given a target sum and an array, return a vector of vectors s.t.
	the elements of each vector sum to the target, 
	all elements of each vector are ordered, 
	and the vectors are ordered lexicographically.
*/
vector<vector<int>> triplets_brute_force(int target, vector<int> v) {
	
	//vector of vectors
	vector<vector<int>> output;

	//assert input is all non-negative
	if (target < 0) {
		cout << "can't have a negative target" << endl;
		return output;
	}
	//assert all of v is non-zero
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < 0) {
			cout << "can't have negative elements in v" << endl;
			return output;
		}
	}

	//if output is good now we do it!

	//first we sort v
	sort(v.begin(), v.end());

	//iterate over first elements
	int i1, i2, i3; //iterators
	int prev1, prev2, prev3; //previous elements corresponding to v[i1],v[i2],v[i3]
	vector<int> to_add; //vector of integers we can add to output
	
	prev1 = -1;
	for (i1 = 0; i1 < v.size(); i1++) {
		if (v[i1] > target) {
			break;
		}
		else if (v[i1] == prev1) {
			continue;
		}
		else {
			//reset prev1, prev2
			prev1 = v[i1];
			prev2 = -1;
			for (i2 = i1 + 1; i2 < v.size(); i2++) {
				if (v[i1] + v[i2] > target) {
					break;
				}
				else if (v[i2] == prev2) {
					continue;
				}
				else {
					prev2 = v[i2];
					prev3 = -1;
					for (i3 = i2 + 1; i3 < v.size(); i3++) {
						if (v[i1] + v[i2] + v[i3] > target) {
							break;
						}
						else if (v[i3] == prev3) {
							continue;
						}
						prev3 = v[i3];
						if (v[i1] + v[i2] + v[i3] == target) {
							vector<int> to_add = { v[i1],v[i2],v[i3] };
							output.push_back(to_add);
						}
					}
				}
			}
		}
	}

	return output;

}
//brute force but basically assumes elements of the input array are unique
vector<vector<int>> triplets_brute_force_nocheck(int target, vector<int> v) {

	//vector of vectors
	vector<vector<int>> output;

	//assert input is all non-negative
	if (target < 0) {
		cout << "can't have a negative target" << endl;
		return output;
	}
	//assert all of v is non-zero
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < 0) {
			cout << "can't have negative elements in v" << endl;
			return output;
		}
	}

	//if output is good now we do it!

	//first we sort v
	sort(v.begin(), v.end());

	//iterate over first elements
	int i1, i2, i3; //iterators
	vector<int> to_add; //vector of integers we can add to output

	for (i1 = 0; i1 < v.size(); i1++) {
		if (v[i1] > target) {
			break;
		}

		else {
			for (i2 = i1 + 1; i2 < v.size(); i2++) {
				if (v[i1] + v[i2] > target) {
					break;
				}
				else {
					for (i3 = i2 + 1; i3 < v.size(); i3++) {
						if (v[i1] + v[i2] + v[i3] > target) {
							break;
						}
						else if (v[i1] + v[i2] + v[i3] == target) {
							vector<int> to_add = { v[i1],v[i2],v[i3] };
							output.push_back(to_add);
						}
					}
				}
			}
		}
	}
	return output;

}

//okay now a two pointer approach
vector<vector<int>> triplets_2ptr(int target, vector<int> v) {
	//vector of vectors
	vector<vector<int>> output;

	//assert input is all non-negative
	if (target < 0) {
		cout << "can't have a negative target" << endl;
		return output;
	}
	//assert all of v is non-zero
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < 0) {
			cout << "can't have negative elements in v" << endl;
			return output;
		}
	}

	//if input is good we sort
	sort(v.begin(), v.end());
	vector<int> to_add;
	int val, j, k;
	//loop over first element
	for (int i = 0; i < v.size(); i++) {
		val = target - v[i];
		//okay here is the 2 pointer part
		j = i + 1;
		k = v.size()-1;

		while (j < k) {
			//in this case we have a triplet
			if (v[j] + v[k] == val) {
				to_add = { v[i],v[j],v[k] };
				output.push_back(to_add);
				j++;
			}
			else if (v[j] + v[k] < val) {
				j++;
			}
			else if (v[j] + v[k] > val) {
				k--;
			}
		}

	}
	return output;
}


int main() {
	//int x[] = { 1,7,3,4,12 };
	////get the length of x 
	//int len = sizeof(x) / sizeof(x[0]);
	//cout << "x is " << len << " ints long" << endl;
	//int sums[]{ 7,0,13,10};
	//int pair0 = 0;
	//int lensums = sizeof(sums) / sizeof(sums[0]);
	//for (int i = 0; i < lensums; i++) {
	//	pairs_unordered_set(x, len, sums[i]);
	//}
	//return 0;

	vector<int> x = {0, 7,2,3,5,4,6,1};
	auto start = chrono::high_resolution_clock::now();
	vector<vector<int>> output = triplets_brute_force_nocheck(7, x);
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

	cout << "number of triplets: " << output.size() << endl;
	cout << "total time: " << duration.count() << " microseconds"<< endl;
	unsigned int i;
	for (auto v : output) {
		for(i = 0; i < 3; i++){
			cout << v[i] << " ";
		}
		cout << endl;
	}

	//okay now for the 2pter algo
	auto start2 = chrono::high_resolution_clock::now();
	vector<vector<int>> output2 = triplets_2ptr(7, x);
	auto end2 = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::microseconds>(end2 - start2);

	cout << "number of triplets: " << output.size() << endl;
	cout << "total time: " << duration.count() << " microseconds" << endl;
	for (auto v : output) {
		for (i = 0; i < 3; i++) {
			cout << v[i] << " ";
		}
		cout << endl;
	}

	return 0;
}





