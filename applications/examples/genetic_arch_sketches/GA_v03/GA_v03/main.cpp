//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include <iostream>

using namespace std;

// SKETCHING EXAMPLE: Preliminary Architectural Components for a Genetic Algorithm in C++

class Superclass {
public:
	Superclass()
	{
	}
	
	virtual ~Superclass()
	{
		cout << "~Superclass()" << endl;
	}
	
	virtual void getA()
	{
		cout << "CALLED: Superclass::getA()" << endl;
	}
	
	void getB()
	{
		cout << "CALLED: Superclass::getB()" << endl;
	}
};

class Subclass : public Superclass {
public:
	Subclass() : Superclass()
	{
	}
	
	~Subclass()
	{
		cout << "~Subclass()" << endl;
	}
	
	void getA()
	{
		cout << "CALLED: Subclass::getA()" << endl;
	}
	
	void getB()
	{
		cout << "CALLED: Subclass::getB()" << endl;
	}
};

int main(int argc, const char * argv[])
{
	Superclass* tObjSuper = new Superclass();
	
	cout << "Superclass* tObjSuper = new Superclass();" << endl;
	
	tObjSuper->getA();
	tObjSuper->getB();
	
	cout << "-----------" << endl;
	
	cout << "Superclass* tObjPolySub = new Subclass();" << endl;
	
	Superclass* tObjPolySub = new Subclass();
	
	tObjPolySub->getA();
	tObjPolySub->getB();
	
	cout << "-----------" << endl;
	
	cout << "Subclass* tObjSub = new Subclass();" << endl;
	
	Subclass* tObjSub = new Subclass();
	
	tObjSub->getA();
	tObjSub->getB();
	
	cout << "-----------" << endl;
	
	delete tObjSuper;
	delete tObjPolySub;
	delete tObjSub;
	
    return 0;
}

