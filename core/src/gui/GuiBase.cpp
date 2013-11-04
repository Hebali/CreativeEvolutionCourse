//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include "GuiBase.h"

using namespace std;
using namespace ci;

GuiBase::GuiBase() :
	mPosition( Vec2f::zero() ),
	mDimension( Vec2f::zero() ),
	mFlowX( GuiFlow::UI_FIXED ),
	mFlowY( GuiFlow::UI_FIXED ),
	mFlowW( GuiFlow::UI_FIXED ),
	mFlowH( GuiFlow::UI_FIXED ),
	mVisible( true ),
	mParent( NULL )
{
}

GuiBase::~GuiBase()
{
	// Remove parent ref:
	mParent = NULL;
	// Delete children:
	for(GuiBaseDequeCiter it = mChildren.begin(); it != mChildren.end(); it++) {
		delete (*it);
	}
	mChildren.clear();
}

void GuiBase::setName(const string& iName)
{
	mName = iName;
}

const string& GuiBase::getName()
{
	return mName;
}

void GuiBase::setVisibility(const bool& iVisible)
{
	mVisible = iVisible;
}

bool GuiBase::getVisibility() const
{
	if( !mVisible ) { return false; }
	else if( mParent ) { return mParent->getVisibility(); }
	return true;
}

void GuiBase::deepDraw()
{
	if( getVisibility() ) {
		// Handle self:
		draw();
		// Handle children:
		for(GuiBaseDequeCiter it = mChildren.begin(); it != mChildren.end(); it++) {
			(*it)->deepDraw();
		}
	}
}

void GuiBase::draw()
{
	// Override this method
}

bool GuiBase::deepMouseMove(ci::app::MouseEvent iEvent)
{
	bool tHandled = false;
	if( getVisibility() ) {
		// Handle children:
		for(GuiBaseDequeRiter it = mChildren.rbegin(); it != mChildren.rend(); it++) {
			if( (*it)->deepMouseMove( iEvent ) ) {
				tHandled = true;
			}
		}
		// Handle self:
		if( !tHandled ) {
			tHandled = mouseMove( iEvent );
		}
	}
	return tHandled;
}

bool GuiBase::deepMouseDown(ci::app::MouseEvent iEvent)
{
	bool tHandled = false;
	if( getVisibility() ) {
		// Handle children:
		for(GuiBaseDequeRiter it = mChildren.rbegin(); it != mChildren.rend(); it++) {
			if( (*it)->deepMouseDown( iEvent ) ) {
				tHandled = true;
			}
		}
		// Handle self:
		if( !tHandled ) {
			tHandled = mouseDown( iEvent );
		}
	}
	return tHandled;
}

bool GuiBase::deepMouseDrag(ci::app::MouseEvent iEvent)
{
	bool tHandled = false;
	if( getVisibility() ) {
		// Handle children:
		for(GuiBaseDequeRiter it = mChildren.rbegin(); it != mChildren.rend(); it++) {
			if( (*it)->deepMouseDrag( iEvent ) ) {
				tHandled = true;
			}
		}
		// Handle self:
		if( !tHandled ) {
			tHandled = mouseDrag( iEvent );
		}
	}
	return tHandled;
}

bool GuiBase::deepMouseUp(ci::app::MouseEvent iEvent)
{
	bool tHandled = false;
	if( getVisibility() ) {
		// Handle children:
		for(GuiBaseDequeRiter it = mChildren.rbegin(); it != mChildren.rend(); it++) {
			if( (*it)->deepMouseUp( iEvent ) ) {
				tHandled = true;
			}
		}
		// Handle self:
		if( !tHandled ) {
			tHandled = mouseUp( iEvent );
		}
	}
	return tHandled;
}

bool GuiBase::mouseMove(app::MouseEvent iEvent)
{
	return false;
}

bool GuiBase::mouseDown(app::MouseEvent iEvent)
{
	return false;
}

bool GuiBase::mouseDrag(app::MouseEvent iEvent)
{
	return false;
}

bool GuiBase::mouseUp(app::MouseEvent iEvent)
{
	return false;
}

bool GuiBase::deepKeyDown(ci::app::KeyEvent iEvent)
{
	bool tHandled = false;
	if( getVisibility() ) {
		// Handle children:
		for(GuiBaseDequeRiter it = mChildren.rbegin(); it != mChildren.rend(); it++) {
			if( (*it)->deepKeyDown( iEvent ) ) {
				tHandled = true;
			}
		}
		// Handle self:
		if( !tHandled ) {
			tHandled = keyDown( iEvent );
		}
	}
	return tHandled;
}

bool GuiBase::deepKeyUp(ci::app::KeyEvent iEvent)
{
	bool tHandled = false;
	if( getVisibility() ) {
		// Handle children:
		for(GuiBaseDequeRiter it = mChildren.rbegin(); it != mChildren.rend(); it++) {
			if( (*it)->deepKeyUp( iEvent ) ) {
				tHandled = true;
			}
		}
		// Handle self:
		if( !tHandled ) {
			tHandled = keyUp( iEvent );
		}
	}
	return tHandled;
}

bool GuiBase::keyDown(ci::app::KeyEvent iEvent)
{
	return false;
}

bool GuiBase::keyUp(ci::app::KeyEvent iEvent)
{
	return false;
}

bool GuiBase::hasParent() const
{
	return ( mParent != NULL );
}

GuiBase* GuiBase::getParent() const
{
	return mParent;
}

void GuiBase::setParent(GuiBase* iParent)
{
	mParent = iParent;
}

bool GuiBase::hasChildren() const
{
	return !mChildren.empty();
}

GuiBase::GuiBaseDeque& GuiBase::getChildren()
{
	return mChildren;
}

const GuiBase::GuiBaseDeque& GuiBase::getChildren() const
{
	return mChildren;
}

void GuiBase::addChild(GuiBase* iChild)
{
	iChild->setParent( this );
	mChildren.push_back( iChild );
}

void GuiBase::setPosition(const Vec2f& iPosition)
{
	mPosition = iPosition;
	mFlowX = GuiFlow::UI_FIXED;
	mFlowY = GuiFlow::UI_FIXED;
}

void GuiBase::setPosition(const float& iPositionX, const float& iPositionY)
{
	mPosition = Vec2f( iPositionX, iPositionY );
	mFlowX = GuiFlow::UI_FIXED;
	mFlowY = GuiFlow::UI_FIXED;
}

void GuiBase::setPositionX(const float& iPositionX)
{
	mPosition.x = iPositionX;
	mFlowX = GuiFlow::UI_FIXED;
}

void GuiBase::setPositionY(const float& iPositionY)
{
	mPosition.y = iPositionY;
	mFlowY = GuiFlow::UI_FIXED;
}

void GuiBase::setRelativePosition(const ci::Vec2f& iPosition)
{
	mPosition = iPosition;
	mFlowX = GuiFlow::UI_RELATIVE;
	mFlowY = GuiFlow::UI_RELATIVE;
}

void GuiBase::setRelativePosition(const float& iPositionX, const float& iPositionY)
{
	mPosition  = Vec2f( iPositionX, iPositionY );
	mFlowX = GuiFlow::UI_RELATIVE;
	mFlowY = GuiFlow::UI_RELATIVE;
}

void GuiBase::setRelativePositionX(const float& iPositionX)
{
	mPosition.x = iPositionX;
	mFlowX = GuiFlow::UI_RELATIVE;
}

void GuiBase::setRelativePositionY(const float& iPositionY)
{
	mPosition.y = iPositionY;
	mFlowY = GuiFlow::UI_RELATIVE;
}

Vec2f GuiBase::getPosition() const
{
	return getLocalPosition() + ( mParent ? mParent->getPosition() : Vec2f::zero() );
}

Vec2f GuiBase::getLocalPosition() const
{
	Vec2f tOut = mPosition;
	if( mFlowX == GuiFlow::UI_RELATIVE ) {
		float tPar  = ( mParent ? mParent->getDimensionX() : app::getWindowWidth() );
		float tDim  = ( ( mFlowW == GuiFlow::UI_RELATIVE ) ? ( mDimension.x * tPar ) : ( mDimension.x ) );
		tOut.x = mPosition.x * ( tPar - tDim );
	}
	if( mFlowY == GuiFlow::UI_RELATIVE ) {
		float tPar  = ( mParent ? mParent->getDimensionY() : app::getWindowHeight() );
		float tDim  = ( ( mFlowH == GuiFlow::UI_RELATIVE ) ? ( mDimension.y * tPar ) : ( mDimension.y ) );
		tOut.y = mPosition.y * ( tPar - tDim );
	}
	return tOut;
}

void GuiBase::setDimension(const Vec2f& iDimension)
{
	mDimension = iDimension;
	mFlowW = GuiFlow::UI_FIXED;
	mFlowH = GuiFlow::UI_FIXED;
}

void GuiBase::setDimension(const float& iDimensionX, const float& iDimensionY)
{
	mDimension = Vec2f( iDimensionX, iDimensionY );
	mFlowW = GuiFlow::UI_FIXED;
	mFlowH = GuiFlow::UI_FIXED;
}

void GuiBase::setDimensionX(const float& iDimensionX)
{
	mDimension.x = iDimensionX;
	mFlowW = GuiFlow::UI_FIXED;
}

void GuiBase::setDimensionY(const float& iDimensionY)
{
	mDimension.y = iDimensionY;
	mFlowH = GuiFlow::UI_FIXED;
}

void GuiBase::setRelativeDimension(const ci::Vec2f& iDimension)
{
	mDimension = iDimension;
	mFlowW = GuiFlow::UI_RELATIVE;
	mFlowH = GuiFlow::UI_RELATIVE;
}

void GuiBase::setRelativeDimension(const float& iDimensionX, const float& iDimensionY)
{
	mDimension = Vec2f( iDimensionX, iDimensionY );
	mFlowW = GuiFlow::UI_RELATIVE;
	mFlowH = GuiFlow::UI_RELATIVE;
}

void GuiBase::setRelativeDimensionX(const float& iDimensionX)
{
	mDimension.x = iDimensionX;
	mFlowW = GuiFlow::UI_RELATIVE;
}

void GuiBase::setRelativeDimensionY(const float& iDimensionY)
{
	mDimension.y = iDimensionY;
	mFlowH = GuiFlow::UI_RELATIVE;
}

Vec2f GuiBase::getDimension() const
{
	return Vec2f( getDimensionX(), getDimensionY() );
}

float GuiBase::getDimensionX() const
{
	return ( ( mFlowW == GuiFlow::UI_RELATIVE ) ? ( mDimension.x * ( mParent ? mParent->getDimensionX() : app::getWindowWidth() ) ) : ( mDimension.x ) );
}

float GuiBase::getDimensionY() const
{
	return ( ( mFlowH == GuiFlow::UI_RELATIVE ) ? ( mDimension.y * ( mParent ? mParent->getDimensionY() : app::getWindowHeight() ) ) : ( mDimension.y ) );
}