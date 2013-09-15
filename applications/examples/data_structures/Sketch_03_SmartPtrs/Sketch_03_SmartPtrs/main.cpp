//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include <iostream>

#include "SmartPtr.h"

class TestClass {
public:
	TestClass(const std::string& iString) : mString( iString )
	{
		std::cout << "TestClass() began" << std::endl;
	}
	
	~TestClass()
	{
		std::cout << "~TestClass() ended" << std::endl;
	}
	
	void test()
	{
		std::cout << "TestClass::test() called: \'" << mString << "\'" << std::endl;
	}
	
	void set(const std::string& iString)
	{
		mString = iString;
	}
	
private:
	std::string mString;
};

int main(int argc, const char * argv[])
{
	SmartPtr<TestClass> tPtrA = SmartPtr<TestClass>( new TestClass( "Object A" ) );
	SmartPtr<TestClass> tPtrB = tPtrA;
	
	std::cout << "Testing A..." << std::endl;
	tPtrA.get()->test();
	std::cout << "Testing B..." << std::endl;
	tPtrB.get()->test();
	std::cout << "Changing label..." << std::endl;
	tPtrB.get()->set( "Object B" );
	std::cout << "Testing A..." << std::endl;
	tPtrA.get()->test();
	std::cout << "Testing B..." << std::endl;
	tPtrB.get()->test();
	
    return 0;
}

