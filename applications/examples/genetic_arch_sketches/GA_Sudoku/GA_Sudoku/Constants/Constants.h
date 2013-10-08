//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include <iostream>
#include <chrono>
#include <string>
#include <cmath>

/** @brief Returns the GA population size = 1000 */
extern int		getPopulationSize();

/** @brief Returns the GA population count = 50 */
extern int		getTestRunCount();

/** @brief Returns the Sudoku axis length = 9 */
extern int		getTileAxis();

/** @brief Returns the Sudoku tile count = 81 */
extern int		getTileCount();

/** @brief Returns the minimum Sudoku tile value = 1 */
extern int		getTileValueMin();

/** @brief Returns the maximum Sudoku tile value = 9 */
extern int		getTileValueMax();

/** @brief Returns the current time in milliseconds */
extern size_t	getTimeNow();

/** @brief Returns whether the input board represents a Sudoku win state */
extern bool		getBoardWin(int* iBoard, const size_t& iTileCount);

