/***********************************************************************
* File: map.h
************************************************************************/

#ifndef MAP
#define MAP

#include <iostream> 
#include "pair.h"
#include "bst.h"
/***********************************************
* MAP
* 
**********************************************/
template <class K>
template <class V>
template <class T>
class Map
{
public:
	// constructors
	Map() : {bst = new BST<Pair<K,V>>;}
	// copy constructor

	// destructor
	~Map() {bst->clear();}
	// methods
	bool empty() { return bst->empty(); }
	int size() { return bst->empty() ? 0 : bst->root->size();}
	void clear() { bst->clear(); }
	RedBlackTreeNodeIterator <T> find(const T & t) {return bst->find(t);}
	RedBlackTreeNodeIterator <T> begin() { return bst->begin();}
	RedBlackTreeNodeIterator <T> end() { return bst->end();}
	// operator=
	// operator[]
	
	// members
	// BST made from pair type
    BST <Pair<K,V>> * bst;

};

// nonmember function prototypes


#endif // MAP
