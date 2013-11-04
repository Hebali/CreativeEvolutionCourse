//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include "cinder/Rand.h"
#include "cinder/Thread.h"
#include "cinder/ConcurrentCircularBuffer.h"

#include "GuiPlot.h"
#include "PolynomialData.h"
#include "PolynomialAssertion.h"

/** 
 * @brief A population container and evolutionary process facilitation class for polynomial data and assertions 
 */
class PolynomialPopulation {
public:
	
	typedef std::shared_ptr<std::thread>					ThreadRef;	//!< A shared_ptr thread wrapper type
	typedef ci::ConcurrentCircularBuffer<PolynomialDataRef>	Buffer;		//!< A concurrent buffer type
private:

	AssertionGroup		mAssertionGroup;	//!< The AssertionGroup determining individual fitness
	PolynomialDataRef*	mPopulation;		//!< The gene pool
	size_t				mPopulationSize;	//!< The number of items allowed in the gene pool
	size_t				mGenerationIter;	//!< The current generation number
	size_t				mGenerationMax;		//!< The maximum allowed number of generations in the evolutionary process
	float				mMutationRate;		//!< The rate of individual mutation
	float				mPerfectThreshold;	//!< The perfect score threshold value
	bool				mRunning;			//!< Flags whether the evolutionary process is currently running
	ThreadRef			mThread;			//!< The thread upon which the evolutionary process is run
	Buffer				mBuffer;			//!< A concurrent circular container storing buffered outputs
			
public:
	
	/** @brief Basic constructor */
	PolynomialPopulation(const AssertionGroup& iAssertionGroup, const size_t& iPopulationSize,
						 const size_t& iMaxGenerationCount, const float& iMutationRate, const float& iPerfectScore = 1e12);
	
	/** @brief Destructor */
	~PolynomialPopulation();
	
	/** @brief Returns true if the internal buffer contains at least one item */
	bool				hasUpdate();
	
	/** @brief Pops an item from the internal buffer and returns it in a thread-safe manner */
	PolynomialDataRef	getUpdate();
	
private:
	
	/** @brief An internal threaded function that computes each stage of the evolutionary process */
	void				computeEvolution();
		
	/** @brief An internal function that creates an initial gene pool member */
	PolynomialDataRef	initializationFunction();
	
	/** @brief An internal fitness function that scores an individual agains the AssertionGroup */
	float				fitnessFunction(PolynomialDataRef iGenes);
	
	/** @brief An internal cross-over function that returns a new child for the given parents */
	PolynomialDataRef	crossoverFunction(PolynomialDataRef iGenesA, PolynomialDataRef iGenesB);
	
	/** @brief An internal mutation function that applies genetic mutations to the input at the given frequency rate */
	void				mutationFunction(PolynomialDataRef ioGenes, const float& iMutationRate);
	
	/** @brief An internal printer function (for debugging) */
	void				printFunction(PolynomialDataRef iGenes);
};