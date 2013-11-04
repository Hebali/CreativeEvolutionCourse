//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include "GuiRect.h"

using namespace std;
using namespace ci;
using namespace ci::app;

UiRect::UiRect() : UiBase(), mFillColor( ColorA( 0.0, 0.0, 0.0, 0.0 ) ), mStrokeColor( ColorA( 0.0, 0.0, 0.0, 0.0 ) ), mStrokeWeight(1.0)
{
}

UiRect::~UiRect()
{
}

void UiRect::draw()
{
	// Compute draw rect:
	Vec2f tPos  = getPosition();
	Rectf tRect = Rectf( tPos, tPos + getDimension() );
	// Draw background:
	gl::color( mFillColor );
	gl::drawSolidRect( tRect );
	// Draw border:
	gl::color( mStrokeColor );
	gl::lineWidth( toPixels( mStrokeWeight ) );
	gl::drawStrokedRect( tRect );
}

void UiRect::setFillColor(const ci::ColorA& iColor)
{
	mFillColor = iColor;
}

const ci::ColorA& UiRect::getFillColor() const
{
	return mFillColor;
}

void UiRect::setStrokeColor(const ci::ColorA& iColor)
{
	mStrokeColor = iColor;
}

const ci::ColorA& UiRect::getStrokeColor() const
{
	return mStrokeColor;
}

void UiRect::setStrokeWeight(const float& iWeight)
{
	mStrokeWeight = iWeight;
}

const float& UiRect::getStrokeWeight() const
{
	return mStrokeWeight;
}
