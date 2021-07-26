#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <chrono>
#include <string>
#include "pairs_triplets.h" //has the pairs_triplets functions
#include "mountain.h" //mountain functions
#include "longestband.h"
using namespace std;

//runs the triplets exercise
void run_triplets() {
	vector<int> x = { 0, 7,2,3,5,4,6,1 };
	auto start = chrono::high_resolution_clock::now();
	vector<vector<int>> output = triplets_brute_force_nocheck(7, x);
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

	cout << "number of triplets: " << output.size() << endl;
	cout << "total time: " << duration.count() << " microseconds" << endl;
	unsigned int i;
	for (auto v : output) {
		for (i = 0; i < 3; i++) {
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
}

void run_mountain() {
	//naive version
	vector<int> x = { 5,6,1,2,3,4,5,4,3,2,0,1,2,3,-2,4 };
	cout << "length " << mountain_naive(x) << endl;

	cout << "second approach" << endl;
	cout << "length " << mountain_peak_first(x) << endl;

}

void run_longest_band() {
	vector<int> x = { 1,4,2,6,5,3,7,0,-2,8,12,15,13,14,20,-5,41,42,43,44,45,46,47,48,49,50,51,52,53,54,-10,-11,-12,-13,100,101};
	auto start = chrono::high_resolution_clock::now();
	longest_band_naive(x);
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "total time: " << duration.count() << " microseconds" << endl;


	cout << "trying O(n) way" << endl;
	start = chrono::high_resolution_clock::now();
	longest_band_unordered_sets(x);
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "total time: " << duration.count() << " microseconds" << endl;
	
}


int main() {
	//run_mountain();
	run_longest_band();
	return 0;
}




