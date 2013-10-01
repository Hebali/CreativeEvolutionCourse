//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include "NumericData.h"

using namespace std;

// SKETCHING EXAMPLE: Preliminary Architectural Components for a Genetic Algorithm in C++

int main(int argc, const char * argv[])
{
	size_t tComponentCount = 3;
	
	Data<double> tFeat = Data<double>( tComponentCount );
	
	tFeat.pushComponent( 0.0 );
	tFeat.pushComponent( 0.1 );
	tFeat.pushComponent( 0.2 );
	
	tFeat.pushComponent( 1.0 );
	tFeat.pushComponent( 1.1 );
	tFeat.pushComponent( 1.2 );
	
	tFeat.pushComponent( 2.0 );
	tFeat.pushComponent( 2.1 );
	tFeat.pushComponent( 2.2 );
	
	tFeat.pushComponent( 3.0 );
	tFeat.pushComponent( 3.1 );
	tFeat.pushComponent( 3.2 );
	
	tFeat.pushComponent( 4.0 );
	tFeat.pushComponent( 4.1 );
	tFeat.pushComponent( 4.2 );
	
	Data<double>::Array tNewCol;
	tNewCol.push_back( 0.3 );
	tNewCol.push_back( 1.3 );
	tNewCol.push_back( 2.3 );
	tNewCol.push_back( 3.3 );
	tNewCol.push_back( 4.3 );
	tFeat.pushColumn( tNewCol );
	
	tFeat.pushEmptyColumn();
	tFeat.pushEmptyRow();
	
	tFeat.getComponentAt( 5, 4 ) = 9.9;
	
	size_t tFeatCount = tFeat.getRowCount();
	cout << "feature count: " << tFeatCount <<endl;
	
	cout << "Feature-first matrix: \n";
	Data<double>::Matrix tMatrixFf = tFeat.getRowFirstData();
	for(Data<double>::Matrix::const_iterator itMat = tMatrixFf.begin(); itMat != tMatrixFf.end(); itMat++) {
		for(Data<double>::Array::const_iterator itArr = (*itMat).begin(); itArr != (*itMat).end(); itArr++) {
			printf( "%1.1f ", (*itArr) );
		}
		cout << endl;
	}
	
	cout << "Component-first matrix: \n";
	Data<double>::Matrix tMatrixCf = tFeat.getColumnFirstData();
	for(Data<double>::Matrix::const_iterator itMat = tMatrixCf.begin(); itMat != tMatrixCf.end(); itMat++) {
		for(Data<double>::Array::const_iterator itArr = (*itMat).begin(); itArr != (*itMat).end(); itArr++) {
			printf( "%1.1f ", (*itArr) );
		}
		cout << endl;
	}
	
	cout << "Feature-first iterator: \n";
	Data<double>::Iterator it = tFeat.getRowFirstIterator();
	while( it.hasNext() ) {
		double tItem = it.next();
		printf( "%1.1f ", (tItem) );
		cout << endl;
	}
	
	cout << "Component-first iterator: \n";
	Data<double>::Iterator itCompWise = tFeat.getColumnFirstIterator();
	while( itCompWise.hasNext() ) {
		double tItem = itCompWise.next();
		printf( "%1.1f ", (tItem) );
		cout << endl;
	}
	
	cout << "Column #2: \n";
	Data<double>::Array tCol2 = tFeat.getColumn( 2 );
	for(Data<double>::Array::const_iterator itArr = tCol2.begin(); itArr != tCol2.end(); itArr++) {
		printf( "%1.1f ", (*itArr) );
	}
	cout << endl;
	
	cout << "Row #2: \n";
	Data<double>::Array tRow2 = tFeat.getRow( 2 );
	for(Data<double>::Array::const_iterator itArr = tRow2.begin(); itArr != tRow2.end(); itArr++) {
		printf( "%1.1f ", (*itArr) );
	}
	cout << endl;
	
	cout << "DONE\n";
	
    return 0;
}

