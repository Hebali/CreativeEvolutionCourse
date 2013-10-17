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

static const string kTargetString = "To be or not to be that is the question...";

static void initializeFunc(char* ioGenes, const size_t& iGeneCount)
{
	for(size_t i = 0; i < iGeneCount; i++) {
		ioGenes[i] = (char)randomInt( 32, 127 );
	}
}

static float fitnessFunc(const char* iGenes, const size_t& iGeneCount) {
	size_t tScore = 0.0;
	for(size_t i = 0; i < iGeneCount; i++) {
		if( iGenes[i] == kTargetString.at( i ) ) {
			tScore++;
		}
	}
	return ( (float)tScore / (float)iGeneCount );
}

static void crossoverFunc(const char* iGenesA, const char* iGenesB, char* oGenes, const size_t& iGeneCount) {
	int tMid = randomInt( 0, (int)iGeneCount );
	for(size_t i = 0; i < iGeneCount; i++) {
		if(i < tMid) { oGenes[i] = iGenesA[i]; }
		else         { oGenes[i] = iGenesB[i]; }
	}
}

static void mutateFunc(char* ioGenes, const size_t& iGeneCount, const float& iMutationRate) {
	for (int i = 0; i < iGeneCount; i++) {
		if( ( (float)rand() / (float)RAND_MAX ) < iMutationRate ) {
			ioGenes[i] = (char)randomInt( 32, 127 );
		}
	}
}

static void printFunc(char* iGenes, const size_t& iGeneCount) {
	cout << "BEST: ";
	for(size_t i = 0; i < iGeneCount; i++) {
		cout << iGenes[ i ];
	}
	cout << std::endl;
}

int main(int argc, const char * argv[])
{
	srand( (unsigned int)time( NULL ) );

	Population<char>* mPopulation = new Population<char>( 1000, kTargetString.size(), 0.01 );
	
	mPopulation->setInitializeFunction( initializeFunc );
	mPopulation->setFitnessFunction( fitnessFunc );
	mPopulation->setCrossoverFunction( crossoverFunc );
	mPopulation->setMutationFunction( mutateFunc );
	mPopulation->setPrintFunction( printFunc );
	
	mPopulation->initialize();
	
	while( mPopulation->isRunning() ) {
		mPopulation->runGeneration();
	}
	
	cout << "GA took " << mPopulation->getGenerationNumber() << " generations." << endl;
	
	delete mPopulation;

    return 0;
}

