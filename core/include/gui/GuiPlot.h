//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include "GuiRect.h"
#include "GuiText.h"
#include "GuiPlotData.h"

/**
 * @brief A 2D plotting widget
 */
class GuiPlot : public GuiRect {
protected:
	
	PlotterDataRefVec		mInputs;			//!< A vector of input references to be plotted
	ci::Rectf				mRange;				//!< The 2D drawing region, formatted as: ( MinX, MinY, MaxX, MaxY )
	ci::ColorA				mOriginColor;		//!< The stroke color of origin lines
	ci::ColorA				mGridColor;			//!< The stroke color of grid lines
	ci::ColorA				mDataColor;			//!< The stroke color of data lines
	float					mOriginWeight;		//!< The stroke weight of origin lines
	float					mGridWeight;		//!< The stroke weight of grid lines
	
	GuiText*				mLabelTL;			//!< A pointer to the top-left label child
	GuiText*				mLabelTR;			//!< A pointer to the top-right label child
	GuiText*				mLabelBL;			//!< A pointer to the bottom-left label child
	GuiText*				mLabelBR;			//!< A pointer to the bottom-right label child
	GuiText*				mLabelCursor;		//!< A pointer to the cursor label child
	
	FontSuitcase*			mFontSuitcaseRef;	//!< A pointer to the global font suitcase
	
	bool					mDirty;				//!< Flags whether internal formatting needs updating
	
public:
	
	/** @brief Basic constructor */
	GuiPlot(const std::string& iFontFamilyName = "", FontSuitcase* iFontSuitcaseRef = NULL);
	
	/** @brief Virtual destructor */
	virtual ~GuiPlot();
	
	/** @brief An overloadable draw method */
	virtual void			draw();
	
	/** @brief Overloadable mouse move event callback method */
	virtual bool			mouseMove(ci::app::MouseEvent iEvent);
	
	/** @brief Overloadable mouse down event callback method */
	virtual bool			mouseDown(ci::app::MouseEvent iEvent);
	
	/** @brief Overloadable mouse drag event callback method */
	virtual bool			mouseDrag(ci::app::MouseEvent iEvent);
	
	/** @brief Overloadable mouse up event callback method */
	virtual bool			mouseUp(ci::app::MouseEvent iEvent);
	
	/** @brief Removes all data inputs from the plotter */
	void					clearInputs();
	
	/** @brief Adds a ci::PolyLine2f data input to the plotter */
	void					addInput(const ci::PolyLine2f& iInput, const ci::ColorA& iColor);
	
	/** @brief Adds a PlotterDataRef data input to the plotter */
	void					addInput(PlotterDataRef iDataRef);
	
	/** @brief Removes the given PlotterDataRef data input from the plotter */
	void					removeInput(PlotterDataRef iDataRef);
	
	/** @brief Sets the display range for the graph's x-axis */
	void					setXRange(const float& iMin, const float &iMax);
	
	/** @brief Sets the display range for the graph's y-axis */
	void					setYRange(const float& iMin, const float &iMax);
	
	/** @brief Sets the origin line color */
	void					setOriginColor(const ci::ColorA& iColor);
	
	/** @brief Returns the origin line color */
	const ci::ColorA&		getOriginColor() const;
	
	/** @brief Sets the origin line width */
	void					setOriginWeight(const float& iWeight);
	
	/** @brief Returns the origin line width */
	const float&			getOriginWeight() const;
	
	/** @brief Sets the grid line color */
	void					setGridColor(const ci::ColorA& iColor);
	
	/** @brief Returns the grid line color */
	const ci::ColorA&		getGridColor() const;
	
	/** @brief Sets the grid line width */
	void					setGridWeight(const float& iWeight);
	
	/** @brief Returns the grid line width */
	const float&			getGridWeight() const;
	
protected:
	
	/** @brief An overloadable method that is evoked when the widget requires updating */
	virtual void			recomputeFormatting();
	
	/** @brief A protected method that is evoked automatically when the widget requires updating */
	void					deepRecomputeFormatting();
	
	/** @brief Returns a formatted string representing the input 2D coordinate */
	std::string				getVertexLabelString(const float& iX, const float& iY);

	/** @brief Returns true if given screen coordinate is within rect and if so, outputs adjusted graph and widget-relative coordinates as parameters */
	bool					screenToGraphCoord(const ci::Vec2f& iScreenCoord, ci::Vec2f& oGraphCoord, ci::Vec2f& oWidgetRelativeCoord);
	
	/** @brief Returns the input value rounded to the nearest interval */
	float					roundToNearest(const float& iValue, const float& iInterval);
};