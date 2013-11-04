//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"

/**
 * @brief An enumeration of the available UI widget positioning types
 * Fixed: Element's value is treated as a fixed offset from the parent element's value
 * Relative: Element's value in range 0 to 1 is interpolated within the parent element's span
 */
enum UiFlow
{
	UI_FIXED, UI_RELATIVE
};

/**
 * @brief A basic two-dimensional scenegraph node
 */
class UiBase {
public:
	
	typedef std::deque<UiBase*>				UiBaseDeque;
	typedef UiBaseDeque::iterator			UiBaseDequeIter;
	typedef UiBaseDeque::reverse_iterator	UiBaseDequeRiter;
	typedef UiBaseDeque::const_iterator		UiBaseDequeCiter;
	
protected:
	
	bool					mVisible;
	ci::Vec2f				mPosition;
	ci::Vec2f				mDimension;
	UiFlow					mFlowX;
	UiFlow					mFlowY;
	UiFlow					mFlowW;
	UiFlow					mFlowH;
	
	std::string				mName;
	
	UiBase*					mParent;
	UiBaseDeque				mChildren;
	
public:
	
	UiBase();
	virtual ~UiBase();
	
	void					setName(const std::string& iName);
	const std::string&		getName();
	
	void					setVisibility(const bool& iVisible);
	bool					getVisibility() const;
	
	void					deepDraw();
	virtual void			draw();
	
	bool					deepMouseMove(ci::app::MouseEvent iEvent);
	bool					deepMouseDown(ci::app::MouseEvent iEvent);
	bool					deepMouseDrag(ci::app::MouseEvent iEvent);
	bool					deepMouseUp(ci::app::MouseEvent iEvent);
	
	virtual bool			mouseMove(ci::app::MouseEvent iEvent);
	virtual bool			mouseDown(ci::app::MouseEvent iEvent);
	virtual bool			mouseDrag(ci::app::MouseEvent iEvent);
	virtual bool			mouseUp(ci::app::MouseEvent iEvent);
	
	bool					deepKeyDown(ci::app::KeyEvent iEvent);
	bool					deepKeyUp(ci::app::KeyEvent iEvent);
	
	virtual bool			keyDown(ci::app::KeyEvent iEvent);
	virtual bool			keyUp(ci::app::KeyEvent iEvent);
	
	bool					hasParent() const;
	UiBase*					getParent() const;
	void					setParent(UiBase* iParent);
	
	bool					hasChildren() const;
	UiBaseDeque&			getChildren();
	const UiBaseDeque&		getChildren() const;
	void					addChild(UiBase* iChild);
	
	void					setPosition(const ci::Vec2f& iPosition);
	void					setPosition(const float& iPositionX, const float& iPositionY);
	void					setPositionX(const float& iPositionX);
	void					setPositionY(const float& iPositionY);
	
	void					setRelativePosition(const ci::Vec2f& iPosition);
	void					setRelativePosition(const float& iPositionX, const float& iPositionY);
	void					setRelativePositionX(const float& iPositionX);
	void					setRelativePositionY(const float& iPositionY);
	
	ci::Vec2f				getPosition() const;
	ci::Vec2f				getLocalPosition() const;
	
	void					setDimension(const ci::Vec2f& iDimension);
	void					setDimension(const float& iDimensionX, const float& iDimensionY);
	void					setDimensionX(const float& iDimensionX);
	void					setDimensionY(const float& iDimensionY);
	
	void					setRelativeDimension(const ci::Vec2f& iDimension);
	void					setRelativeDimension(const float& iDimensionX, const float& iDimensionY);
	void					setRelativeDimensionX(const float& iDimensionX);
	void					setRelativeDimensionY(const float& iDimensionY);
	
	ci::Vec2f				getDimension() const;
	float					getDimensionX() const;
	float					getDimensionY() const;
};