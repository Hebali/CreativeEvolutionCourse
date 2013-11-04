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
enum GuiFlow
{
	UI_FIXED, UI_RELATIVE
};

/**
 * @brief A basic two-dimensional scenegraph node
 */
class GuiBase {
public:
	
	typedef std::deque<GuiBase*>			GuiBaseDeque;		//!< A deque of GuiBase* nodes
	typedef GuiBaseDeque::iterator			GuiBaseDequeIter;	//!< An iterator type for a deque of GuiBase* nodes
	typedef GuiBaseDeque::reverse_iterator	GuiBaseDequeRiter;	//!< A reverse iterator type for a deque of GuiBase* nodes
	typedef GuiBaseDeque::const_iterator	GuiBaseDequeCiter;	//!< A const iterator type for a deque of GuiBase* nodes
	
protected:
	
	std::string				mName;		//!< The node's name
	bool					mVisible;	//!< Flags whether the node is visible
	
	ci::Vec2f				mPosition;	//!< The node's position (either absolute or relative)
	ci::Vec2f				mDimension;	//!< The node's dimension (either absolute or relative)
	GuiFlow					mFlowX;		//!< The node's flow type for its x-position parameter
	GuiFlow					mFlowY;		//!< The node's flow type for its y-position parameter
	GuiFlow					mFlowW;		//!< The node's flow type for its width parameter
	GuiFlow					mFlowH;		//!< The node's flow type for its height parameter
	
	GuiBase*				mParent;	//!< A pointer to the node's parent
	GuiBaseDeque			mChildren;	//!< A deque of the node's children
	
public:
	
	/** @brief Basic constructor */
	GuiBase();
	
	/** @brief Virtual destructor */
	virtual ~GuiBase();
	
	/** @brief Sets the node's name label */
	void					setName(const std::string& iName);

	/** @brief Returns the node's name label */
	const std::string&		getName();
	
	/** @brief Sets the node's visibility status */
	void					setVisibility(const bool& iVisible);
	
	/** @brief Returns the node's visibility status */
	bool					getVisibility() const;
	
	/** @brief The node's deep draw handler */
	void					deepDraw();
	
	/** @brief An overloadable draw method */
	virtual void			draw();
	
	/** @brief The node's deep event-handler for mouseMove events */
	bool					deepMouseMove(ci::app::MouseEvent iEvent);
	
	/** @brief The node's deep event-handler for mouseDown events */
	bool					deepMouseDown(ci::app::MouseEvent iEvent);
	
	/** @brief The node's deep event-handler for mouseDrag events */
	bool					deepMouseDrag(ci::app::MouseEvent iEvent);
	
	/** @brief The node's deep event-handler for mouseUp events */
	bool					deepMouseUp(ci::app::MouseEvent iEvent);
	
	/** @brief An overloadable event-handler for mouseMove events */
	virtual bool			mouseMove(ci::app::MouseEvent iEvent);
	
	/** @brief An overloadable event-handler for mouseDown events */
	virtual bool			mouseDown(ci::app::MouseEvent iEvent);
	
	/** @brief An overloadable event-handler for mouseDrag events */
	virtual bool			mouseDrag(ci::app::MouseEvent iEvent);
	
	/** @brief An overloadable event-handler for mouseUp events */
	virtual bool			mouseUp(ci::app::MouseEvent iEvent);
	
	/** @brief The node's deep event-handler for keyDown events */
	bool					deepKeyDown(ci::app::KeyEvent iEvent);
	
	/** @brief The node's deep event-handler for keyUp events */
	bool					deepKeyUp(ci::app::KeyEvent iEvent);
	
	/** @brief An overloadable event-handler for keyDown events */
	virtual bool			keyDown(ci::app::KeyEvent iEvent);
	
	/** @brief An overloadable event-handler for keyUp events */
	virtual bool			keyUp(ci::app::KeyEvent iEvent);
	
	/** @brief Returns true if the node has a parent node */
	bool					hasParent() const;
	
	/** @brief Returns the node's parent if one exists, otherwise NULL */
	GuiBase*					getParent() const;
	
	/** @brief Sets the node's parent */
	void					setParent(GuiBase* iParent);
	
	/** @brief Returns true if the node has children nodes */
	bool					hasChildren() const;
	
	/** @brief Returns a reference to the child node deque */
	GuiBaseDeque&			getChildren();
	
	/** @brief Returns a const reference to the child node deque */
	const GuiBaseDeque&		getChildren() const;
	
	/** @brief Adds the given node as a child of this node */
	void					addChild(GuiBase* iChild);
	
	/** @brief Sets the node's fixed position */
	void					setPosition(const ci::Vec2f& iPosition);
	
	/** @brief Sets the node's fixed position */
	void					setPosition(const float& iPositionX, const float& iPositionY);
	
	/** @brief Sets the node's fixed x-position */
	void					setPositionX(const float& iPositionX);
	
	/** @brief Sets the node's fixed y-position */
	void					setPositionY(const float& iPositionY);
	
	/** @brief Sets the node's relative position */
	void					setRelativePosition(const ci::Vec2f& iPosition);
	
	/** @brief Sets the node's relative position */
	void					setRelativePosition(const float& iPositionX, const float& iPositionY);
	
	/** @brief Sets the node's relative x-position */
	void					setRelativePositionX(const float& iPositionX);
	
	/** @brief Sets the node's relative y-position */
	void					setRelativePositionY(const float& iPositionY);
	
	/** @brief Returns the node's screen position */
	ci::Vec2f				getPosition() const;
	
	/** @brief Returns the node's local position within its parent */
	ci::Vec2f				getLocalPosition() const;
	
	/** @brief Sets the node's fixed dimension */
	void					setDimension(const ci::Vec2f& iDimension);
	
	/** @brief Sets the node's fixed dimension */
	void					setDimension(const float& iDimensionX, const float& iDimensionY);
	
	/** @brief Sets the node's fixed x-dimension */
	void					setDimensionX(const float& iDimensionX);
	
	/** @brief Sets the node's fixed y-dimension */
	void					setDimensionY(const float& iDimensionY);
	
	/** @brief Sets the node's relative dimension */
	void					setRelativeDimension(const ci::Vec2f& iDimension);
	
	/** @brief Sets the node's relative dimension */
	void					setRelativeDimension(const float& iDimensionX, const float& iDimensionY);
	
	/** @brief Sets the node's relative x-dimension */
	void					setRelativeDimensionX(const float& iDimensionX);
	
	/** @brief Sets the node's relative y-dimension */
	void					setRelativeDimensionY(const float& iDimensionY);
	
	/** @brief Returns the node's screen dimension */
	ci::Vec2f				getDimension() const;
	
	/** @brief Returns the node's screen x-dimension */
	float					getDimensionX() const;
	
	/** @brief Returns the node's screen y-dimension */
	float					getDimensionY() const;
};