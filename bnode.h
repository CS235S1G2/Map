/***********************************************************************
* File: bnode.h
************************************************************************/

// you might want to put these methods into your BinaryNode class
// to help you debug your red-black balancing code
// JUSTIN- I added these functions below: findDepth()const & verifyRedBlack(int)const

#ifndef BINARY_NODE
#define BINARY_NODE

#include <iostream> 
/***********************************************
* BINARY NODE
* A node to be used in a binary tree
**********************************************/
template <class T>
class BinaryNode
{
public:
	// constructors
	BinaryNode() : pParent(NULL), pLeft(NULL), pRight(NULL)
	{
		data = T();
	}
	BinaryNode(const T & t) :
		data(t), pParent(NULL), pLeft(NULL), pRight(NULL) {}

	// methods
	void addLeft(BinaryNode <T> * pAdd);
	void addRight(BinaryNode <T> * pAdd);
	void addLeft(const T & t) throw (const char *);
	void addRight(const T & t) throw (const char *);

	int size();

	// members
	T data;
	BinaryNode <T> * pParent;
	BinaryNode <T> * pLeft;
	BinaryNode <T> * pRight;
};

// nonmember function prototypes
template <class T>
void deleteBinaryTree(BinaryNode <T> * & pNode);

template <class T>
std::ostream & operator << (std::ostream & out, const BinaryNode <T> * rhs);

/***********************************************
* BINARY NODE :: ADD LEFT (BNODE)
* Add a previously existing left node
**********************************************/
template <class T>
void BinaryNode <T> ::addLeft(BinaryNode <T> * pAdd)
{
	if (pAdd != NULL)
		pAdd->pParent = this;

	pLeft = pAdd;
}

/***********************************************
* BINARY NODE :: ADD RIGHT (BNODE)
* Add a previously existing right node
**********************************************/
template <class T>
void BinaryNode <T> ::addRight(BinaryNode <T> * pAdd)
{
	if (pAdd != NULL)
		pAdd->pParent = this;
	pRight = pAdd;
}

/***********************************************
* BINARY NODE :: ADD LEFT (T)
* Add a NEW node to the left with value t
**********************************************/
template <class T>
void BinaryNode <T> ::addLeft(const T & t) throw (const char *)
{
	try
	{
		BinaryNode <T> * pAdd = new BinaryNode <T>(t);
		pAdd->pParent = this;
		pLeft = pAdd;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a node";
	}
}

/***********************************************
* BINARY NODE :: ADD RIGHT (T)
* Add a NEW node to the right with value t
**********************************************/
template <class T>
void BinaryNode <T> ::addRight(const T & t) throw (const char *)
{
	try
	{
		BinaryNode <T> * pAdd = new BinaryNode <T>(t);
		pAdd->pParent = this;
		pRight = pAdd;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: unable to allocate a node";
	}
}

/***********************************************
* SIZE B TREE
* return the size of the tree under a given node
**********************************************/
template <class T>
int BinaryNode <T> ::size()
{
	if (this == NULL)
		return 0;
	else
		return pLeft->size() + 1 + pRight->size();
}

/***********************************************
* DELETE B TREE
* Delete binary tree
**********************************************/
template <class T>
void deleteBinaryTree(BinaryNode <T> * & pNode)
{
	if (pNode == NULL)
		return;
	deleteBinaryTree(pNode->pLeft);
	deleteBinaryTree(pNode->pRight);
	delete pNode;
}

/***********************************************
* OPERATOR <<
* Overload the insertion operator
**********************************************/
template <class T>
std::ostream & operator << (std::ostream & out, const BinaryNode <T> * rhs)
{
	if (rhs != NULL)
	{
		out << rhs->pLeft;
		out << rhs->data << " ";
		out << rhs->pRight;
	}

	return out;
}


/****************************************************
 * BINARY NODE :: FIND DEPTH
 * Find the depth of the black nodes. This is useful for
 * verifying that a given red-black tree is valid
 * Author: Br. Helfrich
 ****************************************************/
template <class T>
int BinaryNode <T> :: findDepth() const
{
   // if there are no children, the depth is ourselves
   if (pRight == NULL && pLeft == NULL)
      return (isRed ? 0 : 1);

   // if there is a right child, go that way
   if (pRight != NULL)
      return (isRed ? 0 : 1) + pRight->findDepth();
   else
      return (isRed ? 0 : 1) + pLeft->findDepth();
}

/****************************************************
 * BINARY NODE :: VERIFY RED BLACK
 * Do all four red-black rules work here?
 * Author: Br. Helfrich
 ***************************************************/
template <class T>
void BinaryNode <T> :: verifyRedBlack(int depth) const
{
   depth -= (isRed == false) ? 1 : 0;

   // Rule a) Every node is either red or black
   assert(isRed == true || isRed == false); // this feels silly

   // Rule b) The root is black
   if (pParent == NULL)
      assert(isRed == false);

   // Rule c) Red nodes have black children
   if (isRed == true)
   {
      if (pLeft != NULL)
         assert(pLeft->isRed == false);
      if (pRight != NULL)
         assert(pRight->isRed == false);
   }

   // Rule d) Every path from a leaf to the root has the same # of black nodes
   if (pLeft == NULL && pRight && NULL)
      assert(depth == 0);
   if (pLeft != NULL)
      pLeft->verifyRedBlack(depth);
   if (pRight != NULL)
      pRight->verifyRedBlack(depth);
}

/******************************************************
 * VERIFY B TREE
 * Verify that the tree is correctly formed
 * Author: Br. Helfrich
 ******************************************************/
template <class T>
void BinaryNode <T> :: verifyBTree() const
{
   // check parent
   if (pParent)
      assert(pParent->pLeft == this || pParent->pRight == this);

   // check left
   if (pLeft)
   {
      assert(pLeft->data <= data);
      assert(pLeft->pParent == this);
      pLeft->verifyBTree();
   }

   // check right
   if (pRight)
   {
      assert(pRight->data >= data);
      assert(pRight->pParent == this);
      pRight->verifyBTree();
   }
}
#endif // BINARY_NODE
