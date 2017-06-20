/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (RedBlackTreeNode)
 *    Brother Jones, CS 235
 * Author:
 *    Nathan Bench, Jed Billman, Jeremy Chandler, Justin Chandler
 * Summary:
 *    Binary Search Tree
 ************************************************************************/

#ifndef RedBlackTreeNode_H
#define RedBlackTreeNode_H

#include "bnode.h"   // for BinaryNode
#include "stack.h"   // for Stack

// forward declaration for RedBlackTreeNode iterators
template <class T>
class RedBlackTreeNodeIterator;

/***********************************************
 * BINARY SEARCH TREE
 * A binary tree that follows the rule pLeft < root < pRight
 **********************************************/
template <class T>
class RedBlackTreeNode
{
   public:
      // constructors & destructor
      RedBlackTreeNode(): root(NULL) {}
      RedBlackTreeNode(const RedBlackTreeNode <T> & rhs) throw (const char *);
      ~RedBlackTreeNode()
      {
         clear();
      }
      RedBlackTreeNode <T> & operator = (const RedBlackTreeNode <T> & rhs) throw (const char *);
      
      // make a friend -- cannot use the same template class as the class definition
      template <class Y>
      friend void deleteBinaryTree(BinaryNode <Y> * &pNode);
      
      // container interfaces
      bool empty()   { return root == NULL;    }
      int size()     { return empty() ? 0 : root->size();     }
      void clear()   
      { 
         if (root)
         {
            deleteBinaryTree(root); 
            root = NULL;
         }
      }
      
      // Binary Search Tree interfaces
      void insert(const T & t) throw (const char *);
      void remove(RedBlackTreeNodeIterator <T> & it);
      RedBlackTreeNodeIterator <T> find(const T & t);
      
      // iterators
      RedBlackTreeNodeIterator <T> begin();
      RedBlackTreeNodeIterator <T> end()  { return RedBlackTreeNodeIterator <T> (NULL); }
      RedBlackTreeNodeIterator <T> rbegin();
      RedBlackTreeNodeIterator <T> rend() { return RedBlackTreeNodeIterator <T> (NULL); }
      
   private:
      BinaryNode <T> * root; 
      
      // private methods
      void copyBinaryTree(BinaryNode <T> * & pNode, const BinaryNode <T> * rhs)
      {
         if (rhs == NULL)
         {
            pNode = NULL;
            return;
         }
         try
         {
            pNode = new BinaryNode <T>;
            pNode->data = rhs->data;
            copyBinaryTree(pNode->pLeft, rhs->pLeft);
            copyBinaryTree(pNode->pRight, rhs->pRight);
		 }
		 catch (std::bad_alloc)
		 {
			 throw "ERROR: Unable to allocate a node";
		 }
	  }
};

/***********************************************
 * RedBlackTreeNode :: COPY CONSTRUCTOR
 * Copy rhs to current tree
 **********************************************/
template <class T>
RedBlackTreeNode <T> ::RedBlackTreeNode(const RedBlackTreeNode <T> & rhs) throw (const char *)
{
	copyBinaryTree(root, rhs.root);
}

/***********************************************
 * RedBlackTreeNode :: OPERATOR =
 * Assign rhs to current tree
 **********************************************/
template <class T>
RedBlackTreeNode <T> & RedBlackTreeNode <T> :: operator = (const RedBlackTreeNode <T> & rhs) throw (const char *)
{
	// check for !empty tree
	if (!empty())
		clear();
	// IF rhs NULL
	if (rhs.root == NULL)
		root = NULL;
	// copy the tree
	copyBinaryTree(root, rhs.root);

	return *this;
}

/***********************************************
 * RedBlackTreeNode :: INSERT
 * Insert a value into the tree
 **********************************************/
template <class T>
void RedBlackTreeNode <T> ::insert(const T & t) throw (const char *)
{
	// empty tree
	if (empty())
	{
		try
		{
			root = new BinaryNode <T>(t);
			return;
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a node";
		}
	}

	BinaryNode <T> * pParent;
	BinaryNode <T> * pGrandparent;
	BinaryNode <T> * pGreatGrandparent;
	BinaryNode <T> * pAunt;
	BinaryNode <T> * pSibling;
	BinaryNode <T> * pCurrent = root;
	while (pCurrent != NULL)
	{
		// save your spot
		pGreatGrandparent = pGrandparent;
		pGrandparent = pParent;
		pParent = pCurrent;
		if (pGrandparent->pLeft == pParent)
			pAunt = pGrandparent->pRight;
		if (pGrandparent->pRight == pParent)
			pAunt = pGrandparent->pLeft;
		if (t > pCurrent->data)
		{
			pSibling = pCurrent->pLeft;
			pCurrent = pCurrent->pRight;
		}
		else
		{
			pSibling = pCurrent->pRight;
			pCurrent = pCurrent->pLeft;
		}
	}
	try
	{
		pCurrent = new BinaryNode <T>(t);
		pCurrent->pParent = pParent;
		if (pCurrent->data > pParent->data)
			pParent->pRight = pCurrent;
		else
			pParent->pLeft = pCurrent;

		// Case 1 No Parent
		if (pCurrent == root)
		{
			pCurrent->setBlack();
		}
		//Case 2 is taken care of because the constructor automatically
		//makes the new node red.

		//Case 3 If the new node's parent is red, grandparent is black, 
		   // and aunt is red, then we re-color the
		   // three.The grandparent becomes red, the parent 
		   // becomes black, and the aunt becomes black.Note that
		   // we may need to do more work if the great - grandparent is red.		if (pParent->isRed() && pGrandparent->isBlack() && pAunt->isRed())		{			pGrandparent->setRed();			pParent->setBlack();			pAunt->setBlack();			if (pGreatGrandparent->isRed())				; // TODO: Something. I'm not sure.		}		// Case 4		if (pParent->isRed() && pGrandparent->isBlack()			&& pAunt->isBlack())		{			// Subcase 4.a.			if (pCurrent == pParent->pLeft && pParent == pGrandparent->pLeft)			{				pParent->setBlack();				pParent = pGrandparent;				pParent->pLeft = pCurrent;				pParent->pRight = pGrandparent;				pGrandparent->setRed();				pGrandparent->pLeft = pSibling;				pGrandparent->pRight = pAunt;			}			// Subcase 4.b.			else if (pCurrent == pParent->pRight && pParent == pGrandparent->pLeft)			{				pParent = pGrandparent;				pGrandparent = pParent;				// Distribute children of pCurrent				if (pAunt == pGrandparent->pLeft)					pGrandparent->pRight = pCurrent->pRight;				if (pAunt == pGrandparent->pRight)					pGrandparent->pLeft = pCurrent->pRight;				if (pSibling == pParent->pLeft)					pParent->pRight = pCurrent->pLeft;				if (pSibling == pParent->pRight)					pParent->pLeft = pCurrent->pLeft;			}			// Subcase 4.c.			else if (pCurrent == pParent->pRight && pParent == pGrandparent->pRight)			{				pParent->setBlack();				pParent = pGrandparent;				pParent->pRight = pCurrent;				pParent->pLeft = pGrandparent;				pGrandparent->setRed();				pGrandparent->pRight = pSibling;				pGrandparent->pLeft = pAunt;			}			// Subcase 4.d.			else if (pCurrent == pParent->pLeft && pParent == pGrandparent->pRight)			{				if (pSibling->isBlack() //All the rest of the conditionals are part of first if statement					&& pParent->pLeft == pCurrent && pGrandparent->pRight == pParent)				{					pGrandparent->pRight = pCurrent->pLeft;					pParent->pLeft = pCurrent->pRight;					if (pGreatGrandparent == NULL)						pCurrent->pParent = NULL;					else if (pGreatGrandparent->pRight == pGrandparent)						pGreatGrandparent->pRight = pCurrent;					else						pGreatGrandparent->pLeft = pCurrent;					pCurrent->pLeft = pGrandparent;					pCurrent->pRight = pParent;					pGrandparent->setRed();					pCurrent->setBlack();				}			}		}
	  }
	  catch (std::bad_alloc)
	  {
		  throw "ERROR: Unable to allocate node";
	  }
      // Set everything right
	  pCurrent->pParent->pParent->pParent = pGreatGrandparent;
	  pCurrent->pParent->pParent = pGrandparent;
	  pCurrent->pParent = pParent;
	  if (pSibling == pCurrent->pParent->pLeft)		  pCurrent->pParent->pLeft = pSibling;	  if (pSibling == pCurrent->pParent->pRight)		  pCurrent->pParent->pRight = pSibling;
	  if (pAunt == pCurrent->pParent->pParent->pRight)		  pCurrent->pParent->pParent->pRight = pAunt;
	  if (pAunt == pCurrent->pParent->pParent->pLeft)		  pCurrent->pParent->pParent->pLeft = pAunt;

	  if (pCurrent->data > pParent->data)
		  pParent->pRight = pCurrent;
	  else
		  pParent->pLeft = pCurrent;
}

/***********************************************
 * RedBlackTreeNode :: REMOVE
 * Remove a value from the tree
 **********************************************/
template <class T>
void RedBlackTreeNode <T> :: remove(RedBlackTreeNodeIterator <T> & it)
{
	//TODO: Proper remove
	// find the node
	BinaryNode <T> * pNode = it.getNode();
	// do nothing if there is nothing to do
	if (pNode == NULL)
		return;

	// if there is only one child (right) or no children (how sad!)
	if (pNode->pLeft == NULL)
		deleteNode(pNode, true /* goRight */);

	// if there is only one child (left)
	else if (pNode->pRight == NULL)
		deleteNode(pNode, false /* goRight */);

	// otherwise, swap places with the in-order successor
	else
	{
		// find the in-order successor
		BinaryNode <T> * pNodeIOS = pNode->pRight;

		while (pNodeIOS->pLeft != NULL)
			pNodeIOS = pNodeIOS->pLeft;

		// copy its data
		pNode->data = pNodeIOS->data;

		// if there are any children under the in-order successor, fix them
		assert(pNodeIOS->pLeft == NULL); // there cannot be a left child or

										 // I would not be the IOS
		deleteNode(pNodeIOS, true /*goRight*/);

		// prepare for deletion
		pNode = pNodeIOS;
	}

	delete pNode;
   
}

/***********************************************
 * RedBlackTreeNode :: FIND
 * Return an iterator to a value in the tree
 **********************************************/
template <class T>
RedBlackTreeNodeIterator <T> RedBlackTreeNode <T> :: find(const T & t)
{
   return RedBlackTreeNodeIterator <T> (NULL);
}

/***********************************************
 * RedBlackTreeNode :: BEGIN
 * Return an iterator to the start of the tree
 **********************************************/
template <class T>
RedBlackTreeNodeIterator <T> RedBlackTreeNode <T> :: begin()
{
   return RedBlackTreeNodeIterator <T> (NULL); 
}

/***********************************************
 * RedBlackTreeNode :: RBEGIN
 * return a reverse iterator
 **********************************************/
template <class T>
RedBlackTreeNodeIterator <T> RedBlackTreeNode <T> :: rbegin()
{
   return RedBlackTreeNodeIterator <T> (NULL);
}


/***********************************************
 * RedBlackTreeNode ITERATOR
 * A class to iterate through the RedBlackTreeNode
 **********************************************/
template <class T>
class RedBlackTreeNodeIterator
{
   public:
      RedBlackTreeNodeIterator(BinaryNode <T> * pNode);
      RedBlackTreeNodeIterator(Stack <BinaryNode <T> *> nodes);
      
      RedBlackTreeNodeIterator <T> & operator = (const Stack <BinaryNode <T> *> rhs);
      
      bool operator == (const RedBlackTreeNodeIterator <T> & rhs) const;
      
      bool operator != (const RedBlackTreeNodeIterator <T> & rhs) const;
      
      // return const by reference to keep tree valid
      const T & operator * ()
      {
         return nodes.top();
      }
      
      RedBlackTreeNodeIterator <T> & operator -- ();
      RedBlackTreeNodeIterator <T> & operator ++ ();
      RedBlackTreeNodeIterator <T>   operator ++ (int postfix);
      
   private:
      Stack <BinaryNode <T> *> nodes;
};
 
template <class T>
RedBlackTreeNodeIterator <T> :: RedBlackTreeNodeIterator(BinaryNode <T> * pNode)
{
   
}

template <class T>
RedBlackTreeNodeIterator <T> :: RedBlackTreeNodeIterator(Stack <BinaryNode <T> *> nodes)
{
   
}

template <class T>
RedBlackTreeNodeIterator <T> & RedBlackTreeNodeIterator <T> :: operator = (const Stack <BinaryNode <T> *> rhs)
{
   
}

template <class T>
bool RedBlackTreeNodeIterator <T> :: operator == (const RedBlackTreeNodeIterator <T> & rhs) const
{
   
}

template <class T>
bool RedBlackTreeNodeIterator <T> :: operator != (const RedBlackTreeNodeIterator <T> & rhs) const
{
   
}

template <class T>
RedBlackTreeNodeIterator <T> & RedBlackTreeNodeIterator <T> :: operator ++ ()
{
   
}

template <class T>
RedBlackTreeNodeIterator <T> RedBlackTreeNodeIterator <T> :: operator ++ (int postfix)
{
   
}
      
/**************************************************
 * RedBlackTreeNode ITERATOR :: DECREMENT PREFIX
 *     advance by one. Note that this implementation uses
 *     a stack of nodes to remember where we are. This stack
 *     is called "nodes".
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
RedBlackTreeNodeIterator <T> & RedBlackTreeNodeIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}

#endif // RedBlackTreeNode_H

