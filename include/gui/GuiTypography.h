//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include <iostream>
#include <string>
#include <map>

#include "cinder/app/AppNative.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Color.h"
#include "cinder/Font.h"
#include "cinder/Text.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"

enum FontStyle
{
	REGULAR, ITALIC, BOLD, BOLD_ITALIC
};

enum FontAlign
{
	LEFT, CENTER, RIGHT, TOP, MIDDLE, BOTTOM
};

class FontFamilyNode {
public:
	
	/** @brief Basic constructor */
	FontFamilyNode(std::string iRegularSrc = "", std::string iItalicSrc = "", std::string iBoldSrc = "", std::string iBoldItalicSrc = "", int iFontSize = 24);
	
	/** @brief Destructor */
	~FontFamilyNode();
	
	const int&							getSize() const;
	
	bool								hasStyle(const FontStyle& iType) const;
	bool								hasRegular() const;
	bool								hasItalic() const;
	bool								hasBold() const;
	bool								hasBoldItalic() const;
	
	ci::gl::TextureFontRef				getStyle(const FontStyle& iType) const;
	ci::gl::TextureFontRef				getRegular() const;
	ci::gl::TextureFontRef				getItalic() const;
	ci::gl::TextureFontRef				getBold() const;
	ci::gl::TextureFontRef				getBoldItalic() const;
	
	ci::gl::TextureFont::DrawOptions	getDrawOptions() const;
	
private:
	int									mSize;
	ci::gl::TextureFontRef				mRegular;
	ci::gl::TextureFontRef				mItalic;
	ci::gl::TextureFontRef				mBold;
	ci::gl::TextureFontRef				mBoldItalic;
	ci::gl::TextureFont::DrawOptions	mTexFontOptions;
};

class FontFamily {
	
	typedef std::map<int,FontFamilyNode*>		FontFamilyNodeMap;		//!< A map type storing <int,FontFamilyNode*> pairs
	typedef FontFamilyNodeMap::iterator			FontFamilyNodeMapIter;	//!< An iterator type for a map storing <int,FontFamilyNode*> pairs
	typedef FontFamilyNodeMap::const_iterator	FontFamilyNodeMapCiter;	//!< A const iterator type for a map storing <int,FontFamilyNode*> pairs
	
private:
	
	FontFamilyNodeMap	mNodes;				//!< The node map
	std::string			mRegularPath;		//!< The file path associated with the regular style node
	std::string			mItalicPath;		//!< The file path associated with the italic style node
	std::string			mBoldPath;			//!< The file path associated with the bold style node
	std::string			mBoldItalicPath;	//!< The file path associated with the bold-italic style node
	
public:
	
	/** @brief Basic constructor */
	FontFamily(std::string iRegularSrc = "", std::string iItalicSrc = "", std::string iBoldSrc = "", std::string iBoldItalicSrc = "");
	
	/** @brief Destructor */
	~FontFamily();
	
	/** @brief Returns a pointer to the font node with the given pt size */
	FontFamilyNode*		getNodeRef(const int& iSize);
};

/**
 * @brief A wrapper for a collection of gl::TextureFont families
 */
class FontSuitcase {
public:
	
	typedef std::map<std::string,FontFamily*>	FontFamilyMap;		//!< A map type storing <std::string,FontFamily*> pairs
	typedef FontFamilyMap::iterator				FontFamilyMapIter;	//!< An iterator type for a map storing <std::string,FontFamily*> pairs
	typedef FontFamilyMap::const_iterator		FontFamilyMapCiter;	//!< A const iterator type for a map storing <std::string,FontFamily*> pairs
	
private:
	
	FontFamilyMap	mFamilies;	//!< The suitcase's font family map
	
public:
	
	/** @brief Default constructor */
	FontSuitcase();
	
	/** @brief Destructor */
	~FontSuitcase();
	
	/** @brief Adds a font family to the suitcase using the associated family name and file paths */
	void					addFamily(const std::string& iFamilyName, std::string iRegularSrc = "", std::string iItalicSrc = "",
									  std::string iBoldSrc = "", std::string iBoldItalicSrc = "");
	
	/** @brief Returns a pointer to the font family with the given input name */
	FontFamily*				getFamilyRef(const std::string& iFamilyName);
	
	/** @brief Returns a reference to the TextureFont with the given family name, size and style */
	ci::gl::TextureFontRef	getFontRef(const std::string& iFamilyName, const int& iSize, const FontStyle& iStyle);
};