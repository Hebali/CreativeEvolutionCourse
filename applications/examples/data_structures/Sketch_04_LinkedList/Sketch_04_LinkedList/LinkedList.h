//////////////////////////////////////////////////
/*         Evolution as a Creative Tool         */
/*           Taught by Patrick Hebron           */
/* Interactive Telecommunications Program (ITP) */
/*             New York University              */
/*                  Fall 2013                   */
//////////////////////////////////////////////////

#pragma once

#include <iostream>

#pragma mark -
#pragma mark LINKED_LIST_NODE

/** @brief represents an individual node within a templated singly-linked-list container */
template <class T>
class LListNode
{
public:
	/** @brief node constructor method */
	LListNode(const T& iValue) : mValue( iValue ), mNext( NULL )
	{
	}
	
	/** @brief node destructor method */
	~LListNode()
	{
		if( mNext )
		{
			delete mNext;
		}
	}
	
	/** @brief returns true if node has a valid next-node pointer */
	bool		hasNext() const { return ( mNext != NULL ); }
	
	/** @brief sets the node's pointer to the next node in the list */
	void		setNext(LListNode* iNext) { mNext = iNext; }
	
	/** @brief returns a pointer to the next node in the list */
	LListNode*	getNext() const { return mNext; }
	
	/** @brief sets the node's value to the given input */
	void		setValue(const T& iValue) { mValue = iValue; }
	
	/** @brief returns a const reference to the node's value */
	const T&	getValue() const { return mValue; }
	
private:
	T			mValue; //!< the value associated with this node
	LListNode*	mNext;  //!< a pointer to the next node in the list
};

#pragma mark -
#pragma mark LINKED_LIST

/** @brief represents a templated singly-linked-list container */
template <class T>
class LList
{
public:
	/** @brief list constructor method */
	LList() : mFirst( NULL )
	{
	}
	
	/** @brief list destructor method */
	~LList()
	{
		clear();
	}
	
	/** @brief removes all nodes from the list */
	void clear()
	{
		// If list is not empty:
		if( mFirst )
		{
			// Set chain of deletions in motion:
			delete mFirst;
			// Reset pointer:
			mFirst = NULL;
		}
	}
	
	/** @brief returns true if there are no nodes in the linked list */
	bool empty()
	{
		return ( mFirst == NULL );
	}
	
	/** @brief returns the number of nodes in the linked list */
	size_t size()
	{
		// Initialize counter:
		size_t tCount = 0;
		// Set iterator to front:
		LListNode<T>* tCurr = mFirst;
		// Iterate linked list until reaching back:
		while( tCurr )
		{
			// Increment node count:
			tCount++;
			// Set iterator to next node:
			tCurr = tCurr->getNext();
		}
		// Return count:
		return tCount;
	}
	
	/** @brief returns the first node in list or null if none exists */
	LListNode<T>* front()
	{
		// Return first node:
		return mFirst;
	}
	
	/** @brief returns the last node in list or null if none exists */
	LListNode<T>* back()
	{
		// Set iterator to front:
		LListNode<T>* tCurr = mFirst;
		// Iterate linked list until reaching back:
		while( tCurr && tCurr->hasNext() )
		{
			// Set iterator to next node:
			tCurr = tCurr->getNext();
		}
		// Return last node:
		return tCurr;
	}
	
	/** @brief returns the node at the given index, if index is in bounds, otherwise returns null */
	LListNode<T>* at(const size_t& iIndex)
	{
		// Handle empty list:
		if( !mFirst ) { return NULL; }
		// Initialize counter:
		size_t tCount = 0;
		// Set iterator to front:
		LListNode<T>* tCurr = mFirst;
		// Iterate linked list until reaching back:
		while( tCurr && tCount < iIndex )
		{
			// Increment node count:
			tCount++;
			// Set iterator to next node:
			tCurr = tCurr->getNext();
		}
		// Return node:
		return tCurr;
	}
	
	/** @brief removes the front node of the linked list */
	void pop_front()
	{
		// Handle non-empty list:
		if( mFirst )
		{
			// Temporarily store the second node:
			LListNode<T>* tTemp = mFirst->getNext();
			// Remove the first node from the chain:
			mFirst->setNext( NULL );
			// Delete first node:
			delete mFirst;
			// Move temp node into first position:
			mFirst = tTemp;
		}
	}
	
	/** @brief removes the back node of the linked list */
	void pop_back()
	{
		// Handle non-empty list:
		if( mFirst )
		{
			// Set iterator to front:
			LListNode<T>* tCurr = mFirst;
			LListNode<T>* tPrev = tCurr;
			// Iterate linked list until reaching back:
			while( tCurr )
			{
				// Check whether node has a next-pointer:
				if( tCurr->hasNext() )
				{
					// Set previous iterator to current node:
					tPrev = tCurr;
					// Set iterator to next node:
					tCurr = tCurr->getNext();
				}
				else
				{
					// Remove previous node's reference to current:
					tPrev->setNext( NULL );
					// Delete current node:
					delete tCurr;
					// Escape from iteration loop:
					break;
				}
			}
		}
	}
	
	/** @brief adds a new node to the front of the linked list */
	void push_front(const T& iValue)
	{
		// Add to empty list:
		if( !mFirst )
		{
			mFirst = new LListNode<T>( iValue );
		}
		// Add to non-empty list:
		else
		{
			// Create a new front node:
			LListNode<T>* tFirst = new LListNode<T>( iValue );
			// Store a pointer to the current front node:
			LListNode<T>* tSecond = mFirst;
			// Set list pointer to new front node:
			mFirst = tFirst;
			// Add link between first and second nodes:
			mFirst->setNext( tSecond );
		}
	}
	
	/** @brief adds a new node to the back of the linked list */
	void push_back(const T& iValue)
	{
		// Add to empty list:
		if( !mFirst )
		{
			mFirst = new LListNode<T>( iValue );
		}
		// Add to non-empty list:
		else
		{
			// Set iterator to front:
			LListNode<T>* tCurr = mFirst;
			// Iterate linked list until reaching back:
			while( tCurr )
			{
				// Check whether node has a next-pointer:
				if( tCurr->hasNext() )
				{
					// Set iterator to next node:
					tCurr = tCurr->getNext();
				}
				else
				{
					// Add new next node to current:
					tCurr->setNext( new LListNode<T>( iValue ) );
					// Escape from iteration loop:
					break;
				}
			}
		}
	}
	
	/** @brief prints the sequence of values stored in the linked list */
	void print()
	{
		// Set iterator to front:
		LListNode<T>* tPtr = mFirst;
		// Iterate linked list until reaching back:
		while( tPtr )
		{
			// Print current node's value:
			std::cout << tPtr->getValue() << std::endl;
			// Set iterator to next node:
			tPtr = tPtr->getNext();
		}
	}
	
private:
	LListNode<T>* mFirst; //!< a pointer to the first node in the list
};

