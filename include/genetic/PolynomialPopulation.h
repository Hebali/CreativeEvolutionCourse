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

class PolynomialPopulation {
public:
	
	typedef std::shared_ptr<std::thread>					ThreadRef;
	typedef ci::ConcurrentCircularBuffer<PolynomialDataRef>	Buffer;
private:

	AssertionGroup		mAssertionGroup;
	PolynomialDataRef*	mPopulation;
	size_t				mPopulationSize;
	size_t				mGenerationIter;
	size_t				mGenerationMax;
	float				mMutationRate;
	float				mPerfectThreshold;
	bool				mRunning;
	ThreadRef			mThread;
	Buffer				mBuffer;
			
public:
	
	PolynomialPopulation(const AssertionGroup& iAssertionGroup, const size_t& iPopulationSize,
						 const size_t& iMaxGenerationCount, const float& iMutationRate, const float& iPerfectScore = 1e12);
	
	~PolynomialPopulation();
	
	bool				hasUpdate();
	PolynomialDataRef	getUpdate();
	
private:
	
	void				computeEvolution();
		
	PolynomialDataRef	initializationFunction();
	float				fitnessFunction(PolynomialDataRef iGenes);
	PolynomialDataRef	crossoverFunction(PolynomialDataRef iGenesA, PolynomialDataRef iGenesB);
	void				mutationFunction(PolynomialDataRef ioGenes, const float& iMutationRate);
	void				printFunction(PolynomialDataRef iGenes);
};