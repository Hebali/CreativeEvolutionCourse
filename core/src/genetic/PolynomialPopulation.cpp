//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include "PolynomialPopulation.h"

using namespace std;
using namespace ci;
using namespace ci::app;

PolynomialPopulation::PolynomialPopulation(const AssertionGroup& iAssertionGroup, const size_t& iPopulationSize,
					 const size_t& iMaxGenerationCount, const float& iMutationRate, const float& iPerfectScore) :
	mPopulationSize( iPopulationSize ),
	mAssertionGroup( iAssertionGroup ),
	mMutationRate( iMutationRate ),
	mGenerationMax( iMaxGenerationCount ),
	mPerfectThreshold( iPerfectScore ),
	mGenerationIter( 0 ),
	mRunning( true ),
	mBuffer( 100 ),
	mPopulation( NULL )
{
	mThread = make_shared<thread>( bind( &PolynomialPopulation::computeEvolution, this ) );
}

PolynomialPopulation::~PolynomialPopulation()
{
	// Stop evolution:
	mRunning = false;
	// Cancel buffer:
	mBuffer.cancel();
	// Join thread:
	mThread->join();
	// Delete population:
	if( mPopulation ) {
		delete [] mPopulation;
	}
}

bool PolynomialPopulation::hasUpdate()
{
	return mBuffer.isNotEmpty();
}

PolynomialDataRef PolynomialPopulation::getUpdate()
{
	PolynomialDataRef tResult;
    mBuffer.popBack( &tResult );
	return tResult;
}

void PolynomialPopulation::computeEvolution()
{
	ThreadSetup threadSetup;
	// Initialize population:
	mPopulation = new PolynomialDataRef[ mPopulationSize ];
	for(int i = 0; i < mPopulationSize; i++) {
		mPopulation[ i ] = initializationFunction();
	}
	// Compute generations:
	while( mRunning && mGenerationIter < mGenerationMax ) {
		// Prepare scoring variables:
		float  tScores[ mPopulationSize ];
		size_t tBestIdx    = 0;
		float  tBestScore  = -1e12;
		float  tWorstScore = 1e12;
		// Perform scoring:
		for(size_t i = 0; i < mPopulationSize; i++) {
			tScores[ i ] = fitnessFunction( mPopulation[ i ] );
			if( tScores[ i ] > tBestScore ) {
				tBestScore = tScores[ i ];
				tBestIdx   = i;
			}
			if( tScores[ i ] < tWorstScore ) {
				tWorstScore = tScores[ i ];
			}
		}
		// Print the best individual:
		printFunction( mPopulation[ tBestIdx ] );
		// Push a clone of the best individual into buffer:
		mBuffer.pushFront( PolynomialDataRef( (PolynomialData*)( mPopulation[ tBestIdx ]->clone() ) ) );
		// Check whether a perfect score has been achieved:
		if( tBestScore >= mPerfectThreshold ) {
			mRunning = false;
		}
		// Handle mating:
		else {
			// Normalize scores:
			float tNormMin  = 1.0;
			float tNormMax  = 1000.0;
			float tScoreSum = 0.0;
			// Prevent division by zero:
			if( tBestScore == tWorstScore ) {
				tBestScore += 0.1;
			}
			// Normalize scores:
			for(size_t i = 0; i < mPopulationSize; i++) {
				tScores[ i ] = tNormMin + ( tNormMax - tNormMin ) * ( ( tScores[i] - tWorstScore ) / ( tBestScore - tWorstScore ) );
				tScoreSum += tScores[ i ];
			}
			// Initialize new population:
			PolynomialDataRef* tPopulation = new PolynomialDataRef[ mPopulationSize ];
			// Create a new population:
			for(int i = 0; i < mPopulationSize; i++) {
				// Choose mating pair:
				size_t tIdxA = 0;
				size_t tIdxB = 0;
				float tRandA = randFloat( tScoreSum );
				float tRandB = randFloat( tScoreSum );
				while( tRandA > 0.0 ) { tRandA -= tScores[ tIdxA++ ]; }
				while( tRandB > 0.0 ) { tRandB -= tScores[ tIdxB++ ]; }
				// Apply crossover function:
				tPopulation[ i ] = crossoverFunction( mPopulation[ tIdxA - 1 ], mPopulation[ tIdxB - 1 ] );
				// Apply mutation function:
				mutationFunction( tPopulation[ i ], mMutationRate );
			}
			// Delete previous population:
			delete [] mPopulation;
			// Set new population:
			mPopulation = tPopulation;
			// Advance generation iter:
			mGenerationIter++;
		}
	}
}

PolynomialDataRef PolynomialPopulation::initializationFunction()
{
	PolynomialDataRef tNew = PolynomialDataRef( new PolynomialData() );
	for(int i = 0; i < 5; i++) {
		tNew->addComponent( randFloat( -10.0, 10.0 ), (float)i );
	}
	return tNew;
}

float PolynomialPopulation::fitnessFunction(PolynomialDataRef iGenes)
{
	return mAssertionGroup.applyTo( iGenes );
}

PolynomialDataRef PolynomialPopulation::crossoverFunction(PolynomialDataRef iGenesA, PolynomialDataRef iGenesB)
{
	PolynomialDataRef tNew = PolynomialDataRef( new PolynomialData() );
	PolynomialData::ComponentVec& tParentA = iGenesA->getComponents();
	PolynomialData::ComponentVec& tParentB = iGenesB->getComponents();
	PolynomialData::ComponentVecCiter itA  = tParentA.begin();
	PolynomialData::ComponentVecCiter itB  = tParentB.begin();
	while( itA != tParentA.end() && itB != tParentB.end() ) {
		int tRand = randInt( 3 );
		if( tRand == 0 ) {
			tNew->addComponent( (*itA).first, (*itA).second );
		}
		else if( tRand == 1 ) {
			tNew->addComponent( (*itB).first, (*itB).second );
		}
		else {
			tNew->addComponent( ( (*itA).first + (*itB).first ) / 2.0, ( (*itA).second + (*itB).second ) / 2.0 );
		}
		itA++;
		itB++;
	}
	return tNew;
}

void PolynomialPopulation::mutationFunction(PolynomialDataRef ioGenes, const float& iMutationRate)
{
	PolynomialData::ComponentVec& tGenes = ioGenes->getComponents();
	if( randFloat( 1.0 ) <= iMutationRate ) {
		size_t tIdx = randInt( 0, tGenes.size() );
		tGenes[ tIdx ].first = randFloat( -10.0, 10.0 );
	}
}

void PolynomialPopulation::printFunction(PolynomialDataRef iGenes)
{
	printf( "%s\n", mAssertionGroup.getAssertionString( iGenes ).c_str() );
}