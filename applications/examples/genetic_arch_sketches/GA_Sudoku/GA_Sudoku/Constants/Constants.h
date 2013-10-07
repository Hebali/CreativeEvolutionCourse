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

extern int		getPopulationSize();
extern int		getTestRunCount();
extern int		getTileAxis();
extern int		getTileCount();
extern int		getTileValueMin();
extern int		getTileValueMax();

extern bool		getBoardWin(int* iBoard, const size_t& iTileCount);

extern size_t	getTimeNow();

