//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

/*
 Eight Queens Puzzle
 Overview: http://en.wikipedia.org/wiki/Eight_queens_puzzle
 
 Rule: In an N-by-N board, place N queens such that no two queens occupy the same row, column or diagonal.
 
	BOARD SIZE:		TOTAL SOLUTIONS:			UNIQUE SOLUTIONS:
	1 x 1				1							1
	2 x 2				0							0
	3 x 3				0							0
	4 x 4				2							1
	5 x 5				10							2
	6 x 6				4							1
	7 x 7				40							6
	8 x 8				92							12
	9 x 9				352							46
	10 x 10				724							92
	11 x 11				2,680						341
	12 x 12				14,200						1,787
	13 x 13				73,712						9,233
	14 x 14				365,596						45,752
	15 x 15				2,279,184					285,053
	16 x 16				14,772,512					1,846,955
	17 x 17				95,815,104					11,977,939
	18 x 18				666,090,624					83,263,591
	19 x 19				4,968,057,848				621,012,754
	20 x 20				39,029,188,884				4,878,666,808
	21 x 21				314,666,222,712				39,333,324,973
	22 x 22				2,691,008,701,644			336,376,244,042
	23 x 23				24,233,937,684,440			3,029,242,658,210
	24 x 24				227,514,171,973,736			28,439,272,956,934
	25 x 25				2,207,893,435,808,350		275,986,683,743,434

	Solutions that differ only by symmetry operations (rotations and reflections) of the board are not counted as unique.
 */

#include <iostream>

#include "EightQueens.h"

using namespace std;

int main(int argc, const char * argv[])
{
	NQueensBoard* tBoard = new NQueensBoard( 8 );
	
	tBoard->solveWithBacktracking();
	
	delete tBoard;
	
    return 0;
}

