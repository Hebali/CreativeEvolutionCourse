//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include <memory>

#include "cinder/PolyLine.h"

typedef std::shared_ptr<class PlotterData>		PlotterDataRef;				//!< A shared pointer to a PlotterData item
typedef std::vector<PlotterDataRef>				PlotterDataRefVec;			//!< A vector of PlotterDataRef items
typedef PlotterDataRefVec::iterator				PlotterDataRefVecIter;		//!< An iterator type for a vector of PlotterDataRef items
typedef PlotterDataRefVec::reverse_iterator		PlotterDataRefVecRiter;		//!< A reverse iterator type for a vector of PlotterDataRef items
typedef PlotterDataRefVec::const_iterator		PlotterDataRefVecCiter;		//!< A const iterator type for a vector of PlotterDataRef items

/** 
 * @brief Base class representing data to be plotted by GuiPlot 
 */
class PlotterData {
protected:
	
	ci::ColorA	mColor;			//!< The data's stroke color
	float		mStrokeWeight;	//!< The data's stroke weight
	
public:
	
	/** @brief Basic constructor */
	PlotterData(const ci::ColorA& iColor = ci::ColorA::white(), const float& iStrokeWeight = 3.0);
	
	/** @brief Virtual destructor */
	virtual ~PlotterData();
	
	/** @brief Returns a clone of this item */
	virtual PlotterData*	clone();
	
	/** @brief An overloadable draw method */
	virtual void			draw();
	
	/** @brief Sets the data's stroke color */
	void					setStrokeColor(const ci::ColorA& iColor);
	
	/** @brief Returns the data's stroke color */
	const ci::ColorA&		getStrokeColor() const;
	
	/** @brief Sets the data's stroke weight */
	void					setStrokeWeight(const float& iStrokeWeight);
	
	/** @brief Returns the data's stroke weight */
	const float&			getStrokeWeight() const;
};

/**
 * @brief Implements a subclass of PlotterData that stores ci::PolyLine2f data
 */
class PolyLineData : public PlotterData {
protected:
	
	ci::PolyLine2f	mData; //!< The 2D PolyLine data
	
public:
	
	/** @brief Default constructor */
	PolyLineData();
	
	/** @brief Basic constructor */
	PolyLineData(const ci::PolyLine2f& iData, const ci::ColorA& iColor = ci::ColorA::white(), const float& iStrokeWeight = 3.0);
	
	/** @brief Virtual destructor */
	virtual ~PolyLineData();
	
	/** @brief Returns a clone of this item */
	virtual PlotterData*	clone();
	
	/** @brief An overloadable draw method */
	virtual void			draw();
};
