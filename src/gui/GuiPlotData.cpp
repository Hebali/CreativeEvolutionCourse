//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include "GuiPlotData.h"

using namespace std;
using namespace ci;
using namespace ci::app;

PlotterData::PlotterData(const ci::ColorA& iColor, const float& iStrokeWeight) :
	mColor( iColor ),
	mStrokeWeight( iStrokeWeight )
{
}

PlotterData::~PlotterData()
{
}

PlotterData* PlotterData::clone()
{
	return new PlotterData( mColor, mStrokeWeight );
}

void PlotterData::draw()
{
	// Overload this method.
}

void PlotterData::setStrokeColor(const ci::ColorA& iColor)
{
	mColor = iColor;
}

const ci::ColorA& PlotterData::getStrokeColor() const
{
	return mColor;
}

void PlotterData::setStrokeWeight(const float& iWeight)
{
	mStrokeWeight = iWeight;
}

const float& PlotterData::getStrokeWeight() const
{
	return mStrokeWeight;
}

PolyLineData::PolyLineData() :
	PlotterData()
{
}

PolyLineData::PolyLineData(const ci::PolyLine2f& iData, const ci::ColorA& iColor, const float& iStrokeWeight) :
	PlotterData( iColor, iStrokeWeight ), mData( iData )
{
}

PolyLineData::~PolyLineData()
{
}

PlotterData* PolyLineData::clone()
{
	return new PolyLineData( mData, mColor, mStrokeWeight );
}

void PolyLineData::draw()
{
	// Set stroke weight:
	gl::lineWidth( toPixels( mStrokeWeight ) );
	// Set stroke color:
	gl::color( mColor );
	// Draw data:
	gl::draw( mData );
}