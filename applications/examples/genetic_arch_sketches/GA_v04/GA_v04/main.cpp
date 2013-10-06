//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// SKETCHING EXAMPLE: Preliminary Architectural Components for a Genetic Algorithm in C++

typedef std::function<std::string(const int&,const int&)> TestFunc;

std::string myTestFunc(Thing* iA, const int& iB)
{
	stringstream ss;
	ss << "( " << iA << ", " << iB << " )";
	return ss.str();
}

class Aclass {
public:
	Aclass() : mFunc( NULL ), mA( 0 ), mB( 0 )
	{
	}
	
	~Aclass()
	{
	}
	
	void setFunction(TestFunc iFunc)
	{
		mFunc = iFunc;
	}
	
	void setA(const int& iVal)
	{
		mA = iVal;
	}
	
	void setB(const int& iVal)
	{
		mB = iVal;
	}
	
	void runFunction()
	{
		if( mFunc ) {
			string tStr = mFunc( mA, mB );
			cout << "Function output: " << tStr << endl;
		}
		else {
			cout << "Sorry. Function is not set!" << endl;
		}
	}
	
protected:
	TestFunc	mFunc;
	int			mA;
	int			mB;
};

int main(int argc, const char * argv[])
{
	Aclass* tObj = new Aclass();
	tObj->setA( 3 );
	tObj->setB( 5 );
	tObj->setFunction( myTestFunc );

	tObj->runFunction();
	
	delete tObj;
	
    return 0;
}

