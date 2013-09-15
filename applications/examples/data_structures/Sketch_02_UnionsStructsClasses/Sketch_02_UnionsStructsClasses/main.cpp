//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include <iostream>
#include <string>

using namespace std;

/** @brief An example union of numeric data types */
union NumericUnion
{
	bool	mBool;
	int		mInt;
	float	mFloat;
};

/** @brief An example struct containing numeric data types */
struct NumericStruct
{
	bool	mBool;
	int		mInt;
	float	mFloat;
};

/** @brief An enumeration of supported numeric types */
enum NumericType
{
	T_NULL, T_BOOL, T_INT, T_FLOAT
};

/** @brief An example class containing a union of numeric data types */
class NumericUnionClass
{
public:
	/** @brief Default constructor */
	NumericUnionClass() : mType(T_NULL) { /* no-op */ }
	/** @brief Empty destructor */
	~NumericUnionClass() { /* no-op */ }
	
	const NumericType& getType() const
	{
		return mType;
	}
	
	bool isBool() const
	{
		return ( mType == T_BOOL );
	}
	
	bool isInt() const
	{
		return ( mType == T_INT );
	}
	
	bool isFloat() const
	{
		return ( mType == T_FLOAT );
	}
	
	bool& getBool()
	{
		return mUnion.mBool;
	}
	
	int& getInt()
	{
		return mUnion.mInt;
	}
	
	float& getFloat()
	{
		return mUnion.mFloat;
	}
	
	void setBool(const bool& iBool)
	{
		mUnion.mBool = iBool;
		mType = T_BOOL;
	}
	
	void setInt(const int& iInt)
	{
		mUnion.mInt = iInt;
		mType = T_INT;
	}
	
	void setFloat(const float& iFloat)
	{
		mUnion.mFloat = iFloat;
		mType = T_FLOAT;
	}
	
private:
	NumericType		mType;	//!< The type currently being stored
	NumericUnion	mUnion; //!< The internal copy of the union
};

int main(int argc, const char * argv[])
{
	NumericUnion tUnion;
	
	cout << "-----------------------------------------------------------" << endl;
	cout << "SET: tUnion.mInt = 123;" << endl << endl << endl;
	tUnion.mInt   = 123;
	
	cout << "GET:" << endl;
	cout << "tUnion.mBool   = " << tUnion.mBool << endl;
	cout << "tUnion.mInt    = " << tUnion.mInt << endl;
	cout << "tUnion.mFloat  = " << tUnion.mFloat << endl;
	
	cout << endl << endl;
	
	cout << "-----------------------------------------------------------" << endl;
	cout << "SET: tUnion.mFloat = 456.7;" << endl << endl << endl;
	tUnion.mFloat = 456.7;
	
	cout << "GET:" << endl;
	cout << "tUnion.mBool   = " << tUnion.mBool << endl;
	cout << "tUnion.mInt    = " << tUnion.mInt << endl;
	cout << "tUnion.mFloat  = " << tUnion.mFloat << endl;
	
	NumericStruct tStruct;
	
	cout << "-----------------------------------------------------------" << endl;
	cout << "SET: tStruct.mInt = 123;" << endl << endl << endl;
	tStruct.mInt   = 123;
	
	cout << "GET:" << endl;
	cout << "tStruct.mBool   = " << tStruct.mBool << endl;
	cout << "tStruct.mInt    = " << tStruct.mInt << endl;
	cout << "tStruct.mFloat  = " << tStruct.mFloat << endl;
	
	cout << endl << endl;
	
	cout << "-----------------------------------------------------------" << endl;
	cout << "SET: tStruct.mFloat = 456.7;" << endl << endl << endl;
	tStruct.mFloat = 456.7;
	
	cout << "GET:" << endl;
	cout << "tStruct.mBool   = " << tStruct.mBool << endl;
	cout << "tStruct.mInt    = " << tStruct.mInt << endl;
	cout << "tStruct.mFloat  = " << tStruct.mFloat << endl;
	
	cout << "-----------------------------------------------------------" << endl;
	cout << "tUnionClass.setFloat( 123.4 );" << endl << endl;
	
	NumericUnionClass tUnionClass = NumericUnionClass();
	tUnionClass.setFloat( 123.4 );
	
	if( tUnionClass.isBool() ) {
		cout << "tUnionClass.mUnion.mBool = " << tUnionClass.getBool() << endl;
	}
	else {
		cout << "tUnionClass does not contain a bool!" << endl;
	}
	
	if( tUnionClass.isInt() ) {
		cout << "tUnionClass.mUnion.mInt = " << tUnionClass.getInt() << endl;
	}
	else {
		cout << "tUnionClass does not contain an int!" << endl;
	}
	
	if( tUnionClass.isFloat() ) {
		cout << "tUnionClass.mUnion.mFloat = " << tUnionClass.getFloat() << endl;
	}
	else {
		cout << "tUnionClass does not contain a float!" << endl;
	}
	
	cout << endl << endl;
	
	return 0;
}


