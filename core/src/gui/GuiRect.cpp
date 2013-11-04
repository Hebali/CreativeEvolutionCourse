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

GuiRect::GuiRect() : GuiBase(), mFillColor( ColorA( 0.0, 0.0, 0.0, 0.0 ) ), mStrokeColor( ColorA( 0.0, 0.0, 0.0, 0.0 ) ), mStrokeWeight(1.0)
{
}

GuiRect::~GuiRect()
{
}

void GuiRect::draw()
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

void GuiRect::setFillColor(const ci::ColorA& iColor)
{
	mFillColor = iColor;
}

const ci::ColorA& GuiRect::getFillColor() const
{
	return mFillColor;
}

void GuiRect::setStrokeColor(const ci::ColorA& iColor)
{
	mStrokeColor = iColor;
}

const ci::ColorA& GuiRect::getStrokeColor() const
{
	return mStrokeColor;
}

void GuiRect::setStrokeWeight(const float& iWeight)
{
	mStrokeWeight = iWeight;
}

const float& GuiRect::getStrokeWeight() const
{
	return mStrokeWeight;
}
