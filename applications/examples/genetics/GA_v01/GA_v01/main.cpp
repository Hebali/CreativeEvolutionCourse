#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

template <class DataType>
class GenomePopulation {
protected:
	size_t		mTotalIndexCount;
	size_t		mDimensionCount;
	size_t*		mUnitsPerDimension;
	DataType*	mData;
	
public:
	
	GenomePopulation()
	: mTotalIndexCount( 0 ), mDimensionCount( 0 ), mUnitsPerDimension( NULL ), mData( NULL )
	{
	}
	
	GenomePopulation(size_t* iUnitsPerDimension, size_t iDimensionCount)
	: mTotalIndexCount( 0 ), mDimensionCount( iDimensionCount ), mUnitsPerDimension( NULL ), mData( NULL )
	{
		if( mDimensionCount > 0 ) {
			// Set dimension sizes:
			mUnitsPerDimension = new size_t[ mDimensionCount ];
			copy( iUnitsPerDimension, iUnitsPerDimension + mDimensionCount, mUnitsPerDimension );
			// Set total index count:
			mTotalIndexCount = 1;
			for(size_t i = 0; i < mDimensionCount; i++) {
				mTotalIndexCount *= mUnitsPerDimension[ i ];
			}
			// Initialize data array:
			mData = new DataType[ mTotalIndexCount ];
		}
	}
	
	~GenomePopulation()
	{
		if( mUnitsPerDimension ) {
			delete [] mUnitsPerDimension;
		}
		if( mData ) {
			delete [] mData;
		}
	}
	
	DataType& getDatumAtIndex(const size_t& iIndex)
	{
		return mData[ iIndex ];
	}
	
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
	vector<size_t> getCoordinates(const size_t& iIndex) const
	{
		// FORM:
		// x =   iIndex % xLen;
		// y =  (iIndex / xLen) % yLen;
		// z = ((iIndex / xLen) / yLen) % zLen;
		
		// Prepare output vector:
		vector<size_t> tOut;
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
		
};

int main(int argc, const char * argv[])
{
	size_t tPopulationSize   = 100;
	size_t tFeatureCount     = 10;
	size_t tDimensionPerFeat = 5;
	
	GenomePopulation<double>* tGenome = new GenomePopulation<double>( (size_t[]){ tPopulationSize, tFeatureCount, tDimensionPerFeat }, 3 );
	
	size_t tIdxCount = tGenome->getDatumCount();
	
	size_t tErrCount = 0;
	
	for(size_t i = 0; i < tIdxCount; i++) {
		vector<size_t> tCoords = tGenome->getCoordinates( i );
		size_t tConvert = tGenome->getIndex( &tCoords[0] );
		if( tConvert != i ) {
			tErrCount++;
			cout << "ERROR! " << tConvert << " != " << i << endl;
		}
	}
	
	if( tErrCount == 0 ) {
		cout << "TEST PASSED. " << tGenome->getDatumCount() << endl;
		tGenome->getDatumAtIndex( 443 ) = 111222.333444;
		printf( "%f \n", tGenome->getDatumAtIndex( 443 ) );
		cout << setprecision( 6 ) << fixed << tGenome->getDatumAtIndex( 443 ) << endl << endl;
	}
	else {
		cout << "TEST FAILED." << endl;
	}
	
	delete tGenome;
	
    return 0;
}

