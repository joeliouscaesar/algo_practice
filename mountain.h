/*
	For solving the mountain problem. Takes in an array of distinct integers,
	finds the length of the widest (?) mountain.

	A mountain is defined as a strictly increasing sequence of numbers followed 
	by a strictly decreasing sequence of numbers, i.e. 1 2 4 3 1 is a mountain of 
	length 5. 

	I think what we want is the longest mountain.  
*/

#include<iostream>
#include<vector>
using namespace std;

//my naive approach
int mountain_naive(vector<int> x) {

	//_direction = 0 if not increasing or decreasing, 1 if increasing, -1 if decreasing
	//_stretch_length is the length of the previous stretch
	if (x.size() < 3) {
		cout << "impossible to have a mountain with fewer than 3 values" << endl;
		return -1;
	}
	
	int previous_direction = 0; //int previous_stretch_length = 0;
	int current_stretch_length = 0;
	bool on_mountain = false;
	int peak; int mountain_length = 0;
	int longest_mountain = 0; int longest_mountain_peak = -1;
	int direction; //stores the direction the vector is moving in
	for (long i = 1; i < x.size(); i++) {
		direction = x[i] == x[i - 1] ? 0 : (x[i] - x[i - 1]) / abs(x[i] - x[i - 1]);

		cout << "i: " << i << ", direction: " << direction << endl;
		//look at the direction, if it's a new direction, check for a peak and reset the directions/lengths
		//if it's the same direction, add to the current length
		
		if (direction < 0 && previous_direction > 0) {
			//means we have a peak! at i-1
			on_mountain = true;
			cout << "on a mountain!" << endl;
			//sets the mountain length to be the increasing length for now 
			mountain_length = current_stretch_length;
			current_stretch_length = 1;
			peak = i-1;
		}
		else if (direction != previous_direction) {
			//in this case we had a switch but not a peak
			
			//if we were on a mountain, now the mountain is over
			if (on_mountain) {
				cout << "mountain ended" << endl;
				//evaluate if this was the longest mountain
				mountain_length = mountain_length + current_stretch_length + 1;
				if (mountain_length > longest_mountain) {
					longest_mountain = mountain_length;
					longest_mountain_peak = peak;
				}
				mountain_length = 0;
				on_mountain = false;
			}
			current_stretch_length = 1;
		}
		else {
			//in this case we're going in the same direction
			current_stretch_length++;
		}
		previous_direction = direction;

	}
	//if we were on a mountain it may not have ended!
	if (on_mountain) {
		cout << "mountain ended" << endl;
		//evaluate if this was the longest mountain
		mountain_length = mountain_length + current_stretch_length + 1;
		if (mountain_length > longest_mountain) {
			longest_mountain = mountain_length;
			longest_mountain_peak = peak;
		}
	}

	cout << "longest mountain peaked at " << longest_mountain_peak << endl;
	return longest_mountain;
}

