//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include <iostream>
#include <limits>
#include <string>

using namespace std;

/** @brief An example union of numeric data types */
union NumericUnion
{
	bool			mBool;
	char			mChar;
	unsigned int	mUint;
	int				mInt;
	long			mLong;
	float			mFloat;
	double			mDouble;
};

/** @brief An example union of numeric and string data types */
union GenericUnion
{
	bool			mBool;
	char			mChar;
	unsigned int	mUint;
	int				mInt;
	long			mLong;
	float			mFloat;
	double			mDouble;
	const char*		mCstring;
	std::string		mString;
};

/** @brief An example struct containing numeric data types */
struct NumericStruct
{
	bool			mBool;
	char			mChar;
	unsigned int	mUint;
	int				mInt;
	long			mLong;
	float			mFloat;
	double			mDouble;
};

/** @brief An example struct containing numeric and string data types */
struct GenericStruct
{
	bool			mBool;
	char			mChar;
	unsigned int	mUint;
	int				mInt;
	long			mLong;
	float			mFloat;
	double			mDouble;
	const char*		mCstring;
	std::string		mString;
};


int main(int argc, const char * argv[])
{
	cout << "-----------------------------------------------------------" << endl;
	cout << "TYPES:" << endl << endl << endl;
	
	cout << "bool:" << endl;
	cout << "\tSize: " << sizeof( bool ) << " byte(s)" << endl;
	cout << "\tRange: ( " << numeric_limits<bool>::min() << ", " << numeric_limits<bool>::max() << " )" << endl << endl;
	
	cout << "char:" << endl;
	cout << "\tSize: " << sizeof( char ) << " byte(s)" << endl;
	cout << "\tRange: ( " << (int)numeric_limits<char>::min() << ", " << (int)numeric_limits<char>::max() << " )" << endl << endl;
	
	cout << "unsigned int:" << endl;
	cout << "\tSize: " << sizeof( unsigned int ) << " byte(s)" << endl;
	cout << "\tRange: ( " << numeric_limits<unsigned int>::min() << ", " << numeric_limits<unsigned int>::max() << " )" << endl << endl;
	
	cout << "int:" << endl;
	cout << "\tSize: " << sizeof( int ) << " byte(s)" << endl;
	cout << "\tRange: ( " << numeric_limits<int>::min() << ", " << numeric_limits<int>::max() << " )" << endl << endl;
	
	cout << "long:" << endl;
	cout << "\tSize: " << sizeof( long ) << " byte(s)" << endl;
	cout << "\tRange: ( " << numeric_limits<long>::min() << ", " << numeric_limits<long>::max() << " )" << endl << endl;
	
	cout << "float:" << endl;
	cout << "\tSize: " << sizeof( float ) << " byte(s)" << endl;
	cout << "\tRange: ( " << numeric_limits<float>::min() << ", " << numeric_limits<float>::max() << " )" << endl << endl;
	
	cout << "double:" << endl;
	cout << "\tSize: " << sizeof( double ) << " byte(s)" << endl;
	cout << "\tRange: ( " << numeric_limits<double>::min() << ", " << numeric_limits<double>::max() << " )" << endl << endl;
	
	cout << "const char*:" << endl;
	cout << "\tSize: " << sizeof( const char* ) << " byte(s)" << endl;
	cout << "\tRange: N/A" << endl << endl;
	
	cout << "std::string:" << endl;
	cout << "\tSize: " << sizeof( std::string ) << " byte(s)" << endl;
	cout << "\tRange: N/A" << endl << endl;
	
	cout << "-----------------------------------------------------------" << endl;
	cout << "UNIONS AND STRUCTS:" << endl << endl << endl;
	
	cout << "NumericUnion:" << endl;
	cout << "\tSize: " << sizeof( NumericUnion ) << " byte(s)" << endl << endl;
	
	cout << "GenericUnion:" << endl;
	cout << "\tSize: " << sizeof( GenericUnion ) << " byte(s)" << endl << endl;
	
	cout << "NumericStruct:" << endl;
	cout << "\tSize: " << sizeof( NumericStruct ) << " byte(s)" << endl << endl;
	
	cout << "GenericStruct:" << endl;
	cout << "\tSize: " << sizeof( GenericStruct ) << " byte(s)" << endl << endl;
	
	cout << "-----------------------------------------------------------" << endl;
	cout << "ARRAYS:" << endl << endl << endl;
	
	int arrayA[10];
	int arrayB[1000];
	
	cout << "int arrayA[10]:" << endl;
	cout << "\tSize: " << sizeof( arrayA ) << " byte(s)" << endl;
	cout << "\tLength: " << ( sizeof( arrayA ) / sizeof( int ) ) << endl << endl;
	
	cout << "int arrayB[1000]:" << endl;
	cout << "\tSize: " << sizeof( arrayB ) << " byte(s)" << endl;
	cout << "\tLength: " << ( sizeof( arrayB ) / sizeof( int ) ) << endl << endl;
	
	int* arrayC = new int[10];
	int* arrayD = new int[1000];
	
	cout << "int* arrayC = new int[10]:" << endl;
	cout << "\tSize: " << sizeof( arrayC ) << " byte(s)" << endl;
	cout << "\tLength: Cannot be inferred from pointer" << endl << endl;
	
	cout << "int* arrayD = new int[1000]:" << endl;
	cout << "\tSize: " << sizeof( arrayD ) << " byte(s)" << endl;
	cout << "\tLength: Cannot be inferred from pointer" << endl << endl;
	
	delete [] arrayC;
	delete [] arrayD;
	
    return 0;
}

