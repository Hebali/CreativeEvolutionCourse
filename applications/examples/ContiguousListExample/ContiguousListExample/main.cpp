//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include <iostream>

#include "ContiguousList.h"

int main(int argc, const char * argv[])
{
	evo::types::CList<double> tList = evo::types::CList<double>();
	
	tList.push_back( 1.1 );
	tList.push_back( 2.1 );
	tList.push_back( 3.1 );
	//tList.print();
	
	tList.clear();
	tList.push_back( 5.1 );
	tList.push_back( 6.1 );
	tList.push_back( 7.1 );
	//std::cout << "Bracket operator access: " << tList[ 1 ] << std::endl;
	//tList.print();
	tList.clear();
	std::cout << "Size: " << tList.size() << std::endl;
	
	
    return 0;
}

