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

int main(int argc, const char * argv[])
{
	// Seed random
	srand( (unsigned int)time( NULL ) );
	// Prepare analytics:
	size_t tAvgDuration = 0;
	size_t tAvgGenCount = 0;
	// Run each test round:
	for(int i = 0; i < kTestRunCount; i++) {
		// Start timer:
		size_t tTimeStart = getEpochMilliseconds();
		// Create new population instance:
		Population<int>* mPopulation = new Population<int>( kPopulationSize, kBoardTotalTiles, kMutationRate );
		// Set function bindings:
		mPopulation->setInitializeFunction( randomBoard );
		mPopulation->setFitnessFunction( fitnessFunc );
		mPopulation->setCompletionTestFunction( solutionCheckFunc );
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
		size_t tTimeStop = getEpochMilliseconds();
		// Update analytics:
		tAvgDuration += ( tTimeStop - tTimeStart );
		tAvgGenCount += mPopulation->getGenerationNumber();
		// Delete population:
		delete mPopulation;
	}
	// Print score:
	cout << "TEAM SCORE: " << kAuthorTeam << endl;
	cout << "\tAverage Duration: " << ( (float)tAvgDuration / (float)kTestRunCount ) << " milliseconds" << endl;
	cout << "\tAverage Generation Count: " << ( (float)tAvgGenCount / (float)kTestRunCount ) << endl;
	// Return:
    return 0;
}

