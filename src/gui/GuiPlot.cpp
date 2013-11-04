//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include "GuiPlot.h"

using namespace std;
using namespace ci;
using namespace ci::app;

UiPlot::UiPlot(const string& iFontFamilyName, FontSuitcase* iFontSuitcaseRef) :
	UiRect(),
	mFontSuitcaseRef( iFontSuitcaseRef ),
	mOriginColor( ColorA( 1.0, 1.0, 1.0, 0.75 ) ),
	mGridColor( ColorA( 1.0, 1.0, 1.0, 0.5 ) ),
	mDataColor( ColorA( 1.0, 1.0, 1.0, 1.0 ) ),
	mOriginWeight( 2.0 ),
	mGridWeight( 1.0 ),
	mDirty( false ),
	mLabelTL( NULL ),
	mLabelTR( NULL ),
	mLabelBL( NULL ),
	mLabelBR( NULL ),
	mLabelCursor( NULL )
{
	// If font suitcase is attached, create labels:
	if( mFontSuitcaseRef ) {
		mLabelTL = new UiText( "", iFontFamilyName, 14, FontStyle::BOLD, mFontSuitcaseRef );
		mLabelTL->setRelativePosition( Vec2f( 0.01, 0.01 ) );
		mLabelTL->setHighlightColor( ColorA( 0.0, 0.0, 0.0, 0.5 ) );
		addChild( mLabelTL );
		
		mLabelTR = new UiText( "", iFontFamilyName, 14, FontStyle::BOLD, mFontSuitcaseRef );
		mLabelTR->setRelativePosition( Vec2f( 0.99, 0.01 ) );
		mLabelTR->setHighlightColor( ColorA( 0.0, 0.0, 0.0, 0.5 ) );
		addChild( mLabelTR );
		
		mLabelBL = new UiText( "", iFontFamilyName, 14, FontStyle::BOLD, mFontSuitcaseRef );
		mLabelBL->setRelativePosition( Vec2f( 0.01, 0.99 ) );
		mLabelBL->setHighlightColor( ColorA( 0.0, 0.0, 0.0, 0.5 ) );
		addChild( mLabelBL );
		
		mLabelBR = new UiText( "", iFontFamilyName, 14, FontStyle::BOLD, mFontSuitcaseRef );
		mLabelBR->setRelativePosition( Vec2f( 0.99, 0.99 ) );
		mLabelBR->setHighlightColor( ColorA( 0.0, 0.0, 0.0, 0.5 ) );
		addChild( mLabelBR );
		
		mLabelCursor = new UiText( "", iFontFamilyName, 20, FontStyle::BOLD, mFontSuitcaseRef );
		mLabelCursor->setHighlightColor( ColorA( 0.0, 0.0, 0.0, 0.5 ) );
		addChild( mLabelCursor );
	}
}

UiPlot::~UiPlot()
{
}

void UiPlot::draw()
{
	// Update, if dirty:
	deepRecomputeFormatting();
	// Get window size:
	Vec2f tWindowDim = getWindowSize();
	// Compute draw rect:
	Vec2f tPos  = getPosition();
	Vec2f tDim  = getDimension();
	Rectf tRect = Rectf( tPos, tPos + tDim );
	// Compute range scale:
	Vec2f tRangeSize = mRange.getSize();
	// Enter line smoothing:
	glEnable( GL_LINE_SMOOTH );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	// Draw background:
	gl::color( mFillColor );
	gl::drawSolidRect( tRect );
	// Draw border:
	gl::color( mStrokeColor );
	gl::lineWidth( toPixels( mStrokeWeight ) );
	gl::drawStrokedRect( tRect );
	// Enter scissor region:
	glEnable( GL_SCISSOR_TEST );
	glScissor( toPixels( tPos.x ), toPixels( tWindowDim.y - tDim.y - tPos.y ), toPixels( tDim.x ), toPixels( tDim.y ) );
	// Push graph matrix:
	gl::pushMatrices();
	// Translate matrix to rect origin:
	gl::translate( tPos );
	// Scale to match range:
	gl::scale( tDim / tRangeSize );
	// Translate range:
	gl::translate( Vec2f( -mRange.x1, tRangeSize.y ) );
	// Flip graph (so that top of rect is +Y in graph space):
	gl::scale( 1.0, -1.0 );
	gl::translate( 0.0, -mRange.y1 );
	// Draw origin:
	gl::color( mOriginColor );
	gl::lineWidth( toPixels( mOriginWeight ) );
	gl::drawLine( Vec2f( mRange.x1, 0.0 ), Vec2f( mRange.x2, 0.0 ) );
	gl::drawLine( Vec2f( 0.0, mRange.y1 ), Vec2f( 0.0, mRange.y2 ) );
	// Compute appropriate grid increments based on range scale:
	float tIncrX = min( max( pow( 10.0f, floor( log( tRangeSize.x ) ) - 2.0f ), 0.1f ), 10.0f );
	float tIncrY = min( max( pow( 10.0f, floor( log( tRangeSize.y ) ) - 2.0f ), 0.1f ), 10.0f );
	// Draw grid:
	gl::color( mGridColor );
	gl::lineWidth( toPixels( mGridWeight ) );
	float tXs = roundToNearest( mRange.x1, tIncrX );
	float tXe = mRange.x2 + tIncrX;
	while( tXs <= tXe ) {
		gl::drawLine( Vec2f( tXs, mRange.y1 ), Vec2f( tXs, mRange.y2 ) );
		tXs += tIncrX;
	}
	float tYs = roundToNearest( mRange.y1, tIncrY );
	float tYe = mRange.y2 + tIncrY;
	while( tYs <= tYe ) {
		gl::drawLine( Vec2f( mRange.x1, tYs ), Vec2f( mRange.x2, tYs ) );
		tYs += tIncrY;
	}
	// Draw data:
	for(PlotterDataRefVecIter it = mInputs.begin(); it != mInputs.end(); it++) {
		(*it)->draw();
	}
	// Pop graph matrix:
	gl::popMatrices();
	// Exit scissor region:
	glDisable( GL_SCISSOR_TEST );
	// Exit line smoothing:
	glDisable( GL_LINE_SMOOTH );
}

bool UiPlot::mouseMove(app::MouseEvent iEvent)
{
	Vec2f tGraphCoord;
	Vec2f tWidgetRelativeCoord;
	if( screenToGraphCoord( iEvent.getPos(), tGraphCoord, tWidgetRelativeCoord ) ) {
		if( mLabelCursor ) {
			mLabelCursor->setText( getVertexLabelString( tGraphCoord.x, tGraphCoord.y ) );
			mLabelCursor->setRelativePosition( tWidgetRelativeCoord );
			mLabelCursor->setVisibility( true );
		}
	}
	else if( mLabelCursor ) {
		mLabelCursor->setVisibility( false );
	}
	return false;
}

bool UiPlot::mouseDown(app::MouseEvent iEvent)
{
	return false;
}

bool UiPlot::mouseDrag(app::MouseEvent iEvent)
{
	return false;
}

bool UiPlot::mouseUp(app::MouseEvent iEvent)
{
	return false;
}

void UiPlot::clearInputs()
{
	mInputs.clear();
}

void UiPlot::addInput(const ci::PolyLine2f& iLine, const ci::ColorA& iColor)
{
	mInputs.push_back( PlotterDataRef( new PolyLineData( iLine, iColor ) ) );
}

void UiPlot::addInput(PlotterDataRef iDataRef)
{
	mInputs.push_back( iDataRef );
}

void UiPlot::removeInput(PlotterDataRef iDataRef)
{
	for(PlotterDataRefVecCiter it = mInputs.begin(); it != mInputs.end(); it++) {
		if( (*it).get() == iDataRef.get() ) {
			mInputs.erase( it );
			return;
		}
	}
}

void UiPlot::setXRange(const float& iMin, const float &iMax)
{
	mRange.x1 = iMin;
	mRange.x2 = iMax;
	mDirty = true;
}

void UiPlot::setYRange(const float& iMin, const float &iMax)
{
	mRange.y1 = iMin;
	mRange.y2 = iMax;
	mDirty = true;
}

void UiPlot::setOriginColor(const ci::ColorA& iColor)
{
	mOriginColor = iColor;
}

const ci::ColorA& UiPlot::getOriginColor() const
{
	return mOriginColor;
}

void UiPlot::setOriginWeight(const float& iWeight)
{
	mOriginWeight = iWeight;
}

const float& UiPlot::getOriginWeight() const
{
	return mOriginWeight;
}

void UiPlot::setGridColor(const ci::ColorA& iColor)
{
	mGridColor = iColor;
}

const ci::ColorA& UiPlot::getGridColor() const
{
	return mGridColor;
}

void UiPlot::setGridWeight(const float& iWeight)
{
	mGridWeight = iWeight;
}

const float& UiPlot::getGridWeight() const
{
	return mGridWeight;
}

void UiPlot::recomputeFormatting()
{
	// Overload this method.
}

void UiPlot::deepRecomputeFormatting()
{
	if( mDirty ) {
		if( mFontSuitcaseRef ) {
			mLabelTL->setText( getVertexLabelString( mRange.x1, mRange.y2 ) );
			mLabelTR->setText( getVertexLabelString( mRange.x2, mRange.y2 ) );
			mLabelBL->setText( getVertexLabelString( mRange.x1, mRange.y1 ) );
			mLabelBR->setText( getVertexLabelString( mRange.x2, mRange.y1 ) );
		}
		recomputeFormatting();
		mDirty = false;
	}
}

string UiPlot::getVertexLabelString(const float& iX, const float& iY)
{
	stringstream ss;
	ss << setprecision( 2 ) << fixed << " ( " << iX << ", " << iY << " ) ";
	return ss.str();
}

bool UiPlot::screenToGraphCoord(const Vec2f& iScreenCoord, Vec2f& oGraphCoord, Vec2f& oWidgetRelativeCoord)
{
	Vec2f tPos  = getPosition();
	Vec2f tDim  = getDimension();
	Rectf tRect = Rectf( tPos, tPos + tDim );
	if( tRect.contains( iScreenCoord ) ) {
		// Map to graph range (flipping y):
		oGraphCoord.x = lmap<float>( iScreenCoord.x, tPos.x, tPos.x + tDim.x, mRange.x1, mRange.x2 );
		oGraphCoord.y = lmap<float>( iScreenCoord.y, tPos.y, tPos.y + tDim.y, mRange.y2, mRange.y1 );
		// Map to widget range:
		oWidgetRelativeCoord = ( iScreenCoord - tPos ) / tDim;
		return true;
	}
	return false;
}

float UiPlot::roundToNearest(const float& iValue, const float& iInterval)
{
	if( iInterval == 0.0 ) { return iValue; }
	float tV  = floor( iValue / iInterval );
	return ( ( iValue < ( ( tV + 0.5 ) * iInterval )  ) ? ( tV ) : ( tV + 1.0 ) ) * iInterval;
}
