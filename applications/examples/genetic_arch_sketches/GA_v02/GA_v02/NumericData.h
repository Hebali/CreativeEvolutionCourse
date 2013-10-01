//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include <iostream>
#include <vector>

/** 
 * @brief A templated data table container
 */
template <class DataType>
class Data {
public:
	typedef std::vector<DataType>	Array;		  //!< A one dimensional array of DataType data
	typedef std::vector<Array>		Matrix;		  //!< A two dimensional matrix of DataType data
	
	class Iterator; // forward declaration
	
protected:
	Array		mData;	  //!< The raw data container
	size_t		mColumns; //!< The number of components per feature
	
public:
	/** @brief Basic constructor, initializes empty container and expects data to be formatted with the given number of columns */
	Data(size_t iColumns = 1)
	{
		mColumns = ( ( iColumns == 0 ) ? 1 : iColumns );
	}

	/** @brief Default population constructor, fills container with default value of 0 for the given number of rows and columns */
	Data(const size_t& iColumns, const size_t& iRows)
	{
		mColumns = ( ( iColumns == 0 ) ? 1 : iColumns );
		mData = Array( mColumns * iRows, 0 );
	}
	
	/** @brief Returns the number of rows (features) in the dataset */
	size_t getRowCount() const
	{
		return ( mData.size() / mColumns );
	}
	
	/** @brief Returns the number of columns (components per feature) in the dataset */
	size_t getColumnCount() const
	{
		return mColumns;
	}
	
	/** @brief Adds an individual numeric component to the end of the container */
	void pushComponent(const DataType& iComponent)
	{
		mData.push_back( iComponent );
	}
	
	/** @brief Adds a data row to the end of the container. The input row must contain the appropriate number of columns */
	void pushRow(Array& iRow)
	{
		if( iRow.size() == getColumnCount() ) {
			// Add a row of data to the container:
			for(typename Array::const_iterator it = iRow.begin(); it != iRow.end(); it++) {
				mData.push_back( *it );
			}
		}
	}
	
	/** @brief Adds a data column to the end of each row in the container. The input column must contain the appropriate number of rows (Sub-optimal) */
	void pushColumn(Array& iColumn)
	{
		size_t tRowCount = getRowCount();
		if( iColumn.size() == tRowCount ) {
			// Add a new column to the container:
			mColumns++;
			// Iterate over rows and add column to each:
			size_t tCol = mColumns - 1;
			for(size_t tRow = 0; tRow < tRowCount; tRow++) {
				size_t tIdx = tRow * mColumns + tCol;
				mData.insert( mData.begin() + tIdx, iColumn[ tRow ] );
			}
		}
	}
	
	/** @brief Adds a data row with the given default value to the end of the container */
	void pushEmptyRow(DataType iDefaultValue = 0)
	{
		// Add an empty row of data to the container:
		for(size_t i = 0; i < mColumns; i++) {
			mData.push_back( iDefaultValue );
		}
	}
	
	/** @brief Adds a data column with the given default value to the end of each row in the container (Sub-optimal) */
	void pushEmptyColumn(DataType iDefaultValue = 0)
	{
		size_t tRowCount = getRowCount();
		// Add a new column to the container:
		mColumns++;
		// Iterate over rows and add column to each:
		size_t tCol = mColumns - 1;
		for(size_t tRow = 0; tRow < tRowCount; tRow++) {
			size_t tIdx = tRow * mColumns + tCol;
			mData.insert( mData.begin() + tIdx, iDefaultValue );
		}
	}
	
	/** @brief Returns the component value at the given index */
	DataType& getComponentAt(const size_t& iIndex)
	{
		return mData[ iIndex ];
	}
	
	/** @brief Returns the component value at the given row and column indices */
	DataType& getComponentAt(const size_t& iRow, const size_t& iColumn)
	{
		return mData[ iRow * mColumns + iColumn ];
	}
	
	/** @brief Returns the n-th row of data in the array, where n = iRow */
	Array getRow(const size_t& iRow)
	{
		Array tArray;
		getRow( iRow, tArray );
		return tArray;
	}
	
	/** @brief Returns the n-th row of data in the array as a parameter, where n = iRow */
	void getRow(const size_t& iRow, Array& oOutputArray)
	{
		// Iterate over columns and get data from the appropriate row:
		for(size_t tCol = 0; tCol < mColumns; tCol++) {
			oOutputArray.push_back( mData[ iRow * mColumns + tCol ] );
		}
	}
	
	/** @brief Returns the n-th column of data in the array, where n = iColumn */
	Array getColumn(const size_t& iColumn)
	{
		Array tArray;
		getColumn( iColumn, tArray );
		return tArray;
	}
	
	/** @brief Returns the n-th column of data in the array as a parameter, where n = iColumn */
	void getColumn(const size_t& iColumn, Array& oOutputArray)
	{
		// Iterate over rows and get data from the appropriate column:
		size_t tRowCount = getRowCount();
		for(size_t tRow = 0; tRow < tRowCount; tRow++) {
			oOutputArray.push_back( mData[ tRow * mColumns + iColumn ] );
		}
	}
	
	/** @brief Returns a "row-first" iterator (See class notes for iterator type explanation) */
	Iterator getRowFirstIterator()
	{
		return Iterator( mData, mColumns, false );
	}

	/** @brief Returns a "column-first" iterator (See class notes for iterator type explanation) */
	Iterator getColumnFirstIterator()
	{
		return Iterator( mData, mColumns, true );
	}
	
	/** @brief Returns a data matrix that has been structured in a "row-first" manner (See class notes for iterator type explanation) */
	Matrix getRowFirstData()
	{
		Matrix tMatrix;
		getRowFirstData( tMatrix );
		return tMatrix;
	}
	
	/** @brief Returns a data matrix that has been structured in a "row-first" manner as a parameter (See class notes for iterator type explanation) */
	void getRowFirstData(Matrix& oOutputMatrix)
	{
		Array tCurArray;
		Iterator it = Iterator( mData, mColumns, false );
		while( it.hasNext() ) {
			tCurArray.push_back( it.next() );
			if( it.getColumnIter() == 0 ) {
				oOutputMatrix.push_back( tCurArray );
				tCurArray.clear();
			}
		}
	}
	
	/** @brief Returns a data matrix that has been structured in a "column-first" manner (See class notes for iterator type explanation) */
	Matrix getColumnFirstData()
	{
		Matrix tMatrix;
		getColumnFirstData( tMatrix );
		return tMatrix;
	}
	
	/** @brief Returns a data matrix that has been structured in a "column-first" manner as a parameter (See class notes for iterator type explanation) */
	void getColumnFirstData(Matrix& oOutputMatrix)
	{
		Array  tCurArray;
		Iterator it = Iterator( mData, mColumns, true );
		while( it.hasNext() ) {
			tCurArray.push_back( it.next() );
			if( it.getRowIter() == 0 ) {
				oOutputMatrix.push_back( tCurArray );
				tCurArray.clear();
			}
		}
	}
	
	/** @brief Returns the container's raw data array */
	Array& getRawData()
	{
		return mData;
	}

	/** @brief An iterator type for Data objects */
	class Iterator {
	public:
		Iterator(Array& iDataRef, const size_t& iColumns, const bool& iColumnFirst) :
			mDataRef(iDataRef), mIterCol(0), mIterRow(0), mColCount(iColumns),
			mRowCount(iDataRef.size()/iColumns), mColFirst(iColumnFirst)
		{
		}
		
		/** @brief Returns true if the iterator has not reached the end of range */
		bool hasNext() const
		{
			return ( (mColFirst) ? (mIterCol != mColCount) : (mIterRow != mRowCount) );
		}
		
		/** @brief Returns the next component in the container */
		double& next()
		{
			// Capture current iter state:
			size_t tReturnRow = mIterRow;
			size_t tReturnCol = mIterCol;
			// Column-first handling:
			if( mColFirst ) {
				mIterRow++;
				if( mIterRow == mRowCount ) {
					mIterRow = 0;
					mIterCol++;
				}
			}
			// Row-first handling:
			else {
				mIterCol++;
				if( mIterCol == mColCount ) {
					mIterCol = 0;
					mIterRow++;
				}
			}
			// Return captured state:
			return ( mDataRef[ tReturnRow * mColCount + tReturnCol ] );
		}
		
		/** @brief Returns the index of the current row being iterated */
		const size_t& getRowIter() const
		{
			return mIterRow;
		}
		
		/** @brief Returns the index of the current column being iterated */
		const size_t& getColumnIter() const
		{
			return mIterCol;
		}
		
		/** @brief Returns the number of rows of data that exist within the container */
		const size_t& getRowCount() const
		{
			return mRowCount;
		}
		
		/** @brief Returns the number of columns of data that exist within the container */
		const size_t& getColumnCount() const
		{
			return mColCount;
		}
		
		/** @brief Returns true if the iterator is a "column-first" iterator. Otherwise, it is a "row-first" iterator */
		const bool& isColumnFirst() const
		{
			return mColFirst;
		}

	private:
		bool			mColFirst;	//!< If true, will iterate in a component-wise manner (see example above)
		Array&			mDataRef;	//!< A reference to the data array
		size_t			mIterCol;	//!< The current component
		size_t			mIterRow;	//!< The current feature
		size_t			mColCount;	//!< The number of components per feature
		size_t			mRowCount;	//!< The number of features
	};
};
