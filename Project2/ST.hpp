/*
Name: Evan Poirier
Email: espoirier@crimson.ua.edu
Course Section: Fall 2024 CS 201
Homework #2
*/

#ifndef _ST_HPP_
#define _ST_HPP_

#include <utility>

#include "RBT.hpp"
#include "RBTPrint.hpp"

template <class Key, class Type>
class ST : public RedBlackTree<Key, Type> {
public:
	typedef RBTNode<Key, Type>* iterator;

	// Constructors
	// constant
	ST() {
		this->root = nullptr;
		this->nodeCount = 0;
	}; 

	// Destructor
	// linear in the size of the ST
	~ST(){
		this->clear();
	};

	// access or insert specifies element
	// inserts if the key is not present and returns a reference to
	// the value corresponding to that key
	// O(LogN), N size of ST
	Type& operator[](const Key& key) {
		iterator temp = this->Search(key);

		if (temp != nullptr) {
			return temp->value;
		} else {
			Type defaultVal = Type();
			this->insert(key, defaultVal);
			return this->Search(key)->value;
		}
	}; 

	// insert a (key, value) pair, if the key already exists
	// set the new value to the existing key
	// O(LogN), N size of ST
	void insert(const Key& key, const Type& value) {
		iterator temp = this->Search(key);
		if (temp != nullptr) {
			temp->value = value;
		} else {
			this->Insert(key, value);
			this->nodeCount ++;
		}
	};

	// remove element at the given position
	// amortized constant
	void remove(iterator position) {
		this->RemoveNode(position);
		(this->nodeCount) --;
	};

    // remove element with keyvalue key and 
	// return number of elements removed (either 0 or 1)
	// O(logN), N size of ST
	std::size_t remove(const Key& key) {
		iterator temp = this->Search(key);
		if (temp != nullptr) {
			this->RemoveNode(temp);
			(this->nodeCount) --;
			return 1;
		} else {
			return 0;
		}
	};  

	// removes all elements from the ST, after this size() returns 0
	// linear in the size of the ST
	void clear() {
		this->DeleteTree(this->root);
		this->root = nullptr;
		this->nodeCount = 0;
	}; 

	// checks if ST has no elements; true is empty, false otherwise
	// constant
	bool empty() const {
		return this->nodeCount == 0;
	}; 

	// returns number of elements in ST
	// constant
	std::size_t size() const {	
		return this->nodeCount;
	}; 

	// returns number of elements that match keyvalue key
	// value returned is 0 or 1 since keys are unique
	// O(LogN), N size of ST
	std::size_t count(const Key& key) {
		if (this->Search(key) == nullptr) {
			return 0;
		} else {
			return 1;
		}
	}; 

	// find an element with keyvalue key and return 
	// the iterator to the element found, nullptr if not found
	// O(LogN), N size of ST
	iterator find(const Key& key) {
		return this->Search(key);
	};

	// check if key exists in ST
	// O(LogN), N size of ST
	bool contains(const Key& key) {
		if (this->Search(key) == nullptr) {
			return false;
		} else {
			return true;
		}
	};

	// return contents of ST as a vector of (key,value) pairs
	// O(N), N size of ST
	std::vector<std::pair<Key, Type>> toVector() {
		std::vector<std::pair<Key, Type>> returnVector;

		// helper function that performs an in-order traversal, appending key-value pairs to vector passed by reference recursively.
		populateVectorInOrder(this->GetRoot(), returnVector);

		return returnVector;
	};

	// print the symbol table as Red-Black Tree
	// O(N), N size of ST
	void displayTree() {
		std::cout << RBTPrint<Key,Type>::TreeToString(RedBlackTree<Key,Type>::root) << std::endl;
	};

	// print the symbol table in sorted order
	// O(N), N size of ST
	void display() {
		std::vector<std::pair<Key,Type>> stVector;
		stVector = this->toVector();
		for (const auto & i : stVector) {
	    	std::cout << i.first << ": " << i.second << std::endl;
		}
	};

private:
	std::size_t nodeCount;

	void populateVectorInOrder(iterator startingNode, std::vector<std::pair<Key,Type>> &vectorToPopulate) {
		if (startingNode != nullptr) {
			populateVectorInOrder(startingNode->left, vectorToPopulate);
			vectorToPopulate.push_back(std::pair<Key,Type>(startingNode->key, startingNode->value));
			populateVectorInOrder(startingNode->right, vectorToPopulate);
		}
	}
};

#endif

