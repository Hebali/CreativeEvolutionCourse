//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include "EightQueens.h"

using namespace std;

NQueensBoard::NQueensBoard(int iTilesPerAxis)
: mTilesPerAxis(iTilesPerAxis), mSolutionCount(0), mTotalCallCount(0), mTempCallCount(0)
{
	// Initialize rows:
	mBoard = new bool*[mTilesPerAxis];
	//Iterate over each row:
	for(int i = 0; i < mTilesPerAxis; i++) {
		// Initialize column for current row:
		mBoard[i] = new bool[mTilesPerAxis];
		// Iterate over each column:
		for(int j = 0; j < mTilesPerAxis; j++) {
			// Initialize each tile on board to false (non-queen):
			mBoard[i][j] = false;
		}
	}
}

NQueensBoard::~NQueensBoard()
{
	// Delete each row:
	for(int i = 0; i < mTilesPerAxis; i++) {
		delete [] mBoard[ i ];
	}
	// Delete board:
	delete [] mBoard;
}

void NQueensBoard::solveWithBacktracking()
{
	// Start the recursive process:
	recursiveSolve( 0 );
	// Print the total number of calls:
	cout << "Total calls to recursiveSolve(): " << mTotalCallCount << endl;
}

bool NQueensBoard::rowIsSafe(const int& iRow, const int& iCol) const
{
	// Iterate over each column for row (except iCol):
	for(int i = 0; i < iCol; i++) {
		if( mBoard[iRow][i] ) { return false; }
	}
	for(int i = iCol + 1; i < mTilesPerAxis; i++) {
		if( mBoard[iRow][i] ) { return false; }
	}
	return true;
}

bool NQueensBoard::columnIsSafe(const int& iRow, const int& iCol) const
{
	// Iterate over each row for column (except iRow):
	for(int i = 0; i < iRow; i++) {
		if( mBoard[i][iCol] ) { return false; }
	}
	for(int i = iRow + 1; i < mTilesPerAxis; i++) {
		if( mBoard[i][iCol] ) { return false; }
	}
	return true;
}

bool NQueensBoard::diagonalIsSafe(const int& iRow, const bool& iRowUp, const int& iCol, const bool& iColUp) const
{
	int r = iRow + ( iRowUp ? -1 : 1 );
	int c = iCol + ( iColUp ? -1 : 1 );
	// Loop while in bounds:
	while( r >= 0 && r < mTilesPerAxis && c >= 0 && c < mTilesPerAxis ) {
		if( mBoard[r][c] ) {
			return false;
		}
		// Advance row iterator:
		if( iRowUp ) { r--; }
		else         { r++; }
		// Advance column iterator:
		if( iColUp ) { c--; }
		else         { c++; }
	}
	return true;
}

bool NQueensBoard::tileIsSafe(const int& iRow, const int& iCol) const
{
	if( !rowIsSafe( iRow, iCol ) )                    { return false; }
	if( !columnIsSafe( iRow, iCol ) )                 { return false; }
	if( !diagonalIsSafe( iRow, false, iCol, false ) ) { return false; }
	if( !diagonalIsSafe( iRow, true,  iCol, false ) ) { return false; }
	if( !diagonalIsSafe( iRow, true,  iCol, true  ) ) { return false; }
	if( !diagonalIsSafe( iRow, false, iCol, true  ) ) { return false; }
	return true;
}

void NQueensBoard::printBoard() const
{
	cout << "BOARD SOLUTION #" << mSolutionCount << " required " << mTempCallCount << " calls to recursiveSolve():" << endl << endl;
	//Iterate over each row:
	for(int i = 0; i < mTilesPerAxis; i++) {
		// Iterate over each column:
		for(int j = 0; j < mTilesPerAxis; j++) {
			// If current tile has queen, print it:
			if( mBoard[i][j] ) { cout << "\tQ"; }
			// Otherwise, print blank tile:
			else               { cout << "\t-"; }
		}
		cout << endl << endl;
	}
}

bool NQueensBoard::recursiveSolve(const int& iCol)
{
	// Increment recursion count (just for analytics):
	mTempCallCount++;
	// Iterate over each row of the current column:
	for(int r = 0; r < mTilesPerAxis; r++) {
		// Place queen at the current row and column:
		mBoard[r][iCol] = true;
		// Check if it is safe to place a queen
		// in current row of the current column:
		if( tileIsSafe( r, iCol ) ) {
			// If the current column index is the final one,
			// then we have reached a solution state:
            if( iCol == mTilesPerAxis - 1 ) {
				// Increment the solution count:
				mSolutionCount++;
				// Print board:
				printBoard();
				// Add temporary call count to total (just for analytics):
				mTotalCallCount += mTempCallCount;
				// Reset the temporary call count:
				mTempCallCount = 0;
			}
			// Recursively call this method on the next column:
            else {
				recursiveSolve( iCol + 1 );
			}
		}
		// Un-place queen at the current row and column:
		mBoard[r][iCol] = false;
	}
	return false;
}