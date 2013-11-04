//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include "GuiBase.h"

/**
 * @brief A scenegraph node representing a rectangle
 */
class GuiRect : public GuiBase {
protected:
	
	ci::ColorA				mFillColor;		//!< The rect's background color
	ci::ColorA				mStrokeColor;	//!< The rect's border color
	float					mStrokeWeight;	//!< The rect's border width
	
public:
	
	/** @brief Default constructor */
	GuiRect();
	
	/** @brief Virtual destructor */
	virtual ~GuiRect();
	
	/** @brief An overloadable draw method */
	virtual void			draw();
	
	/** @brief Sets the rect's background color */
	void					setFillColor(const ci::ColorA& iColor);
	
	/** @brief Returns the rect's background color */
	const ci::ColorA&		getFillColor() const;
	
	/** @brief Sets the rect's border color */
	void					setStrokeColor(const ci::ColorA& iColor);
	
	/** @brief Returns the rect's border color */
	const ci::ColorA&		getStrokeColor() const;
	
	/** @brief Sets the rect's border width */
	void					setStrokeWeight(const float& iWeight);
	
	/** @brief Returns the rect's border width */
	const float&			getStrokeWeight() const;
};