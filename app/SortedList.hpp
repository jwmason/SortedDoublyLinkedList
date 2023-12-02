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
SortedList<Key,Value>::SortedList(const SortedList & st) : head(nullptr)
{
	// SortedList l1 = l2
	// Initialize Node pointer
	Node* current = st.head;
	Node* tail = nullptr;
	// Loop through all the Nodes
	while (current != nullptr)
	{
		// Initialize a newNode
		Node* newNode = new Node(current->key, current->value);
		// Check if head is null, then set newNode to it
		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		// If not, increment the newNode (it is already in order)
		else
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		// Increment Node
		current = current->next;
	}
}


template<typename Key, typename Value>
SortedList<Key,Value> & SortedList<Key,Value>::operator=(const SortedList & st)
{
	// l1 = l2
	if ( this != &st )
	{
		// Loop through all the Nodes in SortedList and delete them
		while (head != nullptr)
		{
			Node* current = head;
			head = head->next;
			delete current;
		}
		// Copy st into given SortedList
		Node* current = st.head;
		Node* tail = nullptr;
		// Loop through Nodes in st and add to SortedList
		while (current != nullptr)
		{
			Node* newNode = new Node(current->key, current->value);
			// If the st is empty, set newNode as head and tail
			if (head == nullptr)
			{
				head = newNode;
				tail = newNode;
			}
			// If not, increment the newNode (it is already in order)
			else
			{
				tail->next = newNode;
				newNode->prev = tail;
				tail = newNode;
			}
			// Increment node
			current = current->next;
		}
	}
	return *this;
}

template<typename Key, typename Value>
SortedList<Key,Value>::~SortedList()
{
	// Loop through every Node and delete it
	while(head != nullptr)
	{
		Node* current = head;
		head = head->next;
		delete current;
	}
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
	// If there is no Nodes, return true. Else return false.
	if (head == nullptr)
	{
		return true;
	}
	return false;
}


// If this key is already present, return false.
// otherwise, return true after inserting this key/value pair/.
template<typename Key, typename Value>
bool SortedList<Key,Value>::insert(const Key &k, const Value &v)
{
	// Make a new Node
	Node* newNode = new Node(k, v);

	// If the head is null or the new key is less then the key of the current Node, new Node is inserted at the beginning of the list
	if (head == nullptr || k < head->key)
	{
		// Set the next Node to head and see if it exists
		newNode->next = head;
		// If it does, set its previous to newNode and make it the new head no matter what
		if (head != nullptr)
		{
			head->prev = newNode;
		}
		head = newNode;
		return true;
	}

	// If the head is not null or the k is greater than current key, loop through doubly linked list to find correct position based on key
	Node* current = head;
	// Loop until go through all nodes or the current k is > k
	while (current->next != nullptr && current->next->key < k)
	{
		current = current->next;
	}

	// After finding correct position, check if the key is already in the linked list
	if (current->next != nullptr && current->next->key == k)
	{
		// Delete newNode and return false
		delete newNode;
		return false;
	}

	// If not, set the newNode into the doubly linked list
	newNode->next = current->next;
	// If current->next is not the last node, make its previous newNode
	if (current->next != nullptr)
	{
		current->next->prev = newNode;
	}
	// Set current->next to newNode and the newNode prev to current and return true
	current->next = newNode;
	newNode->prev = current;
	return true;
}




template<typename Key, typename Value>
bool SortedList<Key,Value>::contains(const Key &k) const noexcept
{
	// Initialize a Node pointer
	Node* current = head;
	// Loop through all the nodes to see if doubly linked list contains that key
	while (current != nullptr)
	{
		// Check if the current Node's key is == k
		if (current->key == k)
		{
			return true;
		}
		// Increment Node
		current = current->next;
	}
	// If not, return false
	return false;
}

template<typename Key, typename Value>
void SortedList<Key,Value>::remove(const Key &k) 
{
	// Initialize Node pointer
	Node* current = head;
	// Loop through the Nodes until one is found with that key
	while (current != nullptr && current->key != k)
	{
		current = current->next;
	}
	// If there is a key, continue. If not, silently end.
	if (current != nullptr)
	{
		// Set the Nodes prev Node to its prev Node value
		if (current->prev != nullptr)
		{
			current->prev->next = current->next;
		}
		// It's the first Node so make the second Node the first
		else
		{
			head = current->next;
		}
		// Set the Nodes next Node to its next Node value
		if (current->next != nullptr)
		{
			current->next->prev = current->prev;
		}
		// Delete the Node after adjustments to next and prev
		delete current;
	}
}



// If this key exists in the list, this function returns how many keys are in the list that are less than it.
// If this key does not exist in the list, this throws a KeyNotFoundException.
template<typename Key, typename Value>
unsigned SortedList<Key,Value>::getIndex(const Key &k) const
{
	// Set current Node to a Node pointer
	Node* current = head;
	// Loop through the nodes while current is not nullptr and the key is not found
	while(current != nullptr && current->key != k)
	{
		current = current->next;
	}
	// If current is not null, find the index
	if (current != nullptr)
	{
		unsigned index = 0;
		// Loop by counting down until null
		while (current->prev != nullptr)
		{
			current = current->prev;
			index ++;
		}
		return index;
	}
	// If the current is null, that means the key does not exist
	throw KeyNotFoundException{"Key not found in list"};

}

template<typename Key, typename Value>
Value & SortedList<Key,Value>::operator[] (const Key &k) 
{
	// Initialize Node pointer
	Node* current = head;
	// Loop through all the Nodes until the key is found
	while (current != nullptr && current->key !=k)
	{
		current = current->next;
	}
	// If key is found, return its value
	if (current != nullptr)
	{
		return current->value;
	}
	// If it is not, throw exception
	throw KeyNotFoundException{"Key not found in list"};
}

template<typename Key, typename Value>
const Value & SortedList<Key,Value>::operator[] (const Key &k) const 
{
	// Initialize Node pointer
	Node* current = head;
	// Loop through all the Nodes until the key is found
	while (current != nullptr && current->key !=k)
	{
		current = current->next;
	}
	// If key is found, return its value
	if (current != nullptr)
	{
		return current->value;
	}
	// If it is not, throw exception
	throw KeyNotFoundException{"Key not found in list"};
}

template<typename Key, typename Value>
const Key & SortedList<Key,Value>::largestLessThan(const Key & k) const
{
	// Initialize Node pointer and Key pointer
	Node* current = head;
	Key* largestLessThan_key = nullptr;
	// Loop through all the Nodes
	while (current != nullptr)
	{
		// Check if the current key is less than given key. If so, temporarily set it as the largestLessThan_key
		if (current->key < k)
		{
			// Since the keys are in order, this will automatically pick the highest key
			largestLessThan_key = &current->key;
		}
		// Increment Node
		current = current->next;
	}
	// Check if a key was found
	if (largestLessThan_key != nullptr)
	{
		return *largestLessThan_key;
	}
	// If not, throw exception
	throw KeyNotFoundException{"Key not found in list"};
}

template<typename Key, typename Value>
const Key & SortedList<Key,Value>::smallestGreaterThan(const Key & k) const
{
	// Initialize Node pointer
	Node* current = head;
	// Loop through all the Nodes
	while (current != nullptr)
	{
		// Check if the key is greater than given key
		if (current->key > k)
		{
			// Can simply return because the linked list is in ascending order
			return current->key;
		}
		// Increment Node
		current = current->next;
	}
	// If no Nodes are found, then return exception
	throw KeyNotFoundException{"Key not found in list"};
}



template <typename Key, typename Value>
bool SortedList<Key,Value>::operator==(const SortedList & l) const noexcept
{
	// Initialize Node pointers for SortedList and l
	Node* current = head;
	Node* currentl = l.head;
	// Loop through all Nodes in both SortedLists
	while (current != nullptr && currentl != nullptr)
	{
		// Check if the keys and values are the same. If not, return false
		if (current->key != currentl->key || current->value != currentl->value)
		{
			return false;
		}
		// Increment Nodes
		current = current->next;
		currentl = currentl->next;
	}
	// Ensures that both lists are the same length and have the same key/value pairs
	return current == nullptr && currentl == nullptr;
}

template <typename Key, typename Value>
void SortedList<Key,Value>::operator++()
{
	// Initialize a Node pointer
	Node* current = head;
	// Loop through every Node
	while (current != nullptr)
	{
		// Increment the value and go to next Node
		current->value++;
		current = current->next;
	}
}




#endif 

