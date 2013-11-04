//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include "GuiText.h"

using namespace std;
using namespace ci;

GuiText::GuiText(std::string iText, std::string iFontName, int iFontSize, FontStyle iStyle, FontSuitcase* iSuitcaseRef) :
	GuiBase(),
	mRetina( app::getWindowContentScale() > 1 ),
	mTextColor( ColorA::white() ),
	mHighlightColor( ColorA( 0, 0, 0, 0 ) ),
	mGuides( false )
{
	if( iSuitcaseRef ) {
		FontFamily* tFamily = iSuitcaseRef->getFamilyRef( iFontName );
		if( tFamily ) {
			FontFamilyNode* tNode = tFamily->getNodeRef( iFontSize );
			if( tNode ) {
				mFontRef     = tNode->getStyle( iStyle );
				mFontOptions = tNode->getDrawOptions();
				setText( iText );
			}
		}
	}
}

GuiText::~GuiText()
{
}

void GuiText::draw()
{
	if( mText.empty() ) { return; }
	// Gather text measurements:
	float tMult      = ( mRetina ? 0.5 : 1.0 );
	Vec2f tAscent    = Vec2f( 0.0, mFontRef->getAscent() * tMult );
	Vec2f tDescent   = Vec2f( 0.0, mFontRef->getDescent() * tMult );
	Vec2f tPosOffset = getPosition() + Vec2f( 0.0, mDimension.y - tDescent.y );
	// Gather guide measurements:
	Vec2f tTextAscnt = tPosOffset - tAscent;
	Vec2f tTextDscnt = tPosOffset + tDescent;
	// Draw highlight:
	gl::color( mHighlightColor );
	gl::drawSolidRect( Rectf( tTextAscnt, tTextDscnt + Vec2f( mDimension.x, 0 ) ) );
	// Draw guides:
	if( mGuides ) {
		// Draw text baseline, ascent and descent:
		gl::color( 1, 1, 0 );
		gl::drawLine( tPosOffset, tPosOffset + Vec2f( mDimension.x, 0 ) );
		gl::color( 1, 0, 1 );
		gl::drawLine( tTextAscnt, tTextAscnt + Vec2f( mDimension.x, 0 ) );
		gl::color( 0, 1, 1 );
		gl::drawLine( tTextDscnt, tTextDscnt + Vec2f( mDimension.x, 0 ) );
	}
	// Draw text:
	gl::color( mTextColor );
	mFontRef->drawGlyphs( mGlyphs, tPosOffset, mFontOptions );
}

void GuiText::setText(const string& iText)
{
	// Set string value:
	mText = iText;
	// Set glyphs:
	mGlyphs = mFontRef->getGlyphPlacements( mText, mFontOptions );
	// Set dimensions from string:
	mDimension = mFontRef->measureString( mText, mFontOptions ) * ( mRetina ? 0.5 : 1.0 );
	mFlowW = UI_FIXED;
	mFlowH = UI_FIXED;
}

const string& GuiText::getText() const
{
	return mText;
}

void GuiText::setTextColor(const ci::ColorA& iColor)
{
	mTextColor = iColor;
}

const ci::ColorA& GuiText::getTextColor() const
{
	return mTextColor;
}

void GuiText::setHighlightColor(const ci::ColorA& iColor)
{
	mHighlightColor = iColor;
}

const ci::ColorA& GuiText::getHighlightColor() const
{
	return mHighlightColor;
}

void GuiText::setGuideVisibility(const bool& iVisible)
{
	mGuides = iVisible;
}

const bool& GuiText::getGuideVisibility() const
{
	return mGuides;
}