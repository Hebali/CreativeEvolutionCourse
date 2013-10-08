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

#include "Constants.h"

inline float map(const float& iValue, const float& iInStart, const float& iInStop, const float& iOutStart, const float& iOutStop)
{
    return iOutStart + ( iOutStop - iOutStart ) * ( ( iValue - iInStart ) / ( iInStop - iInStart ) );
}

inline int randomInt(const int& iMin, const int& iMax)
{
	return ( iMin + rand() % (iMax - iMin) );
}

/**
 * @brief A templated GA container and facilitator
 */
template <class DataType>
class Population {
public:
	typedef std::function<void(DataType*, const size_t&)>										InitializeFunction;
	typedef std::function<float(const DataType*, const size_t&)>								FitnessFunction;
	typedef std::function<void(const DataType*, const DataType*, DataType*, const size_t&)>		CrossoverFunction;
	typedef std::function<void(DataType*, const size_t&, const float&)>							MutationFunction;
	typedef std::function<void(DataType*, const size_t&)>										PrintFunction;
	
protected:
	InitializeFunction		mInitializeFunction;
	FitnessFunction			mFitnessFunction;
	CrossoverFunction		mCrossoverFunction;
	MutationFunction		mMutationFunction;
	PrintFunction			mPrintFunction;
	
	DataType**				mPopulation;
	size_t					mPopulationSize;
	size_t					mGeneCount;
	size_t					mGenerationIter;
	float					mMutationRate;
	bool					mRunning;
	
	DataType*				mWinState;
	
public:

	/**
	 * @brief Population constructor
	 */
	Population(const size_t& iPopulationSize, const size_t& iGeneCount, const float& iMutationRate) :
		mPopulationSize( iPopulationSize ),
		mGeneCount( iGeneCount ),
		mMutationRate( iMutationRate ),
		mGenerationIter( 0 ),
		mRunning( true ),
		mPopulation( NULL ),
		mWinState( NULL ),
		mInitializeFunction( NULL ),
		mFitnessFunction( NULL ),
		mCrossoverFunction( NULL ),
		mMutationFunction( NULL ),
		mPrintFunction( NULL )
	{
	}
	
	/**
	 * @brief Destructor
	 */
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
		// Delete win state:
		if( mWinState ) {
			delete [] mWinState;
			mWinState = NULL;
		}
	}
	
	/**
	 * @brief Binds an external initialization function
	 */
	void setInitializeFunction(InitializeFunction iFunc)
	{
		mInitializeFunction = iFunc;
	}
	
	/**
	 * @brief Binds an external fitness function
	 */
	void setFitnessFunction(FitnessFunction iFunc)
	{
		mFitnessFunction = iFunc;
	}
	
	/**
	 * @brief Binds an external crossover function
	 */
	void setCrossoverFunction(CrossoverFunction iFunc)
	{
		mCrossoverFunction = iFunc;
	}
	
	/**
	 * @brief Binds an external mutation function
	 */
	void setMutationFunction(MutationFunction iFunc)
	{
		mMutationFunction = iFunc;
	}
	
	/**
	 * @brief Binds an external printer function
	 */
	void setPrintFunction(PrintFunction iFunc)
	{
		mPrintFunction = iFunc;
	}
	
	/**
	 * @brief Initializes the genetic population
	 */
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
	
	/**
	 * @brief Runs a single generation of fitness evaluation and mating
	 */
	void runGeneration()
	{
		if( mFitnessFunction ) {
			// Prepare scoring variables:
			float  tScores[ mPopulationSize ];
			size_t tBestIdx    = 0;
			float  tBestScore  = -1e12;
			float  tWorstScore = 1e12;
			// Perform scoring:
			for(size_t i = 0; i < mPopulationSize; i++) {
				tScores[ i ] = mFitnessFunction( mPopulation[ i ], mGeneCount );
				if( tScores[ i ] > tBestScore ) {
					tBestScore = tScores[ i ];
					tBestIdx   = i;
				}
				if( tScores[ i ] < tWorstScore ) {
					tWorstScore = tScores[ i ];
				}
			}
			// Check whether best individual is complete:
			if( getBoardWin( mPopulation[ tBestIdx ], mGeneCount ) ) {
				// Copy win state:
				mWinState = new DataType[ mGeneCount ];
				std::copy( mPopulation[ tBestIdx ], mPopulation[ tBestIdx ] + mGeneCount, mWinState );
				// Set stop flag:
				mRunning = false;
			}
			// Handle mating:
			else if( mCrossoverFunction && mMutationFunction ) {
				std::vector<DataType*> tPool;
				// Add individuals to pool:
				for(int i = 0; i < mPopulationSize; i++) {
					int tN = map( tScores[i], tWorstScore, tBestScore, 1.0f, 100.0f );
					for(int j = 0; j < tN; j++) {
						tPool.push_back( mPopulation[ i ] );
					}
				}
				// Check pool size:
				int tPoolSize = (int)tPool.size();
				if( tPoolSize == 0 ) {
					printf( "ERROR: Cannot build genetic population from an empty mating pool.\n" );
					mRunning = false;
					return;
				}
				// Initialize new population:
				DataType** tPopulation = new DataType*[ mPopulationSize ];
				// Create a new population:
				for(int i = 0; i < mPopulationSize; i++) {
					tPopulation[ i ] = new DataType[ mGeneCount ];
					mCrossoverFunction( tPool.at( randomInt( 0, tPoolSize ) ), tPool.at( randomInt( 0, tPoolSize ) ), tPopulation[ i ], mGeneCount );
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
	
	/**
	 * @brief Prints the saved win state, if one exists
	 */
	void printWinState()
	{
		if( mPrintFunction && mWinState ) {
			printf( "WIN STATE:\n" );
			mPrintFunction( mWinState, mGeneCount );
		}
		else {
			printf( "ERROR: Cannot print valid win state!\n" );
		}
	}
	
	/**
	 * @brief Returns true if the GA has produced a Sudoku win state, otherwise false
	 */
	bool isRunning()
	{
		return mRunning;
	}
	
	/**
	 * @brief Returns the current generation number
	 */
	const size_t& getGenerationNumber() const
	{
		return mGenerationIter;
	}
};