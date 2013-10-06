#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

static const string kTargetString = "To be or not to be that is the question...";

static int random(const int& iMin, const int& iMax)
{
	 return ( iMin + rand() % (iMax - iMin) );
}

static float map(const float& value, const float& istart, const float& istop, const float& ostart, const float& ostop)
{
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

static void initializeFunc(char* ioGenes, const size_t& iGeneCount)
{
	for(size_t i = 0; i < iGeneCount; i++) {
		ioGenes[i] = (char)random( 32, 126 );
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
	int tMid = random( 0, (int)iGeneCount );
	for(size_t i = 0; i < iGeneCount; i++) {
		if(i < tMid) { oGenes[i] = iGenesA[i]; }
		else         { oGenes[i] = iGenesB[i]; }
	}
}

static void mutateFunc(char* ioGenes, const size_t& iGeneCount, const float& iMutationRate) {
	for (int i = 0; i < iGeneCount; i++) {
		if( ( (float)rand() / (float)RAND_MAX ) < iMutationRate ) {
			ioGenes[i] = (char) random( 32, 126 );
		}
	}
}


class Population {
public:
	char**	mPopulation;
	size_t	mPopulationSize;
	size_t	mGeneCount;
	size_t	mGenerationIter;
	float	mMutationRate;
	bool	mRunning;
	
	Population(const size_t& iPopulationSize, const size_t& iGeneCount, const float& iMutationRate) :
		mPopulationSize( iPopulationSize ), mGeneCount( iGeneCount ), mMutationRate( iMutationRate ), mGenerationIter( 0 ), mRunning( true ), mPopulation( NULL )
	{
		// Initialize population:
		mPopulation = new char*[ mPopulationSize ];
		for(int i = 0; i < mPopulationSize; i++) {
			mPopulation[ i ] = new char[ mGeneCount ];
			initializeFunc( mPopulation[ i ], mGeneCount );
		}
	}
	
	~Population()
	{
		// Delete population:
		if( mPopulation ) {
			for(int i = 0; i < mPopulationSize; i++) {
				delete [] mPopulation[ i ];
			}
			delete [] mPopulation;
			mPopulation = NULL;
		}
	}
	
	void runGeneration()
	{
		// Prepare scoring variables:
		float  tScores[ mPopulationSize ];
		size_t tBestIdx    = 0;
		float  tBestScore  = -1e12;
		float  tWorstScore = 1e12;
		// Perform scoring:
		for(size_t i = 0; i < mPopulationSize; i++) {
			tScores[ i ] = fitnessFunc( mPopulation[ i ], mGeneCount );
			if( tScores[ i ] > tBestScore ) {
				tBestScore = tScores[ i ];
				tBestIdx   = i;
			}
			if( tScores[ i ] < tWorstScore ) {
				tWorstScore = tScores[ i ];
			}
		}
		// Print the best individual:
		cout << "BEST: ";
		for(size_t i = 0; i < mGeneCount; i++) {
			cout << mPopulation[ tBestIdx ][ i ];
		}
		cout << endl;
		// Check whether a perfect score has been achieved:
		if( tBestScore == 1.0 ) {
			mRunning = false;
		}
		else {
			vector<char*> tPool;
			// Based on fitness, each member will get added to the mating pool a certain number of times
			// a higher fitness = more entries to mating pool = more likely to be picked as a parent
			// a lower fitness = fewer entries to mating pool = less likely to be picked as a parent
			for(int i = 0; i < mPopulationSize; i++) {
				float tScoreAdjusted = map( tScores[i], tWorstScore, tBestScore, 0.0, 1.0 );
				int n = int( tScoreAdjusted * 100 );  // Arbitrary multiplier, we can also use monte carlo method
				for(int j = 0; j < n; j++) {              // and pick two random numbers
					tPool.push_back( mPopulation[ i ] );
				}
			}
			int tPoolSize = (int)tPool.size();
			// Initialize new population:
			char** tPopulation = new char*[ mPopulationSize ];
			// Create a new population:
			for(int i = 0; i < mPopulationSize; i++) {
				tPopulation[ i ] = new char[ mGeneCount ];
				crossoverFunc( tPool.at( random( 0, tPoolSize ) ), tPool.at( random( 0, tPoolSize ) ), tPopulation[ i ], mGeneCount );
				mutateFunc( tPopulation[ i ], mGeneCount, mMutationRate );
			}
			// Delete previous population:
			for(int i = 0; i < mPopulationSize; i++) {
				delete [] mPopulation[ i ];
			}
			delete [] mPopulation;
			mPopulation = NULL;
			// Set new population:
			mPopulation = tPopulation;
			// Advance generation iter:
			mGenerationIter++;
		}
	}

	bool isRunning()
	{
		return mRunning;
	}
	
	const size_t& getGenerationNumber() const
	{
		return mGenerationIter;
	}
};


int main(int argc, const char * argv[])
{
	srand( (unsigned int)time( NULL ) );

	Population* mPopulation = new Population( 1000, kTargetString.size(), 0.01 );
	
	while( mPopulation->isRunning() ) {
		mPopulation->runGeneration();
	}
	
	printf( "GA took %i generations.\n", (int)mPopulation->getGenerationNumber() );
	
	delete mPopulation;

    return 0;
}

