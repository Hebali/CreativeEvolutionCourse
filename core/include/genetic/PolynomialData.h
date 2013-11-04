//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include "GuiPlot.h"

typedef std::shared_ptr<class PolynomialData>	PolynomialDataRef;			//!< A shared pointer to a PlotterData item
typedef std::vector<PolynomialDataRef>			PolynomialDataRefVec;		//!< A vector of PlotterDataRef items
typedef PolynomialDataRefVec::iterator			PolynomialDataRefVecIter;	//!< An iterator type for a vector of PlotterDataRef items
typedef PolynomialDataRefVec::reverse_iterator	PolynomialDataRefVecRiter;	//!< A reverse iterator type for a vector of PlotterDataRef items
typedef PolynomialDataRefVec::const_iterator	PolynomialDataRefVecCiter;	//!< A const iterator type for a vector of PlotterDataRef items

/** 
 * @brief A class representing a polynomial function 
 */
class PolynomialData :public PlotterData {
public:
	
	typedef std::pair<float,float>			ComponentPair;		//!< A <Coefficient,Exponent> pair
	typedef std::vector<ComponentPair>		ComponentVec;		//!< A vector of <Coefficient,Exponent> pairs
	typedef ComponentVec::iterator			ComponentVecIter;	//!< An iterator type for a vector of <Coefficient,Exponent> pairs
	typedef ComponentVec::reverse_iterator	ComponentVecRiter;	//!< A reverse iterator type for a vector of <Coefficient,Exponent> pairs
	typedef ComponentVec::const_iterator	ComponentVecCiter;	//!< A const iterator type for a vector of <Coefficient,Exponent> pairs
	
protected:
	
	ComponentVec	mComponents;	//!< The formula's components
	
	size_t			mDrawSamples;	//!< The number of samples to be plotted
	float			mDrawRangeIn;	//!< The beginning of the param range
	float			mDrawRangeOut;	//!< The end of the param range
	bool			mDrawFormula;	//!< Flags whether formula data should be drawn
	bool			mDrawDeriv;		//!< Flags whether derivative data should be drawn
	bool			mDirty;			//!< Flags whether raster data needs updating
	
public:
	
	/** @brief Basic Constructor */
	PolynomialData(const float& iParamIn = 0.0, const float &iParamOut = 1.0,
				   const bool& iDrawFormula = true, const bool& iDrawDeriv = true,
				   const ci::ColorA& iColor = ci::ColorA::white(), const float& iStrokeWeight = 3.0);
	
	/** @brief Virtual destructor */
	virtual ~PolynomialData();
	
	/** @brief Returns a clone of this item */
	virtual PlotterData*	clone();
	
	/** @brief An overloadable draw method */
	virtual void			draw();
	
	/** @brief Sets the parameter range for the drawing of the polynomial formula */
	void					setDrawParameters(const float& iParamIn, const float& iParamOut,
											  const bool& iDrawFormula = true, const bool& iDrawDeriv = true,
											  const ci::ColorA& iColor = ci::ColorA::white(), const float& iStrokeWeight = 3.0);
	
	/** @brief Adds a component with the given coefficient and exponent values to the formula */
	void					addComponent(const float& iCoeff, const float& iExpon);
	
	/** @brief Returns a reference to the components vector */
	ComponentVec&			getComponents();
	
	/** @brief Returns a const reference to the components vector */
	const ComponentVec&		getComponents() const;
	
	/** @brief Computes the output value for a given input */
	float					getValue(const float& iParam) const;
	
	/** @brief Computes the derivative of the output value for a given input */
	float					getDerivativeValue(const float& iParam) const;
	
	/** @brief Returns a textual representation of the formula */
	std::string				getFormulaString() const;
	
	/** @brief Returns a textual representation of the derivative formula */
	std::string				getDerivativeFormulaString() const;
};