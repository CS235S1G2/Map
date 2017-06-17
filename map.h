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
	Map() : BST() {}
	// copy constructor

	// destructor
	~Map() {}
	// methods
	// empty()
	// size()
	// clear()
	// find()
	// begin
	// end()
	// operator=
	// operator[]
	// members
	// BST made from pair type
    BST <Pair<K,V>> bst;

};

// nonmember function prototypes


#endif // MAP
