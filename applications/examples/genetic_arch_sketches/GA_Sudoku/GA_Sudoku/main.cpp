//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include <iostream>

#include "Population.h"

using namespace std;

static const int kBoardAxisLen    = 9;
static const int kBoardTotalTiles = kBoardAxisLen * kBoardAxisLen;

static void randomBoard(int* ioBoard, const size_t& iTileCount)
{
	for(int i = 0; i < iTileCount; i++) {
		ioBoard[i] = random( 1, 10 );
	}
}

static float fitnessFunc(const int* iBoard, const size_t& iTileCount)
{
	// TODO:
	return (float)rand() / (float)RAND_MAX;
}

static void crossoverFunc(const int* iBoardA, const int* iBoardB, int* oBoard, const size_t& iTileCount)
{
	int tMid = random( 0, (int)iTileCount );
	for(size_t i = 0; i < iTileCount; i++) {
		if(i < tMid) { oBoard[i] = iBoardA[i]; }
		else         { oBoard[i] = iBoardB[i]; }
	}
}

static void mutateFunc(int* ioBoard, const size_t& iTileCount, const float& iMutationRate)
{
	for (int i = 0; i < iTileCount; i++) {
		if( ( (float)rand() / (float)RAND_MAX ) < iMutationRate ) {
			ioBoard[i] = random( 1, 10 );
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

int main(int argc, const char * argv[])
{
	srand( (unsigned int)time( NULL ) );
	
	Population<int>* mPopulation = new Population<int>( 1000, kBoardTotalTiles, 0.01 );
	
	mPopulation->setInitializeFunction( randomBoard );
	mPopulation->setFitnessFunction( fitnessFunc );
	mPopulation->setCrossoverFunction( crossoverFunc );
	mPopulation->setMutationFunction( mutateFunc );
	mPopulation->setPrintFunction( printBoard );
	
	mPopulation->initialize();
	
	while( mPopulation->isRunning() ) {
		mPopulation->runGeneration();
	}
	
	cout << "GA took " << mPopulation->getGenerationNumber() << " generations." << endl;
	
	delete mPopulation;
	
    return 0;
}

