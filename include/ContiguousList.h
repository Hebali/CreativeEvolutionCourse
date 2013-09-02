//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

# pragma once

#include <iostream>
#include <algorithm>

namespace evo { namespace types {
	
#pragma mark -
#pragma mark CONTIGUOUS_LIST
	
	static const size_t kGlobalCListDefaultInitSize = 10;
	
	/** @brief represents a templated contiguous-memory-list container */
	template <class T>
	class CList
	{
	public:
		/** @brief default contiguous-list constructor method */
		CList(size_t iArrayLimit = kGlobalCListDefaultInitSize) : mArray( NULL )
		{
			mArrayInitLimit = ( iArrayLimit <= 1 ? 1 : iArrayLimit );
			mArrayLimit = mArrayInitLimit;
			// Clear internal trackers:
			clear();
			// Allocate array:
			mArray = new T[ mArrayLimit ];
		}
		
		/** @brief contiguous-list destructor method */
		~CList()
		{
			clear();
			// Delete array:
			delete [] mArray;
		}
		
		/** @brief removes all nodes from the list */
		void clear()
		{
			// Reset interal index trackers:
			mArrayFrontIdx = 0;
			mArrayBackIdx = -1;
			mArrayLimit = mArrayInitLimit;
		}
		
		/** @brief returns the number of nodes in the list */
		size_t size() const
		{
			return ( mArrayLimit );
		}
		
		/** @brief adds a new node to the back of the contiguous-list */
		void push_back(const T& iValue)
		{
			// Check whether list needs to be resized:
			if( mArrayBackIdx >= mArrayLimit - 1 )
			{
				resize();
			}
			// Increment back index:
			mArrayBackIdx++;
			// Insert value at appropriate index:
			mArray[ mArrayBackIdx ] = iValue;
		}
		
		/** @brief prints the sequence of values stored in the contiguous-list */
		void print()
		{
			// Iterate over index range:
			for(int32_t i = mArrayFrontIdx; i <= mArrayBackIdx; i++)
			{
				std::cout << mArray[ i ] << std::endl;
			}
		}
		
		/** @brief TODO */
		T& operator[](const size_t& iIndex)
		{
			return mArray[ iIndex ];
		}
		
		/** @brief TODO */
		const T& operator[](const size_t& iIndex) const
		{
			return mArray[ iIndex ];
		}
		
	private:
		
		void resize()
		{
			// Double the size limit:
			size_t tNewLimit = mArrayLimit * 2;
			// Initialize an array with the new size limit:
			T* tNewArray = new T[ tNewLimit ];
			// Copy the contents of the primary array into the new one:
			std::copy( mArray, mArray + mArrayLimit, tNewArray );
			// Delete the old array:
			delete [] mArray;
			// Point to the new data:
			mArray = tNewArray;
			// Set the new array limit:
			mArrayLimit = tNewLimit;
		}
		
		size_t	mArrayInitLimit; //!< the initial maximum size of the internal dynamic array
		size_t	mArrayLimit;     //!< the maximum size of the internal dynamic array
		int32_t	mArrayFrontIdx;  //!< the index of the last element of the array
		int32_t	mArrayBackIdx;   //!< the index of the last element of the array
		T*		mArray;	         //!< a pointer to the internal dynamic array
	};
	
} } // namespace evo::types
