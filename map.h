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
template <class K, class V>
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
	RedBlackTreeNodeIterator <Pair<K,V>> find(const Pair<K,V> & t) {return bst->find(t);}
	RedBlackTreeNodeIterator <Pair<K,V>> begin() { return bst->begin();}
	RedBlackTreeNodeIterator <Pair<K,V>> end() { return bst->end();}
	// operator=
	// operator[]
	
	// members
	// BST made from pair type
private:
    RedBlackTreeNode <Pair<K,V>> * bst;

};

// nonmember function prototypes


#endif // MAP
