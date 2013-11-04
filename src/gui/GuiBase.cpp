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

UiBase::UiBase() :
	mPosition( Vec2f::zero() ),
	mDimension( Vec2f::zero() ),
	mFlowX( UiFlow::UI_FIXED ),
	mFlowY( UiFlow::UI_FIXED ),
	mFlowW( UiFlow::UI_FIXED ),
	mFlowH( UiFlow::UI_FIXED ),
	mVisible( true ),
	mParent( NULL )
{
}

UiBase::~UiBase()
{
	// Remove parent ref:
	mParent = NULL;
	// Delete children:
	for(UiBaseDequeCiter it = mChildren.begin(); it != mChildren.end(); it++) {
		delete (*it);
	}
	mChildren.clear();
}

void UiBase::setName(const string& iName)
{
	mName = iName;
}

const string& UiBase::getName()
{
	return mName;
}

void UiBase::setVisibility(const bool& iVisible)
{
	mVisible = iVisible;
}

bool UiBase::getVisibility() const
{
	if( !mVisible ) { return false; }
	else if( mParent ) { return mParent->getVisibility(); }
	return true;
}

void UiBase::deepDraw()
{
	if( getVisibility() ) {
		// Handle self:
		draw();
		// Handle children:
		for(UiBaseDequeCiter it = mChildren.begin(); it != mChildren.end(); it++) {
			(*it)->deepDraw();
		}
	}
}

void UiBase::draw()
{
	// Override this method
}

bool UiBase::deepMouseMove(ci::app::MouseEvent iEvent)
{
	bool tHandled = false;
	if( getVisibility() ) {
		// Handle children:
		for(UiBaseDequeRiter it = mChildren.rbegin(); it != mChildren.rend(); it++) {
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

bool UiBase::deepMouseDown(ci::app::MouseEvent iEvent)
{
	bool tHandled = false;
	if( getVisibility() ) {
		// Handle children:
		for(UiBaseDequeRiter it = mChildren.rbegin(); it != mChildren.rend(); it++) {
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

bool UiBase::deepMouseDrag(ci::app::MouseEvent iEvent)
{
	bool tHandled = false;
	if( getVisibility() ) {
		// Handle children:
		for(UiBaseDequeRiter it = mChildren.rbegin(); it != mChildren.rend(); it++) {
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

bool UiBase::deepMouseUp(ci::app::MouseEvent iEvent)
{
	bool tHandled = false;
	if( getVisibility() ) {
		// Handle children:
		for(UiBaseDequeRiter it = mChildren.rbegin(); it != mChildren.rend(); it++) {
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

bool UiBase::mouseMove(app::MouseEvent iEvent)
{
	return false;
}

bool UiBase::mouseDown(app::MouseEvent iEvent)
{
	return false;
}

bool UiBase::mouseDrag(app::MouseEvent iEvent)
{
	return false;
}

bool UiBase::mouseUp(app::MouseEvent iEvent)
{
	return false;
}

bool UiBase::deepKeyDown(ci::app::KeyEvent iEvent)
{
	bool tHandled = false;
	if( getVisibility() ) {
		// Handle children:
		for(UiBaseDequeRiter it = mChildren.rbegin(); it != mChildren.rend(); it++) {
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

bool UiBase::deepKeyUp(ci::app::KeyEvent iEvent)
{
	bool tHandled = false;
	if( getVisibility() ) {
		// Handle children:
		for(UiBaseDequeRiter it = mChildren.rbegin(); it != mChildren.rend(); it++) {
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

bool UiBase::keyDown(ci::app::KeyEvent iEvent)
{
	return false;
}

bool UiBase::keyUp(ci::app::KeyEvent iEvent)
{
	return false;
}

bool UiBase::hasParent() const
{
	return ( mParent != NULL );
}

UiBase* UiBase::getParent() const
{
	return mParent;
}

void UiBase::setParent(UiBase* iParent)
{
	mParent = iParent;
}

bool UiBase::hasChildren() const
{
	return !mChildren.empty();
}

UiBase::UiBaseDeque& UiBase::getChildren()
{
	return mChildren;
}

const UiBase::UiBaseDeque& UiBase::getChildren() const
{
	return mChildren;
}

void UiBase::addChild(UiBase* iChild)
{
	iChild->setParent( this );
	mChildren.push_back( iChild );
}

void UiBase::setPosition(const Vec2f& iPosition)
{
	mPosition = iPosition;
	mFlowX = UiFlow::UI_FIXED;
	mFlowY = UiFlow::UI_FIXED;
}

void UiBase::setPosition(const float& iPositionX, const float& iPositionY)
{
	mPosition = Vec2f( iPositionX, iPositionY );
	mFlowX = UiFlow::UI_FIXED;
	mFlowY = UiFlow::UI_FIXED;
}

void UiBase::setPositionX(const float& iPositionX)
{
	mPosition.x = iPositionX;
	mFlowX = UiFlow::UI_FIXED;
}

void UiBase::setPositionY(const float& iPositionY)
{
	mPosition.y = iPositionY;
	mFlowY = UiFlow::UI_FIXED;
}

void UiBase::setRelativePosition(const ci::Vec2f& iPosition)
{
	mPosition = iPosition;
	mFlowX = UiFlow::UI_RELATIVE;
	mFlowY = UiFlow::UI_RELATIVE;
}

void UiBase::setRelativePosition(const float& iPositionX, const float& iPositionY)
{
	mPosition  = Vec2f( iPositionX, iPositionY );
	mFlowX = UiFlow::UI_RELATIVE;
	mFlowY = UiFlow::UI_RELATIVE;
}

void UiBase::setRelativePositionX(const float& iPositionX)
{
	mPosition.x = iPositionX;
	mFlowX = UiFlow::UI_RELATIVE;
}

void UiBase::setRelativePositionY(const float& iPositionY)
{
	mPosition.y = iPositionY;
	mFlowY = UiFlow::UI_RELATIVE;
}

Vec2f UiBase::getPosition() const
{
	return getLocalPosition() + ( mParent ? mParent->getPosition() : Vec2f::zero() );
}

Vec2f UiBase::getLocalPosition() const
{
	Vec2f tOut = mPosition;
	if( mFlowX == UiFlow::UI_RELATIVE ) {
		float tPar  = ( mParent ? mParent->getDimensionX() : app::getWindowWidth() );
		float tDim  = ( ( mFlowW == UiFlow::UI_RELATIVE ) ? ( mDimension.x * tPar ) : ( mDimension.x ) );
		tOut.x = mPosition.x * ( tPar - tDim );
	}
	if( mFlowY == UiFlow::UI_RELATIVE ) {
		float tPar  = ( mParent ? mParent->getDimensionY() : app::getWindowHeight() );
		float tDim  = ( ( mFlowH == UiFlow::UI_RELATIVE ) ? ( mDimension.y * tPar ) : ( mDimension.y ) );
		tOut.y = mPosition.y * ( tPar - tDim );
	}
	return tOut;
}

void UiBase::setDimension(const Vec2f& iDimension)
{
	mDimension = iDimension;
	mFlowW = UiFlow::UI_FIXED;
	mFlowH = UiFlow::UI_FIXED;
}

void UiBase::setDimension(const float& iDimensionX, const float& iDimensionY)
{
	mDimension = Vec2f( iDimensionX, iDimensionY );
	mFlowW = UiFlow::UI_FIXED;
	mFlowH = UiFlow::UI_FIXED;
}

void UiBase::setDimensionX(const float& iDimensionX)
{
	mDimension.x = iDimensionX;
	mFlowW = UiFlow::UI_FIXED;
}

void UiBase::setDimensionY(const float& iDimensionY)
{
	mDimension.y = iDimensionY;
	mFlowH = UiFlow::UI_FIXED;
}

void UiBase::setRelativeDimension(const ci::Vec2f& iDimension)
{
	mDimension = iDimension;
	mFlowW = UiFlow::UI_RELATIVE;
	mFlowH = UiFlow::UI_RELATIVE;
}

void UiBase::setRelativeDimension(const float& iDimensionX, const float& iDimensionY)
{
	mDimension = Vec2f( iDimensionX, iDimensionY );
	mFlowW = UiFlow::UI_RELATIVE;
	mFlowH = UiFlow::UI_RELATIVE;
}

void UiBase::setRelativeDimensionX(const float& iDimensionX)
{
	mDimension.x = iDimensionX;
	mFlowW = UiFlow::UI_RELATIVE;
}

void UiBase::setRelativeDimensionY(const float& iDimensionY)
{
	mDimension.y = iDimensionY;
	mFlowH = UiFlow::UI_RELATIVE;
}

Vec2f UiBase::getDimension() const
{
	return Vec2f( getDimensionX(), getDimensionY() );
}

float UiBase::getDimensionX() const
{
	return ( ( mFlowW == UiFlow::UI_RELATIVE ) ? ( mDimension.x * ( mParent ? mParent->getDimensionX() : app::getWindowWidth() ) ) : ( mDimension.x ) );
}

float UiBase::getDimensionY() const
{
	return ( ( mFlowH == UiFlow::UI_RELATIVE ) ? ( mDimension.y * ( mParent ? mParent->getDimensionY() : app::getWindowHeight() ) ) : ( mDimension.y ) );
}