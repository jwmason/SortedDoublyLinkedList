#ifndef __SORTED_DOUBLY_LINKED_LIST_HPP
#define __SORTED_DOUBLY_LINKED_LIST_HPP

#include <stdexcept>

class KeyNotFoundException : public std::runtime_error 
{
public:
	explicit KeyNotFoundException(const std::string & err) : std::runtime_error(err) {}
};

template<typename Key, typename Value>
class SortedList
{
private:
	// make the doubly linked list
	struct Node
	{
		Key key;
		Value value;
		Node* prev;
		Node* next;

		Node(const Key& k, const Value& v) : key(k), value(v), prev(nullptr), next(nullptr) {}
	};

	Node* head;

public:
	SortedList();

	// Note:  copy constructors are required.
	// Be sure to do a "deep copy" -- if I 
	// make a copy and modify one, it should not affect the other. 
	SortedList(const SortedList & st);
	SortedList & operator=(const SortedList & st);
	~SortedList();


	size_t size() const noexcept;
	bool isEmpty() const noexcept;


	// If this key is already present, return false.
	// otherwise, return true after inserting this key/value pair.
	bool insert(const Key &k, const Value &v); 

	// Return true if this SortedList contains a mapping of this key.
	bool contains(const Key &k) const noexcept; 


	// removes the given key (and its associated value) from the list.
	// If that key is not in the list, this will silently do nothing.
	void remove(const Key &k);

	// If this key exists in the list, this function returns how many keys are in the list that are less than it.
	// If this key does not exist in the list, this throws a KeyNotFoundException.
	unsigned getIndex(const Key &k) const;

	// If this key does not exist in the list, this throws a KeyNotFoundException.
	// subscript operator for non-const objects returns modifiable lvalue
	Value & operator[] (const Key &k) ;



	// subscript operator for nonconst objects returns non-modifiable lvalue
	// DON'T FORGET TO TEST THIS FUNCTION EXPLICITLY
	// I omitted it from required test cases on purpose.
	// Write a test case that calls this -- I showed you how in class a few times.
	// In projects like this (which also come up in ICS 46), forgetting to test this
	// is a major cause of lost points, sometimes disproportionate to how easy the fix is.
	// Don't let that happen to you.
	// (I'd rather it doesn't happen to anyone)
	const Value & operator [] (const Key & k) const; 



	// returns the largest key in the list that is < the given key.
	// If no such element exists, this throws a KeyNotFoundException.
	// Hint:  think carefully about the situation where none would exist.
	//		Think also very carefully about how this is different
	//		from the subscript operator functions and the getIndex function.
	// A little bit of thinking ahead of time will make this *much easier* to program.
	const Key & largestLessThan(const Key & k) const;



	// This is similar to the previous one, but has some key (pun intended) differences.
	// I recommend you finish the previous function and *extensively* test it first.
	// (be sure to think about boundary cases!)
	// THEN, think carefully about how this differs from that -- you might want to 
	// approach it slightly differently than you approached that one.
	// The time you spend thinking about this will likely save you even more time
	// 	when you can code this quicker and have fewer bugs.
	// There's no prize for "first to finish this function."  Write the previous one first.
	const Key & smallestGreaterThan(const Key & k) const;

	
	// Two SortedLists are equal if and only if:
	//	* They have the same number of elements
	//	* Each element matches in both key and value.
	// This is only a meaningful operator when key-type and value-type both have
	// an implemented operator==.  As such, we will only test with those.
	bool operator==(const SortedList & l) const noexcept;

	// preincrement every Value (not key) in the list.
	// Unlike a numeric type's ++ operator, this does not return a copy of itself.
	// Note that this is silly and is done explicitly to have overload this operator
	// in this assignment.  
	// Because the syntax of pre-incrementing an element can be weird, although
	// it is what you probably think it is, for purposes of this assignment, I will 
	// only test this with value-types whose pre-increment and post-increment
	// operators have the same end-state.
	void operator++();


};


template<typename Key, typename Value>
SortedList<Key,Value>::SortedList() : head(nullptr)
{}


template<typename Key, typename Value>
SortedList<Key,Value>::SortedList(const SortedList & st)
{
}


template<typename Key, typename Value>
SortedList<Key,Value> & SortedList<Key,Value>::operator=(const SortedList & st)
{
	if( this != &st )
	{

	}

	return *this;

}
	
template<typename Key, typename Value>
SortedList<Key,Value>::~SortedList()
{
}


template<typename Key, typename Value>
size_t SortedList<Key,Value>::size() const noexcept
{
	// Initialize size counter and Node pointer holder
	size_t counter = 0;
	Node * tmp = head;
	// Loop through every Node and count it
	while (tmp != nullptr)
	{
		counter ++;
		tmp = tmp -> next;
	}
	return counter;
}

template<typename Key, typename Value>
bool SortedList<Key,Value>::isEmpty() const noexcept
{
	return false;  // STUB;  fix then remove this comment
}


// If this key is already present, return false.
// otherwise, return true after inserting this key/value pair/.
template<typename Key, typename Value>
bool SortedList<Key,Value>::insert(const Key &k, const Value &v)
{
	return false;
}




template<typename Key, typename Value>
bool SortedList<Key,Value>::contains(const Key &k) const noexcept
{
	return false;
}

template<typename Key, typename Value>
void SortedList<Key,Value>::remove(const Key &k) 
{
}



// If this key exists in the list, this function returns how many keys are in the list that are less than it.
// If this key does not exist in the list, this throws a KeyNotFoundException.
template<typename Key, typename Value>
unsigned SortedList<Key,Value>::getIndex(const Key &k) const
{
	throw KeyNotFoundException{"Key not found in list"};  // STUB;  fix then remove this comment

}

template<typename Key, typename Value>
Value & SortedList<Key,Value>::operator[] (const Key &k) 
{
	throw KeyNotFoundException{"Key not found in list"};  // STUB;  fix then remove this comment

}

template<typename Key, typename Value>
const Value & SortedList<Key,Value>::operator[] (const Key &k) const 
{
	throw KeyNotFoundException{"Key not found in list"};  // STUB;  fix then remove this comment
}

template<typename Key, typename Value>
const Key & SortedList<Key,Value>::largestLessThan(const Key & k) const
{
	throw KeyNotFoundException{"Key not found in list"};  // STUB;  fix then remove this comment
}

template<typename Key, typename Value>
const Key & SortedList<Key,Value>::smallestGreaterThan(const Key & k) const
{
	throw KeyNotFoundException{"Key not found in list"};   // STUB;  fix then remove this comment
}



template <typename Key, typename Value>
bool SortedList<Key,Value>::operator==(const SortedList & l) const noexcept
{
	return false;  // STUB;  fix then remove this comment
}

template <typename Key, typename Value>
void SortedList<Key,Value>::operator++()
{
}




#endif 

