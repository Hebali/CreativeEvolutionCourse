//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include <iostream>

#include "Population.h"
#include "Constants.h"

#include "Solver.h"

using namespace std;

static int init_test_correct[] = {
	8, 3, 5, 4, 1, 6, 9, 2, 7,
	2, 9, 6, 8, 5, 7, 4, 3, 1,
	4, 1, 7, 2, 9, 3, 6, 5, 8,
	5, 6, 9, 1, 3, 4, 7, 8, 2,
	1, 2, 3, 6, 7, 8, 5, 4, 9,
	7, 4, 8, 5, 2, 9, 1, 6, 3,
	6, 5, 2, 7, 8, 1, 3, 9, 4,
	9, 8, 1, 3, 4, 5, 2, 7, 6,
	3, 7, 4, 9, 6, 2, 8, 1, 5
};

static int init_test_incorrect[] = {
	8, 3, 5, 4, 1, 6, 9, 2, 7,
	2, 9, 6, 8, 5, 7, 4, 3, 1,
	4, 1, 7, 2, 9, 3, 6, 5, 8,
	5, 6, 9, 1, 3, 4, 7, 8, 2,
	1, 2, 3, 6, 7, 8, 5, 4, 9,
	7, 4, 8, 5, 2, 9, 1, 6, 3,
	6, 5, 2, 7, 8, 1, 3, 9, 4,
	9, 8, 1, 3, 4, 5, 2, 7, 6,
	3, 7, 4, 9, 6, 2, 8, 1, 1
};

int main(int argc, const char * argv[])
{
	cout << "Performing sanity check..." << endl;
	if( getBoardWin( init_test_correct, getTileCount() ) && !getBoardWin( init_test_incorrect, getTileCount() ) ) {
		cout << "PASSED" << endl << endl;
	}
	else {
		cout << "FAILED" << endl << endl;
		return 0;
	}
	cout << "Running team: \'" << kAuthorTeam << "\'" << endl << endl;
	// Seed random:
	srand( (unsigned int)time( NULL ) );
	// Prepare analytics:
	size_t tAvgDuration = 0;
	size_t tAvgGenCount = 0;
	// Run each test round:
	for(int i = 0; i < getTestRunCount(); i++) {
		// Start timer:
		size_t tTimeStart = getTimeNow();
		// Create new population instance:
		Population<int>* mPopulation = new Population<int>( getPopulationSize(), getTileCount(), kMutationRate );
		// Set function bindings:
		mPopulation->setInitializeFunction( randomBoard );
		mPopulation->setFitnessFunction( fitnessFunc );
		mPopulation->setCrossoverFunction( crossoverFunc );
		mPopulation->setMutationFunction( mutateFunc );
		mPopulation->setPrintFunction( printBoard );
		// Initialize the population:
		mPopulation->initialize();
		// While running flag is set, keep running algorithm:
		while( mPopulation->isRunning() ) {
			mPopulation->runGeneration();
		}
		// End timer:
		size_t tTimeStop = getTimeNow();
		// Update analytics:
		tAvgDuration += ( tTimeStop - tTimeStart );
		tAvgGenCount += mPopulation->getGenerationNumber();
		// Print win state:
		mPopulation->printWinState();
		// Delete population:
		delete mPopulation;
		// Report progress:
		cout << "Test round #" << i << " completed." << endl << endl;
	}
	// Print score:
	cout << "TEAM SCORE: \'" << kAuthorTeam << "\'" << endl;
	cout << "\tAverage Duration: " << ( (float)tAvgDuration / (float)getTestRunCount() ) << " milliseconds" << endl;
	cout << "\tAverage Generation Count: " << ( (float)tAvgGenCount / (float)getTestRunCount() ) << endl;
	// Return:
    return 0;
}

