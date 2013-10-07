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

static const int kPopulationSize  = 1000;
static const int kTestRunCount    = 50;

static const int kBoardAxisLen    = 9;
static const int kBoardTotalTiles = kBoardAxisLen * kBoardAxisLen;

static const int kTileValueMin    = 1;
static const int kTileValueMax    = kBoardAxisLen;

/**
 * @brief Static function returns elapsed milliseconds since 00:00:00 UTC on 1 January 1970
 */
inline size_t getEpochMilliseconds()
{
	auto tNow = std::chrono::system_clock::now();
	auto tEla = tNow.time_since_epoch();
	auto tMil = std::chrono::duration_cast<std::chrono::milliseconds>( tEla );
	return tMil.count();
}
