//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#include "GuiTypography.h"

using namespace std;
using namespace ci;

#pragma mark -
#pragma mark FONT_FAMILY_NODE

FontFamilyNode::FontFamilyNode(string iRegularSrc, string iItalicSrc, string iBoldSrc, string iBoldItalicSrc, int iFontSize)
: mSize( iFontSize )
{
	// Check whether app is running on a retina display:
	bool tRetina = ( app::getWindowContentScale() > 1 );
	// Prepare font options:
	mTexFontOptions = gl::TextureFont::DrawOptions();
	mTexFontOptions.scale( ( tRetina ? 0.5 : 1.0 ) );
	mTexFontOptions.pixelSnap( false );
	// Prepare texture fonts:
	if( !iRegularSrc.empty() ) {
		// Construct data source ref from file path:
		DataSourceRef tSrcRef = DataSourcePath::create( fs::path( iRegularSrc ) );
		// Create font:
		Font tFont = Font( tSrcRef, iFontSize * ( tRetina ? 2.0 : 1.0 ) );
		// Create texture font:
		if( tRetina ) { mRegular = gl::TextureFont::create( tFont, gl::TextureFont::Format().enableMipmapping() ); }
		else          { mRegular = gl::TextureFont::create( tFont ); }
	}
	if( !iItalicSrc.empty() ) {
		// Construct data source ref from file path:
		DataSourceRef tSrcRef = DataSourcePath::create( fs::path( iItalicSrc ) );
		// Create font:
		Font tFont = Font( tSrcRef, iFontSize * ( tRetina ? 2.0 : 1.0 ) );
		// Create texture font:
		if( tRetina ) { mItalic = gl::TextureFont::create( tFont, gl::TextureFont::Format().enableMipmapping() ); }
		else          { mItalic = gl::TextureFont::create( tFont ); }
	}
	if( !iBoldSrc.empty() ) {
		// Construct data source ref from file path:
		DataSourceRef tSrcRef = DataSourcePath::create( fs::path( iBoldSrc ) );
		// Create font:
		Font tFont = Font( tSrcRef, iFontSize * ( tRetina ? 2.0 : 1.0 ) );
		// Create texture font:
		if( tRetina ) { mBold = gl::TextureFont::create( tFont, gl::TextureFont::Format().enableMipmapping() ); }
		else          { mBold = gl::TextureFont::create( tFont ); }
	}
	if( !iBoldItalicSrc.empty() ) {
		// Construct data source ref from file path:
		DataSourceRef tSrcRef = DataSourcePath::create( fs::path( iBoldItalicSrc ) );
		// Create font:
		Font tFont = Font( tSrcRef, iFontSize * ( tRetina ? 2.0 : 1.0 ) );
		// Create texture font:
		if( tRetina ) { mBoldItalic = gl::TextureFont::create( tFont, gl::TextureFont::Format().enableMipmapping() ); }
		else          { mBoldItalic = gl::TextureFont::create( tFont ); }
	}
}

FontFamilyNode::~FontFamilyNode()
{
}

const int& FontFamilyNode::getSize() const
{
	return mSize;
}

bool FontFamilyNode::hasStyle(const FontStyle& iType) const
{
	switch( iType ) {
		case REGULAR:		{ return hasRegular(); }
		case ITALIC:		{ return hasItalic(); }
		case BOLD:			{ return hasBold(); }
		case BOLD_ITALIC:	{ return hasBoldItalic(); }
		default:			{ return false; }
	}
}

bool FontFamilyNode::hasRegular() const
{
	return ( mRegular.get() != NULL );
}

bool FontFamilyNode::hasItalic() const
{
	return ( mItalic.get() != NULL );
}

bool FontFamilyNode::hasBold() const
{
	return ( mBold.get() != NULL );
}

bool FontFamilyNode::hasBoldItalic() const
{
	return ( mBoldItalic.get() != NULL );
}

gl::TextureFontRef FontFamilyNode::getStyle(const FontStyle& iType) const
{
	switch( iType ) {
		case REGULAR:		{ return getRegular(); }
		case ITALIC:		{ return getItalic(); }
		case BOLD:			{ return getBold(); }
		case BOLD_ITALIC:	{ return getBoldItalic(); }
		default:			{ return getRegular(); }
	}
}

gl::TextureFontRef FontFamilyNode::getRegular() const
{
	return mRegular;
}

gl::TextureFontRef FontFamilyNode::getItalic() const
{
	return mItalic;
}

gl::TextureFontRef FontFamilyNode::getBold() const
{
	return mBold;
}

gl::TextureFontRef FontFamilyNode::getBoldItalic() const
{
	return mBoldItalic;
}

gl::TextureFont::DrawOptions FontFamilyNode::getDrawOptions() const
{
	return mTexFontOptions;
}

#pragma mark -
#pragma mark FONT_FAMILY

FontFamily::FontFamily(string iRegularSrc, string iItalicSrc, string iBoldSrc, string iBoldItalicSrc)
: mRegularPath( iRegularSrc ), mItalicPath( iItalicSrc ), mBoldPath( iBoldSrc ), mBoldItalicPath( iBoldItalicSrc )
{
}

FontFamily::~FontFamily()
{
	// Delete all nodes in font family:
	for(map<int,FontFamilyNode*>::const_iterator it = mNodes.begin(); it != mNodes.end(); it++) {
		delete (*it).second;
	}
	mNodes.clear();
}

FontFamilyNode* FontFamily::getNodeRef(const int& iSize)
{
	// Try to find node in map:
	map<int,FontFamilyNode*>::const_iterator iter = mNodes.find( iSize );
	// If not found, insert:
	if( iter == mNodes.end() ) {
		mNodes[ iSize ] = new FontFamilyNode( mRegularPath, mItalicPath, mBoldPath, mBoldItalicPath, iSize );
		return mNodes[ iSize ];
	}
	// If found, return:
	return (*iter).second;
}

#pragma mark -
#pragma mark FONT_SUITCASE

FontSuitcase::FontSuitcase()
{
}

FontSuitcase::~FontSuitcase()
{
	// Delete all font families:
	for(map<string,FontFamily*>::const_iterator it = mFamilies.begin(); it != mFamilies.end(); it++) {
		delete (*it).second;
	}
	mFamilies.clear();
}

void FontSuitcase::addFamily(const string& iFamilyName, string iRegularSrc, string iItalicSrc, string iBoldSrc, string iBoldItalicSrc)
{
	// If font family does not exist, add it:
	if( mFamilies.find( iFamilyName ) == mFamilies.end() ) {
		mFamilies[ iFamilyName ] = new FontFamily( iRegularSrc, iItalicSrc, iBoldSrc, iBoldItalicSrc );
	}
}

FontFamily* FontSuitcase::getFamilyRef(const string& iFamilyName)
{
	// Try to find family in map:
	map<string,FontFamily*>::const_iterator iter = mFamilies.find( iFamilyName );
	// Check that family exists:
	if( iter != mFamilies.end() ) {
		return (*iter).second;
	}
	return NULL;
}

ci::gl::TextureFontRef FontSuitcase::getFontRef(const string& iFamilyName, const int& iSize, const FontStyle& iStyle)
{
	// Try to find family in map:
	map<string,FontFamily*>::const_iterator iter = mFamilies.find( iFamilyName );
	// Check that family exists:
	if( iter != mFamilies.end() ) {
		FontFamilyNode* tNode = (*iter).second->getNodeRef( iSize );
		if( tNode ) {
			return tNode->getStyle( iStyle );
		}
	}
	return NULL;
}
