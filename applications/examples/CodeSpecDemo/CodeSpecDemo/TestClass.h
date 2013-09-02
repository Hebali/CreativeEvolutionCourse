//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
/*                                              */
/*     The code in this file was written by:    */
/*                YOUR_NAME_HERE                */
//////////////////////////////////////////////////

#pragma once

#include <iostream>

namespace evo { namespace types {
	
	static const bool kGlobalConstantExample = true;
	
	/**
	 * @brief A simple test class that does nothing useful
	 * @author YOUR_NAME_HERE
	 */
	class TestClass
	{
	public:
		
		TestClass();
		~TestClass();
		
		const std::string& getString() const;
		std::string& getString();
		
		void setString(const std::string iString);
		
	private:
		
		std::string mString;
	};
	
} } // namespace evo::types
