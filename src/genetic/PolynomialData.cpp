//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include "PolynomialData.h"

using namespace std;
using namespace ci;
using namespace ci::app;

PolynomialData::PolynomialData(const float& iParamIn, const float& iParamOut,
							   const bool& iDrawFormula, const bool& iDrawDeriv,
							   const ci::ColorA& iColor, const float& iStrokeWeight) :
	PlotterData( iColor, iStrokeWeight ),
	mDrawRangeIn(iParamIn ),
	mDrawRangeOut( iParamOut ),
	mDrawFormula( iDrawFormula ),
	mDrawDeriv( iDrawDeriv ),
	mDirty( true )
{
	mDrawSamples = ( mDrawRangeOut - mDrawRangeIn ) * 100;
}

PolynomialData::~PolynomialData()
{
}

PlotterData* PolynomialData::clone()
{
	PolynomialData* tClone = new PolynomialData( mDrawRangeIn, mDrawRangeOut, mDrawFormula, mDrawDeriv, mColor, mStrokeWeight );
	for(ComponentVecCiter it = mComponents.begin(); it != mComponents.end(); it++) {
		tClone->addComponent( (*it).first, (*it).second );
	}
	return tClone;
}

void PolynomialData::draw()
{
	// Set stroke weight:
	gl::lineWidth( toPixels( mStrokeWeight ) );
	// Set stroke color:
	gl::color( mColor );
	// Draw data:	
	if( mDrawFormula ) {
		glBegin( GL_LINE_STRIP );
		for(size_t i = 0; i < mDrawSamples; i++) {
			// Compute current t:
			float t = lmap<float>( i, 0.0, mDrawSamples - 1.0, mDrawRangeIn, mDrawRangeOut );
			glVertex2f( t, getValue( t ) );
		}
		glEnd();
	}
	// Draw derivative data (with stipple):
	if( mDrawDeriv ) {
		glPushAttrib( GL_ENABLE_BIT );
		glLineStipple( toPixels( 10 ), 0xAAAA );
		glEnable( GL_LINE_STIPPLE );
		glBegin( GL_LINE_STRIP );
		for(size_t i = 0; i < mDrawSamples; i++) {
			float t = lmap<float>( i, 0.0, mDrawSamples - 1.0, mDrawRangeIn, mDrawRangeOut );
			glVertex2f( t, getDerivativeValue( t ) );
		}
		glEnd();
		glDisable( GL_LINE_STIPPLE );
		glPopAttrib();
	}
}

void PolynomialData::setDrawParameters(const float& iParamIn, const float &iParamOut,
									   const bool& iDrawFormula, const bool& iDrawDeriv,
									   const ci::ColorA& iColor, const float& iStrokeWeight)
{
	mDrawRangeIn  = iParamIn;
	mDrawRangeOut = iParamOut;
	mDrawFormula  = iDrawFormula;
	mDrawDeriv	  = iDrawDeriv;
	mColor		  = iColor;
	mStrokeWeight = iStrokeWeight;
	mDrawSamples  = ( mDrawRangeOut - mDrawRangeIn ) * 100;
	mDirty        = true;
}

void PolynomialData::addComponent(const float& iCoeff, const float& iExpon)
{
	mComponents.push_back( ComponentPair( iCoeff, iExpon ) );
	mDirty = true;
}

PolynomialData::ComponentVec& PolynomialData::getComponents()
{
	return mComponents;
}

const PolynomialData::ComponentVec& PolynomialData::getComponents() const
{
	return mComponents;
}

float PolynomialData::getValue(const float& iParam) const
{
	// Prepare output:
	float tOut = 0.0;
	// Iterate over components and sum output:
	for(ComponentVecCiter it = mComponents.begin(); it != mComponents.end(); it++) {
		tOut += (*it).first * pow( iParam, (*it).second );
	}
	// Return output:
	return tOut;
}

float PolynomialData::getDerivativeValue(const float& iParam) const
{
	// Prepare output:
	float tOut = 0.0;
	// Iterate over components and sum output:
	for(ComponentVecCiter it = mComponents.begin(); it != mComponents.end(); it++) {
		tOut += ( (*it).first * (*it).second ) * pow( iParam, (*it).second - 1.0 );
	}
	// Return output:
	return tOut;
}

string PolynomialData::getFormulaString() const
{
	stringstream ss;
	ss << setprecision( 5 ) << "f(t) = ";
	for(ComponentVecCiter it = mComponents.begin(); it != mComponents.end(); it++) {
		ss << ( ( (*it).first < 0.0 ) ? ( " - " ) : ( ( ( it == mComponents.begin() ) ? ( "" ) : ( " + " ) ) ) );
		ss << fabs( (*it).first );
		
		if( (*it).second == 1.0 ) { ss << "t"; }
		else if( (*it).second != 0.0 ) { ss << "t^" << (*it).second; }
	}
	return ss.str();
}

string PolynomialData::getDerivativeFormulaString() const
{
	stringstream ss;
	ss << setprecision( 5 ) << "df(t) = ";
	for(ComponentVecCiter it = mComponents.begin(); it != mComponents.end(); it++) {
		float tCoeff = (*it).first * (*it).second;
		float tExpon = (*it).second - 1.0;
		ss << ( ( tCoeff < 0.0 ) ? ( " - " ) : ( ( ( it == mComponents.begin() ) ? ( "" ) : ( " + " ) ) ) );
		ss << fabs( tCoeff );
		
		if( tExpon == 1.0 ) { ss << "t"; }
		else if( tExpon != 0.0 ) { ss << "t^" << tExpon; }
	}
	return ss.str();
}
