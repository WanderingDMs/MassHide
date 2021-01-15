/*
	Name: MassHide
	Copyright: 2020
	Author: Daniel R. Collins
	Date: 06/12/20 13:00
	Description: Assess mass Hide vs. Spot 
	  probabilities by Monte Carlo simulation.

	  Written & used in WanderingDMs S02, E49
	  https://youtu.be/X5wF8p1K8pU
*/
#include <cstdlib>
#include <iostream>
#include <ctime>

// Constants (adjust as desired)
const int NUM_HIDERS = 4;
const int NUM_SPOTTERS = 4;
const int HIDE_BONUS = 0;
const int SPOT_BONUS = 0;
const int NUM_TRIALS = 10000;

// Roll a twenty-sided die
int roll20() {
	return rand() % 20 + 1;
}

// Roll many Hide checks & return lowest
int lowHide() {
	int lowest = 100;
	for (int i = 0; i < NUM_HIDERS; i++) {
		int check = roll20() + HIDE_BONUS;
		if (check < lowest)
			lowest = check;
	}
	return lowest;		
}

// Roll many Spot checks & return highest
int highSpot() {
	int high = -1;
	for (int i = 0; i < NUM_SPOTTERS; i++) {
		int check = roll20() + SPOT_BONUS;
		if (check > high)
			high = check;
	}
	return high;		
}

// Roll one team's Hide vs. one team Spot checks
bool oneTrial() {
	return highSpot() >= lowHide();
}

// Check team vs. team checks many times
// Return: ratio of times hiders are spotted
float manyTrials() {
	int numSpot = 0;
	for (int i = 0; i < NUM_TRIALS; i++) {
		if (oneTrial())
			numSpot++;
	}	
	return (float) numSpot / NUM_TRIALS;
}

// Main test driver
int main(int argc, char *argv[])
{
	srand(time(0));
	float spotRatio = manyTrials();
	std::cout << "Spot success: " << spotRatio * 100 << "%\n";
	return EXIT_SUCCESS;
}
