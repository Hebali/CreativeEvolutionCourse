//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include <iostream>

#include "LinkedList.h"

int main(int argc, const char * argv[])
{
	LList<double> tList = LList<double>();
	
	
	for(double i = 0.0; i < 10.0; i += 1.0)
	{
		tList.push_front( i );
	}
	
	for(double i = 0.0; i < 10.0; i += 1.0)
	{
		tList.push_back( i );
	}
	
	tList.print();
	
	std::cout << "--------------" << std::endl << std::endl;
	
	tList.pop_front();
	tList.pop_back();
	
	tList.pop_front();
	tList.pop_back();
	
	tList.pop_front();
	tList.pop_back();
	
	tList.print();
	
	std::cout << "--------------" << std::endl << std::endl;
	
	size_t tCount = tList.size();
	std::cout << "Node count: " << tCount << std::endl;
	std::cout << "Value at front: " <<  tList.front()->getValue() << std::endl;
	std::cout << "Value at index #" << ( tCount / 2 ) << ": " << tList.at( tCount / 2 )->getValue() << std::endl;
	std::cout << "Value at back: " <<  tList.back()->getValue() << std::endl;
	
    return 0;
}

