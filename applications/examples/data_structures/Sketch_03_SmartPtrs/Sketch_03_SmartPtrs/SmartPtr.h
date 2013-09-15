//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include <iostream>

#pragma mark -
#pragma mark REFERENCE_COUNTER

class RefCount {
public:
	RefCount() : mCount( 0 )
	{
		std::cout << "RefCount() began" << std::endl;
	}
	
	~RefCount()
	{
		std::cout << "~RefCount() ended" << std::endl;
	}
	
	bool isZero() const
	{
		return ( mCount == 0 );
	}
	
	const size_t& get() const
	{
		return mCount;
	}
	
	void increment()
	{
		mCount++;
	}
	
	void decrement()
	{
		mCount--;
	}
	
private:
	size_t mCount;
};

#pragma mark -
#pragma mark SMART_POINTER

template<class T>
class SmartPtr {
public:
	SmartPtr(T* iPtr) : mPtr( iPtr ), mCounter( new RefCount() )
	{
		std::cout << "SmartPtr(T* iPtr) began" << std::endl;
		
		// Increment reference count:
		mCounter->increment();
	}
	
	// copy constructor
	SmartPtr(const SmartPtr& iOther) : mPtr( iOther.get() ), mCounter( iOther.getRefCounter() )
	{
		std::cout << "SmartPtr(const SmartPtr& iOther) began" << std::endl;
		
		// Increment reference count:
		mCounter->increment();
	}
	
	~SmartPtr()
	{
		// Decrement counter:
		mCounter->decrement();
		// Check if counter has reached zero:
		if( mCounter->isZero() )
		{
			// Delete referenced object:
			delete mPtr;
			mPtr = NULL;
			// Delete reference counter:
			delete mCounter;
			mCounter = NULL;
		}
		std::cout << "~SmartPtr() ended" << std::endl;
	}
	
	RefCount* getRefCounter() const
	{
		return mCounter;
	}
	
	T* get() const
	{
		return mPtr;
	}
	
private:
	T*			mPtr;
	RefCount*	mCounter;
};
