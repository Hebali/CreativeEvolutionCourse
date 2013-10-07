//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include <iostream>
#include <chrono>

#include "Population.h"

using namespace std;

static const int	kBoardAxisLen    = 9;
static const int	kBoardTotalTiles = kBoardAxisLen * kBoardAxisLen;

static const int	kTileValueMin    = 1;
static const int	kTileValueMax    = 9;

static const int	kPopulationSize  = 1000;
static const float	kMutationRate    = 0.01f;

static void randomBoard(int* ioBoard, const size_t& iTileCount)
{
	for(int i = 0; i < iTileCount; i++) {
		ioBoard[i] = randomInt( kTileValueMin, kTileValueMax + 1 );
	}
}

static float fitnessFunc(const int* iBoard, const size_t& iTileCount)
{
	// EXERCISE: Please implement a function that evaluates the fitness of a given sudoku board here...
	
	return (float)rand() / (float)RAND_MAX;
}

static void crossoverFunc(const int* iBoardA, const int* iBoardB, int* oBoard, const size_t& iTileCount)
{
	// EXERCISE: Please feel free to replace the contents of this function to improve upon your algorithm's performance...
	
	int tMid = randomInt( 0, (int)iTileCount );
	for(size_t i = 0; i < iTileCount; i++) {
		if(i < tMid) { oBoard[i] = iBoardA[i]; }
		else         { oBoard[i] = iBoardB[i]; }
	}
}

static void mutateFunc(int* ioBoard, const size_t& iTileCount, const float& iMutationRate)
{
	// EXERCISE: Please feel free to replace the contents of this function to improve upon your algorithm's performance...
	
	for(int i = 0; i < iTileCount; i++) {
		if( ( (float)rand() / (float)RAND_MAX ) < iMutationRate ) {
			ioBoard[i] = randomInt( kTileValueMin, kTileValueMax + 1 );
		}
	}
}

static void printBoard(int* iBoard, const size_t& iTileCount)
{
	int tAxisLen = sqrt( iTileCount );
	printf( "%ix%i BOARD:\n", tAxisLen, tAxisLen );
	for(int i = 0; i < tAxisLen; i++) {
		for(int j = 0; j < tAxisLen; j++) {
			printf( "%i ", iBoard[ j * tAxisLen + i ] );
		}
		printf( "\n" );
	}
	printf( "\n" );
}

typedef unsigned long long EpochTime;

/**
 * @brief Static function returns elapsed nanoseconds since 00:00:00 UTC on 1 January 1970
 */
inline EpochTime getEpochNanoseconds()
{
	auto tNow = std::chrono::system_clock::now();
	auto tEla = tNow.time_since_epoch();
	auto tMil = std::chrono::duration_cast<std::chrono::nanoseconds>( tEla );
	return tMil.count();
}

int main(int argc, const char * argv[])
{
	srand( (unsigned int)time( NULL ) );
	
	EpochTime tTimeStart = getEpochNanoseconds();
	
	Population<int>* mPopulation = new Population<int>( kPopulationSize, kBoardTotalTiles, kMutationRate );
	
	mPopulation->setInitializeFunction( randomBoard );
	mPopulation->setFitnessFunction( fitnessFunc );
	mPopulation->setCrossoverFunction( crossoverFunc );
	mPopulation->setMutationFunction( mutateFunc );
	mPopulation->setPrintFunction( printBoard );
	
	mPopulation->initialize();
	
	while( mPopulation->isRunning() ) {
		mPopulation->runGeneration();
	}
	
	EpochTime tTimeStop = getEpochNanoseconds();
	
	cout << "GA took " << mPopulation->getGenerationNumber() << " generations." << endl;
	cout << "GA took " << ( tTimeStop - tTimeStart ) << " nanoseconds." << endl;
	
	delete mPopulation;
	
    return 0;
}

