//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include <iostream>

#include "NArray.h"

using namespace std;

// SKETCHING EXAMPLE: Preliminary Architectural Components for a Genetic Algorithm in C++

int main(int argc, const char * argv[])
{
	size_t tPopulationSize   = 100;
	size_t tFeatureCount     = 10;
	size_t tDimensionPerFeat = 5;
	
	NArray<double>* tGenome = new NArray<double>( (size_t[]){ tPopulationSize, tFeatureCount, tDimensionPerFeat }, 3 );
	
	size_t tErrCount = 0;
	
	// Test the index / coordinate conversion functions:
	size_t tIdxCount = tGenome->getDatumCount();
	for(size_t i = 0; i < tIdxCount; i++) {
		// Get coordinates for index:
		vector<size_t> tCoords = tGenome->getCoordinates( i );
		// Get index for coordinates:
		size_t tConvert = tGenome->getIndex( &tCoords[0] );
		// If original index and convert don't match, mark error:
		if( tConvert != i ) {
			tErrCount++;
			cout << "ERROR! " << tConvert << " != " << i << endl;
		}
	}
	
	if( tErrCount == 0 ) {
		cout << "TEST PASSED. " << tGenome->getDatumCount() << endl;
		
		// Data access test:
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

