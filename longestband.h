/*
	Given an array of n integers, the longest band problem finds the longest band, 
	where a band is a subsequence that can be reordered such that all elements 
	appear consecutive, i.e. have absolute difference of one. The subsequence is 
	just a subset of the original array. 

	Ex: [1,9,3,0,18,5,2,4,10,7,12,6] has a band 0,1,2,3,4,5,6,7 of length 8
*/
#include<iostream>
#include<vector>
#include<unordered_set>
#include<algorithm>

//this just sorts x and gets the longest, so O(nlog(n)) I think
void longest_band_naive(vector<int> x) {

	std::sort(x.begin(), x.end());
	
	cout << "sorted x" << endl;
	for (int y : x) {
		cout << y << " ";
	}
	cout << endl;

	int longest_band = 1;
	int current_streak = 1;
	for (int i = 0; i < x.size() - 1; i++) {
		if (abs(x[i + 1] - x[i]) == 1) {
			current_streak++;
			if (current_streak > longest_band) {
				longest_band = current_streak;
			}
		}
		else {
			current_streak = 1;
		}
	}
	cout << "longest band is length: " << longest_band << endl;
}

//okay now we'll try in O(n)
/*
	Two undordered sets, one for elements that only point to other elements, the other with everything else

	Once we have two sets, we iterate through all of the only pointers and see how long the longest band is. 
	I think this is O(2N)=O(N)
*/

void longest_band_unordered_sets(vector<int> x) {
	unordered_set<int> pointed_to;
	unordered_set<int> not_pointed_to;

	unordered_set<int>::const_iterator found;
	for (int i : x) {

		//is x pointed to by pointed_to or not_pointed_to? if yes to either, then pointed_to. Otherwise, not_pointed_to
		//is any element of not_pointed_to pointed to by x? if yes, said element goes to pointed_to

		//checks if i-1 is in pointed_to, 
		found = pointed_to.find(i - 1);
		if (found != pointed_to.end()) {
			pointed_to.insert(i);
		}
		else {
			found = not_pointed_to.find(i - 1);
			//if i-1 is in not pointed to, i is pointed to
			if (found != not_pointed_to.end()) {
				pointed_to.insert(i);
			}
			else {
				not_pointed_to.insert(i);
			}
		}

		//now we have to check if i points to any of the not pointed to's
		found = not_pointed_to.find(i + 1);
		if (found != not_pointed_to.end()) {
			not_pointed_to.erase(i + 1);
			pointed_to.insert(i + 1);
		}

	}

	int longest_band = 0; int curr_band = 0;
	int longest_band_start = -1; int k;
	//now we loop over elements that aren't pointed to
	for (auto j : not_pointed_to) {
		curr_band = 0;
		k = j;
		do {
			k++;
			curr_band++;
			if (curr_band > longest_band) {
				longest_band = curr_band;
				longest_band_start = j;
			}
			found = pointed_to.find(k);
		} while (found != pointed_to.end());
	}

	cout << "longest band starts at " << longest_band_start << endl;
	cout << "longest band is " << longest_band << " long" << endl;

}





