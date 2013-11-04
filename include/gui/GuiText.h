//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include "GuiBase.h"
#include "GuiTypography.h"

/**
 * @brief A scenegraph node representing a text label
 */
class UiText : public UiBase {
protected:
	
	typedef std::pair<uint16_t,ci::Vec2f>	GlyphPair;		//!< A font glyph data item
	typedef std::vector<GlyphPair>			GlyphVec;		//!< A vector of font glyph data items
	typedef GlyphVec::iterator				GlyphVecIter;	//!< An iterator type for a vector of font glyph data items
	typedef GlyphVec::reverse_iterator		GlyphVecRiter;	//!< A reverse iterator type for a vector of font glyph data items
	typedef GlyphVec::const_iterator		GlyphVecCiter;	//!< A const iterator type for a vector of font glyph data items
	
protected:
	
	std::string							mText;				//!< The text label
	ci::ColorA							mTextColor;			//!< The text color
	ci::ColorA							mHighlightColor;	//!< The text highlight color
	bool								mRetina;			//!< Flags whether display is high-density
	bool								mGuides;			//!< Flags whether text guides should be rendered
	GlyphVec							mGlyphs;			//!< Stores the text label's glyph placements
	ci::gl::TextureFontRef				mFontRef;			//!< A reference to the label's font
	ci::gl::TextureFont::DrawOptions	mFontOptions;		//!< A reference to the label's font options
	
public:
	
	/** @brief Basic constructor */
	UiText(std::string iText = "", std::string iFontName = "", int iFontSize = 12, FontStyle iStyle = FontStyle::REGULAR, FontSuitcase* iSuitcaseRef = NULL);
	
	/** @brief Virtual destructor */
	virtual ~UiText();
	
	/** @brief Overloadable draw method */
	virtual void			draw();
		
	/** @brief Sets the text label */
	void					setText(const std::string& iText);
	
	/** @brief Returns the text label */
	const std::string&		getText() const;
	
	/** @brief Sets the text color */
	void					setTextColor(const ci::ColorA& iColor);
	
	/** @brief Returns the text color */
	const ci::ColorA&		getTextColor() const;
	
	/** @brief Sets the text highlight color */
	void					setHighlightColor(const ci::ColorA& iColor);
	
	/** @brief Returns the text highlight color */
	const ci::ColorA&		getHighlightColor() const;
	
	/** @brief Sets the visibility of the text guide lines */
	void					setGuideVisibility(const bool& iGuides);
	
	/** @brief Returns true if text guide lines are visible */
	const bool&				getGuideVisibility() const;
};
