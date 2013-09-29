//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

/**
 * @brief A templated n-dimensional array supporting variable dimension lengths
 */
template <class DataType>
class NArray {
public:
	
	/** @brief Default constructor */
	NArray()
	: mTotalIndexCount( 0 ), mDimensionCount( 0 ), mUnitsPerDimension( NULL ), mData( NULL )
	{
	}
	
	/** @brief Constructor uses an array of dimension sizes to initialize internal container. Fills data components with given default value. */
	NArray(size_t* iUnitsPerDimension, const size_t& iDimensionCount, const DataType& iDefaultVal = 0)
	: mTotalIndexCount( 0 ), mDimensionCount( iDimensionCount ), mUnitsPerDimension( NULL ), mData( NULL )
	{
		if( mDimensionCount > 0 ) {
			// Set dimension sizes:
			mUnitsPerDimension = new size_t[ mDimensionCount ];
			std::copy( iUnitsPerDimension, iUnitsPerDimension + mDimensionCount, mUnitsPerDimension );
			// Set total index count:
			mTotalIndexCount = 1;
			for(size_t i = 0; i < mDimensionCount; i++) {
				mTotalIndexCount *= mUnitsPerDimension[ i ];
			}
			// Initialize data array:
			mData = new DataType[ mTotalIndexCount ];
			std::fill( mData, mData + mTotalIndexCount, iDefaultVal );
		}
	}
	
	/** @brief Destructor */
	~NArray()
	{
		if( mUnitsPerDimension ) {
			delete [] mUnitsPerDimension;
		}
		if( mData ) {
			delete [] mData;
		}
	}
	
	/** @brief Returns the data component at the given 1D genome index */
	DataType& getDatumAtIndex(const size_t& iIndex)
	{
		return mData[ iIndex ];
	}
	
	/** @brief Returns the data component at the given component-axis coordinates */
	DataType& getDatumAtCoordinate(size_t* iCoordinates)
	{
		return mData[ getIndex( iCoordinates ) ];
	}
	
	/** @brief Returns the total number of data components in the genome */
	const size_t& getDatumCount() const
	{
		return mTotalIndexCount;
	}
	
	/** @brief Converts a 1D genome index to a vector of component-axis coordinates */
	std::vector<size_t> getCoordinates(const size_t& iIndex) const
	{
		// FORM:
		// x =   iIndex % xLen;
		// y =  (iIndex / xLen) % yLen;
		// z = ((iIndex / xLen) / yLen) % zLen;
		
		// Prepare output vector:
		std::vector<size_t> tOut;
		// Check that index is within range:
		if( iIndex >= mTotalIndexCount ) { return tOut; }
		// Iterate over each axis:
		for(int i = 0; i < mDimensionCount; i++) {
			// Compute component coordinate:
			size_t tCur = iIndex;
			for(int j = 0; j <= i - 1; j++) {
				tCur /= mUnitsPerDimension[ j ];
			}
			tCur %= mUnitsPerDimension[ i ];
			tOut.push_back( tCur );
		}
		// Return output:
		return tOut;
	}
	
	/** @brief Converts an array of component-axis genome coordinates to a 1D index */
	size_t getIndex(size_t* iCoordinates) const
	{
		// FORM: idx = (z * xLen * yLen) + (y * xLen) + x;
		
		if( mDimensionCount < 1 ) { return 0; }
		// Start with x-axis:
		size_t tIdx = iCoordinates[ 0 ];
		// Add subsequent axes:
		for(int i = 1; i < mDimensionCount; i++) {
			size_t tCur = iCoordinates[ i ];
			for(int j = i - 1; j >= 0; j--) {
				tCur *= mUnitsPerDimension[ j ];
			}
			tIdx += tCur;
		}
		// Return index:
		return tIdx;
	}
	
protected:
	size_t		mTotalIndexCount;
	size_t		mDimensionCount;
	size_t*		mUnitsPerDimension;
	DataType*	mData;
};

