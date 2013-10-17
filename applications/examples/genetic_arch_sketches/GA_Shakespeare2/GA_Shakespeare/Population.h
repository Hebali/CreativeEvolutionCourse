//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

inline float map(const float& iValue, const float& iInStart, const float& iInStop, const float& iOutStart, const float& iOutStop)
{
    return iOutStart + ( iOutStop - iOutStart ) * ( ( iValue - iInStart ) / ( iInStop - iInStart ) );
}

inline int randomInt(const int& iMin, const int& iMax) {
	return ( iMin + rand() % (iMax - iMin) );
}

template <class DataType>
class Population {
public:
	typedef std::function<void(DataType*, const size_t&)>										InitializeFunction;
	typedef std::function<float(const DataType*, const size_t&)>								FitnessFunction;
	typedef std::function<void(const DataType*, const DataType*, DataType*, const size_t&)>		CrossoverFunction;
	typedef std::function<void(DataType*, const size_t&, const float&)>							MutationFunction;
	typedef std::function<void(DataType*, const size_t&)>										PrintFunction;
	
protected:
	InitializeFunction	mInitializeFunction;
	FitnessFunction		mFitnessFunction;
	CrossoverFunction	mCrossoverFunction;
	MutationFunction	mMutationFunction;
	PrintFunction		mPrintFunction;
	
	DataType**			mPopulation;
	size_t				mPopulationSize;
	size_t				mGeneCount;
	size_t				mGenerationIter;
	float				mMutationRate;
	bool				mRunning;
	
public:

	Population(const size_t& iPopulationSize, const size_t& iGeneCount, const float& iMutationRate) :
		mPopulationSize( iPopulationSize ),
		mGeneCount( iGeneCount ),
		mMutationRate( iMutationRate ),
		mGenerationIter( 0 ),
		mRunning( true ),
		mPopulation( NULL ),
		mInitializeFunction( NULL ),
		mFitnessFunction( NULL ),
		mCrossoverFunction( NULL ),
		mMutationFunction( NULL ),
		mPrintFunction( NULL )
	{
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
	
	void setInitializeFunction(InitializeFunction iFunc)
	{
		mInitializeFunction = iFunc;
	}
	
	void setFitnessFunction(FitnessFunction iFunc)
	{
		mFitnessFunction = iFunc;
	}
	
	void setCrossoverFunction(CrossoverFunction iFunc)
	{
		mCrossoverFunction = iFunc;
	}
	
	void setMutationFunction(MutationFunction iFunc)
	{
		mMutationFunction = iFunc;
	}
	
	void setPrintFunction(PrintFunction iFunc)
	{
		mPrintFunction = iFunc;
	}
	
	void initialize()
	{
		if( mInitializeFunction ) {
			// Initialize population:
			mPopulation = new DataType*[ mPopulationSize ];
			for(int i = 0; i < mPopulationSize; i++) {
				mPopulation[ i ] = new DataType[ mGeneCount ];
				mInitializeFunction( mPopulation[ i ], mGeneCount );
			}
		}
	}
	
	void runGeneration()
	{
		if( mFitnessFunction ) {
			// Prepare scoring variables:
			float  tScores[ mPopulationSize ];
			size_t tBestIdx    = 0;
			float  tBestScore  = -1e12;
			float  tWorstScore = 1e12;
			float  tAvgScore   = 0.0;
			// Perform scoring:
			for(size_t i = 0; i < mPopulationSize; i++) {
				tScores[ i ] = mFitnessFunction( mPopulation[ i ], mGeneCount );
				tAvgScore += tScores[ i ];
				if( tScores[ i ] > tBestScore ) {
					tBestScore = tScores[ i ];
					tBestIdx   = i;
				}
				if( tScores[ i ] < tWorstScore ) {
					tWorstScore = tScores[ i ];
				}
			}
			tAvgScore /= mPopulationSize;
			printf( "AVG SCORE: %f\n", tAvgScore );
			// Print the best individual:
			if( mPrintFunction ) {
				mPrintFunction( mPopulation[ tBestIdx ], mGeneCount );
			}
			// Check whether a perfect score has been achieved:
			if( tBestScore == 1.0 ) {
				mRunning = false;
			}
			// Handle mating:
			else if( mCrossoverFunction && mMutationFunction ) {
				// Normalize scores:
				float tScoreSum = 0.0;
				for(size_t i = 0; i < mPopulationSize; i++) {
					tScores[ i ] = map( tScores[i], tWorstScore, tBestScore, 1.0f, 100.0f );
					tScoreSum += tScores[ i ];
				}
				// Initialize new population:
				DataType** tPopulation = new DataType*[ mPopulationSize ];
				// Create a new population:
				for(int i = 0; i < mPopulationSize; i++) {
					// Choose mating pair:
					size_t tIdxA = 0;
					size_t tIdxB = 0;
					float tRandA = ( (float)rand() / (float)RAND_MAX ) * tScoreSum;
					float tRandB = ( (float)rand() / (float)RAND_MAX ) * tScoreSum;
					while( tRandA > 0.0 ) { tRandA -= tScores[ tIdxA++ ]; }
					while( tRandB > 0.0 ) { tRandB -= tScores[ tIdxB++ ]; }
					// Create population:
					tPopulation[ i ] = new DataType[ mGeneCount ];
					// Apply crossover function:
					mCrossoverFunction( mPopulation[ tIdxA - 1 ], mPopulation[ tIdxB - 1 ], tPopulation[ i ], mGeneCount );
					// Apply mutation function:
					mMutationFunction( tPopulation[ i ], mGeneCount, mMutationRate );
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