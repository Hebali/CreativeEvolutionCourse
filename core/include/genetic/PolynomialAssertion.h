//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include "PolynomialData.h"

/** @brief An enumeration of the available assertion types */
enum AssertType
{
	IS_EQUAL,	//!< Assert: A == B
	IS_NEQUAL,	//!< Assert: A != B
	IS_GREATER,	//!< Assert: A >  B
	IS_LESS,	//!< Assert: A <  B
	IS_GEQUAL,	//!< Assert: A >= B
	IS_LEQUAL	//!< Assert: A <= B
};

/** @brief An array of the symbol string representations of the available assertion types */
static const std::string AssertTypeSymbols[] =
{
	"==",
	"!=",
	">",
	"<",
	">=",
	"<="
};

/** @brief An enumeration of the available assertion modes */
enum AssertMode
{
	FOR_FUNCTION,	//!< Assert Mode: Function
	FOR_DERIVATIVE 	//!< Assert Mode: Derivative
};

/** @brief An array of the symbol string representations of the available assertion modes */
static const std::string AssertModeSymbols[] =
{
	"f",
	"df"
};

typedef std::shared_ptr<class Assertion>	AssertionRef;			//!< A shared pointer to an Assertion
typedef std::vector<AssertionRef>			AssertionRefVec;		//!< A vector of AssertionRef items
typedef AssertionRefVec::iterator			AssertionRefVecIter;	//!< An iterator type for a vector of AssertionRef items
typedef AssertionRefVec::reverse_iterator	AssertionRefVecRiter;	//!< A reverse iterator type for a vector of AssertionRef items
typedef AssertionRefVec::const_iterator		AssertionRefVecCiter;	//!< A const iterator type for a vector of AssertionRef items

/** 
 * @brief A compact description of a comparative assertion template 
 */
class Assertion {
protected:
	
	float				mRangeIn;		//!< The beginning of the param range
	float				mRangeOut;		//!< The end of the param range
	float				mScoreWeight;	//!< The score multiplier value
	AssertType			mType;			//!< The assertion type
	AssertMode			mModeLhs;		//!< The left-hand assertion mode
	AssertMode			mModeRhs;		//!< The right-hand assertion mode
	PolynomialDataRef	mDataRhs;		//!< A reference to the right-hand data
		
public:
	
	/** @brief Default constructor */
	Assertion();
	
	/** @brief Applies the assertion to the given left-hand data */
	float				applyTo(PolynomialDataRef iLhsRef) const;
	
	/** @brief Returns a formatted string representing the assertion */
	std::string			getAssertionString(PolynomialDataRef iLhsRef) const;
	
	/** @brief Sets the right-hand data reference */
	void				setDataRhs(PolynomialDataRef iDataRhs);
	
	/** @brief Returns the right-hand data reference */
	PolynomialDataRef	getDataRhs() const;
	
	/** @brief Sets the assertion's parameter range */
	void				setParameterRange(const float& iParamIn, const float& iParamOut);
	
	/** @brief Returns the assertion's lower-bounds parameter */
	const float&		getParameterRangeIn() const;
	
	/** @brief Returns the assertion's upper-bounds parameter */
	const float&		getParameterRangeOut() const;
	
	/** @brief Sets the score weighting multiplier */
	void				setScoreWeight(const float& iWeight);
	
	/** @brief Returns the score weighting multiplier */
	const float&		getScoreWeight() const;
	
	/** @brief Sets the assertion type */
	void				setType(const AssertType& iType);
	
	/** @brief Returns the assertion type */
	const AssertType&	getType() const;
	
	/** @brief Sets the left-hand assertion mode */
	void				setMode(const AssertMode& iModeLhs, const AssertMode& iModeRhs);
	
	/** @brief Sets the left-hand assertion mode */
	void				setModeLhs(const AssertMode& iModeLhs);
	
	/** @brief Returns the left-hand assertion mode */
	const AssertMode&	getModeLhs() const;
	
	/** @brief Sets the right-hand assertion mode */
	void				setModeRhs(const AssertMode& iModeRhs);
	
	/** @brief Returns the right-hand assertion mode */
	const AssertMode&	getModeRhs() const;
};

/**
 * @brief A wrapper class for a group of Assertion items
 */
class AssertionGroup {
protected:
	
	AssertionRefVec mAssertions;	//!< The assertion vector
	
public:
	
	/** @brief Default constructor */
	AssertionGroup();
	
	/** @brief Returns true if there are no assertions in the group */
	bool				empty() const;
	
	/** @brief Returns the number of assertions in the group */
	size_t				size() const;
	
	/** @brief Removes all assertions from the group */
	void				clear();
	
	/** @brief Adds an assertion to the group */
	void				add(AssertionRef iAssertion);
	
	/** @brief Applies the assertion group to the given left-hand data */
	float				applyTo(PolynomialDataRef iLhsRef) const;
	
	/** @brief Returns a formatted string representing the assertion group */
	std::string			getAssertionString(PolynomialDataRef iLhsRef) const;
};

