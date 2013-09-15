//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include <iostream>

/**
 * @brief A recursive-backtracking solution to the N-Queens Puzzle
 */
class NQueensBoard {
public:
	/** @brief Constructor for an N-Queens Puzzle Solver. Default: N = 8 */
	NQueensBoard(int iTilesPerAxis = 8);
	
	/** @brief Destructor */
	~NQueensBoard();
	
	/** @brief Finds and prints all possible solutions to the n-queens puzzle for the given board size */
	void		solveWithBacktracking();
	
private:
	/** @brief Returns true if a queen can be placed within the row occupied by ( iRow, iCol ) */
	bool		rowIsSafe(const int& iRow, const int& iCol) const;
	
	/** @brief Returns true if a queen can be placed within the column occupied by ( iRow, iCol ) */
	bool		columnIsSafe(const int& iRow, const int& iCol) const;
	
	/** @brief Returns true if a queen can be placed within a component diagonal stemming from ( iRow, iCol ) in an ( iRowUp, iColUp ) dirction */
	bool		diagonalIsSafe(const int& iRow, const bool& iRowUp, const int& iCol, const bool& iColUp) const;
	
	/** @brief Returns true if a queen can be placed within the tile occupied by ( iRow, iCol ) */
	bool		tileIsSafe(const int& iRow, const int& iCol) const;
	
	/** @brief Prints an ascii representation of the current board state to the console */
	void		printBoard() const;
	
	/** @brief The recursive function that handles queen placement and backtracking within the algorithm */
	bool		recursiveSolve(const int& iCol);
	
	int			mTilesPerAxis;		//!< The number of tiles per axis in the two-dimensional board
	bool**		mBoard;				//!< A two-dimensional dynamic bool array storing the board state
	
	int			mSolutionCount;		//!< Stores the number of solutions for the current N
	int			mTotalCallCount;	//!< Stores the total number of calls made while iterating all solutions for the current N
	int			mTempCallCount;		//!< Stores the number of calls made during the current solution iteration
};