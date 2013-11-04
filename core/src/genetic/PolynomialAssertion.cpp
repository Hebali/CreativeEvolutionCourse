//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include "PolynomialAssertion.h"

using namespace std;
using namespace ci;
using namespace ci::app;

Assertion::Assertion() :
	mRangeIn( 0.0 ),
	mRangeOut( 0.0 ),
	mType( IS_EQUAL ),
	mModeLhs( FOR_FUNCTION ),
	mModeRhs( FOR_FUNCTION ),
	mDataRhs( nullptr ),
	mScoreWeight( 1.0 )
{
}

float Assertion::applyTo(PolynomialDataRef iLhsRef) const
{
	// Prepare score:
	float tScore = 0.0;
	// Prepare sample count:
	size_t tSamples = ( mRangeOut - mRangeIn ) * 100;
	// Iterate over samples:
	for(size_t i = 0; i < tSamples; i++) {
		float tParam = lmap<float>( i, 0, tSamples - 1, mRangeIn, mRangeOut );
		// Get right-hand value:
		float tLhsValue = ( ( mModeLhs == FOR_FUNCTION ) ? ( iLhsRef->getValue( tParam ) ) : ( iLhsRef->getDerivativeValue( tParam ) ) );
		float tRhsValue = ( ( mModeRhs == FOR_FUNCTION ) ? ( mDataRhs->getValue( tParam ) ) : ( mDataRhs->getDerivativeValue( tParam ) ) );
		// Check assertion:
		switch( mType ) {
			case IS_EQUAL :   { if( tLhsValue == tRhsValue ) { tScore += 1.0; } break; }
			case IS_NEQUAL :  { if( tLhsValue != tRhsValue ) { tScore += 1.0; } break; }
			case IS_GREATER : { if( tLhsValue >  tRhsValue ) { tScore += 1.0; } break; }
			case IS_LESS :    { if( tLhsValue <  tRhsValue ) { tScore += 1.0; } break; }
			case IS_GEQUAL :  { if( tLhsValue >= tRhsValue ) { tScore += 1.0; } break; }
			case IS_LEQUAL :  { if( tLhsValue <= tRhsValue ) { tScore += 1.0; } break; }
			default : { break; }
		}

	}
	tScore /= (float)tSamples;
	return tScore * mScoreWeight;
}

std::string Assertion::getAssertionString(PolynomialDataRef iLhsRef) const
{
	stringstream ss;
	ss << "Assert :\t" << ( ( mModeLhs == FOR_FUNCTION ) ? ( iLhsRef->getFormulaString() ) : ( iLhsRef->getDerivativeFormulaString() ) );
	ss <<  "   " << AssertTypeSymbols[ mType ] << "   ";
	ss << ( ( mModeRhs == FOR_FUNCTION ) ? ( mDataRhs->getFormulaString() ) : ( mDataRhs->getDerivativeFormulaString() ) );
	ss << "\tIn range: [ " << mRangeIn << ", " << mRangeOut << " ]";
	ss << "\tScore: " << applyTo( iLhsRef );
	return ss.str();
}

void Assertion::setDataRhs(PolynomialDataRef iDataRhs)
{
	mDataRhs = iDataRhs;
}

PolynomialDataRef Assertion::getDataRhs() const
{
	return mDataRhs;
}

void Assertion::setParameterRange(const float& iParamIn, const float& iParamOut)
{
	mRangeIn  = iParamIn;
	mRangeOut = iParamOut;
}

const float& Assertion::getParameterRangeIn() const
{
	return mRangeIn;
}

const float& Assertion::getParameterRangeOut() const
{
	return mRangeOut;
}

void Assertion::setScoreWeight(const float& iWeight)
{
	mScoreWeight = iWeight;
}

const float& Assertion::getScoreWeight() const
{
	return mScoreWeight;
}

void Assertion::setType(const AssertType& iType)
{
	mType = iType;
}

const AssertType& Assertion::getType() const
{
	return mType;
}

void Assertion::setMode(const AssertMode& iModeLhs, const AssertMode& iModeRhs)
{
	mModeLhs = iModeLhs;
	mModeRhs = iModeRhs;
}

void Assertion::setModeLhs(const AssertMode& iModeLhs)
{
	mModeLhs = iModeLhs;
}

const AssertMode& Assertion::getModeLhs() const
{
	return mModeLhs;
}

void Assertion::setModeRhs(const AssertMode& iModeRhs)
{
	mModeRhs = iModeRhs;
}

const AssertMode& Assertion::getModeRhs() const
{
	return mModeRhs;
}

AssertionGroup::AssertionGroup()
{
}

bool AssertionGroup::empty() const
{
	return mAssertions.empty();
}

size_t AssertionGroup::size() const
{
	return mAssertions.size();
}

void AssertionGroup::clear()
{
	mAssertions.clear();
}

void AssertionGroup::add(AssertionRef iAssertion)
{
	mAssertions.push_back( iAssertion );
}

float AssertionGroup::applyTo(PolynomialDataRef iLhsRef) const
{
	float tAvgScore = 0.0;
	if( mAssertions.empty() ) { return tAvgScore; }
	for(AssertionRefVecCiter it = mAssertions.begin(); it != mAssertions.end(); it++) {
		tAvgScore += (*it)->applyTo( iLhsRef );
	}
	tAvgScore /= (float)mAssertions.size();
	return tAvgScore;
}

string AssertionGroup::getAssertionString(PolynomialDataRef iLhsRef) const
{
	string tStr = "";
	for(AssertionRefVecCiter it = mAssertions.begin(); it != mAssertions.end(); it++) {
		tStr += (*it)->getAssertionString( iLhsRef ) + "\n";
	}
	return tStr;
}