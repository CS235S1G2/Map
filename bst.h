/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother JonesL, CS 235
 * Author:
 *    Nathan Bench, Jed Billman, Jeremy Chandler, Justin Chandler
 * Summary:
 *    Binary Search Tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"   // for BinaryNode
#include "stack.h"   // for Stack

// forward declaration for BST iterators
template <class T>
class BSTIterator;

/***********************************************
 * BINARY SEARCH TREE
 * A binary tree that follows the rule pLeft < root < pRight
 **********************************************/
template <class T>
class BST
{
   public:
      // constructors & destructor
      BST(): root(NULL) {}
      BST(const BST <T> & rhs) throw (const char *);
      ~BST()
      {
         clear();
      }
      BST <T> & operator = (const BST <T> & rhs) throw (const char *);
      
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
      void remove(BSTIterator <T> & it);
      BSTIterator <T> find(const T & t);
      
      BinaryNode <T> * getRoot() 
      { 
         return root; 
      }
      
      // iterators
      BSTIterator <T> begin();
      BSTIterator <T> end()  { return BSTIterator <T> (NULL); }
      BSTIterator <T> rbegin();
      BSTIterator <T> rend() { return BSTIterator <T> (NULL); }
      
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
         catch(std::bad_alloc)
         {
            throw "ERROR: Unable to allocate a node";
         }
      }
      
      void deleteNode(BinaryNode <T> * & pDelete, bool toRight);
};

/***********************************************
 * BST :: COPY CONSTRUCTOR
 * Copy rhs to current tree
 **********************************************/
template <class T> 
BST <T> :: BST(const BST <T> & rhs) throw (const char *)
{
   copyBinaryTree(root, rhs.root);
}

/***********************************************
 * BST :: OPERATOR =
 * Assign rhs to current tree
 **********************************************/
template <class T>
 BST <T> & BST <T> :: operator = (const BST <T> & rhs) throw (const char *)
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
 * BST :: INSERT
 * Insert a value into the tree
 **********************************************/
template <class T>
void BST <T> :: insert(const T & t) throw (const char *)
{
   // empty tree
   if (empty())
   {
      try
      {
         root = new BinaryNode <T>(t);
         root->balance();
         return;
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a node";
      }
   }
   
   BinaryNode <T> * pPrev;
   BinaryNode <T> * pCurrent = root;
   while (pCurrent != NULL)
   {
      // save your spot
      pPrev = pCurrent;
      if (t > pCurrent->data)
         pCurrent = pCurrent->pRight;
      else
         pCurrent = pCurrent->pLeft;
   }
   try
   {
      pCurrent = new BinaryNode <T>(t);
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate node";
   }
         pCurrent->pParent = pPrev;
      if (pCurrent->data > pPrev->data)
      {
         pPrev->pRight = pCurrent;
         pCurrent->balance();
      }
      else
      {
         pPrev->pLeft = pCurrent;
         pCurrent->balance();
      }

}

/*************************************************
* BST :: REMOVE
* Remove a given node as specified by the iterator
* CITE: Brother Jones
************************************************/
template <class T>
void BST <T> :: remove(BSTIterator <T> & it)
{
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

/****************************************************
* DELETE NODE
* Delete a single node (pDelete) from the tree indicated
* by a node (pDelete).
* pDelete the node to be deleted
* toRight should the right branch inherit our place?
* CITE: Brother Jones
****************************************************/
template <class T>
void BST <T> :: deleteNode(BinaryNode <T> * & pDelete, bool toRight)
{
   // shift everything up
   BinaryNode <T> * pNext = (toRight ? pDelete->pRight : pDelete->pLeft);

   // if we are not the parent, hook ourselves into the existing tree
   if (pDelete != root)
   {
      if (pDelete->pParent->pLeft == pDelete)
      {
         pDelete->pParent->pLeft = NULL;
         pDelete->pParent->addLeft(pNext);
      }
      else
      {
         pDelete->pParent->pRight = NULL;
         pDelete->pParent->addRight(pNext);
      }
   }
   // otherwise, the pNext is the new root
   else
   {
      root = pNext;
      pNext->pParent = NULL;
   }
}

/***********************************************
 * BST :: FIND
 * Return an iterator to a value in the tree
 **********************************************/
template <class T>
BSTIterator <T> BST <T> :: find(const T & t)
{
   BinaryNode <T> * pCurrent = root;
   while(pCurrent != NULL)
   {
      if (t == pCurrent->data)
         return BSTIterator <T>(pCurrent);
      else if (t > pCurrent->data)
      {
         pCurrent = pCurrent->pRight;
      }
      else
      {
         pCurrent = pCurrent->pLeft;
      }
   }
   return end();
}

/***********************************************
 * BST :: BEGIN
 * Return an iterator to the start of the tree
 **********************************************/
template <class T>
BSTIterator <T> BST <T> :: begin()
{
   Stack < BinaryNode <T> * > nodes;
   
   // add a NULL
   nodes.push(NULL);
   // start the tree
   nodes.push(root);
   // find the left-most leaf
   while(nodes.top() != NULL && nodes.top()->pLeft)
      nodes.push(nodes.top()->pLeft);
   
   return nodes; 
}

/***********************************************
 * BST :: RBEGIN
 * return the right-most leaf
 **********************************************/
template <class T>
BSTIterator <T> BST <T> :: rbegin()
{
   Stack < BinaryNode <T> * > nodes;
   
   // add a NULL
   nodes.push(NULL);
   // start the tree
   nodes.push(root);
   // find the left-most leaf
   while(nodes.top() != NULL && nodes.top()->pRight)
      nodes.push(nodes.top()->pRight);
   
   return nodes; 
}


/***********************************************
 * BST ITERATOR
 * A class to iterate through the BST
 **********************************************/
template <class T>
class BSTIterator
{
   public:
      BSTIterator() {}
      BSTIterator(BinaryNode <T> * pNode);
      BSTIterator(Stack <BinaryNode <T> *> nodes);
      
      BSTIterator <T> & operator = (const Stack <BinaryNode <T> *> rhs)
      {
         nodes = rhs.nodes;
         return *this;
      }
      
      bool operator == (const BSTIterator <T> & rhs) const;
      
      bool operator != (const BSTIterator <T> & rhs) const;
      
      // return const by reference to keep tree valid
      const T & operator * () const
      {
         if (!nodes.empty() && nodes.top() != NULL)
            return nodes.top()->data;
      }
      
      BSTIterator <T> & operator -- ();
      BSTIterator <T> & operator -- (int postfix)
      {
         BSTIterator <T> temp = *this;
         --(*this);
         return temp;
      }
      BSTIterator <T> & operator ++ ();
      BSTIterator <T>   operator ++ (int postfix)
      {
         BSTIterator <T> temp = *this;
         ++(*this);
         return temp;
      }
      
      BinaryNode <T> * getNode() { return nodes.top(); }
      
   private:
      Stack <BinaryNode <T> *> nodes;
};
 
template <class T>
BSTIterator <T> :: BSTIterator(BinaryNode <T> * pNode)
{
   nodes.push(pNode);
}

template <class T>
BSTIterator <T> :: BSTIterator(Stack <BinaryNode <T> *> rhs)
{
   nodes = rhs;
}


template <class T>
bool BSTIterator <T> :: operator == (const BSTIterator <T> & rhs) const
{
   return nodes.top() == rhs.nodes.top();
}

template <class T>
bool BSTIterator <T> :: operator != (const BSTIterator <T> & rhs) const
{
   return nodes.top() != rhs.nodes.top();
}

/***********************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * advance the iterator
 **********************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a right node, take it
   if (nodes.top()->pRight != NULL)
   {
      nodes.push(nodes.top()->pRight);

      // there might be more left-most children
      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);
      return *this;
   }

   // there are no right children, the left are done
   assert(nodes.top()->pRight == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the left-child, got to the parent.
   if (pSave == nodes.top()->pLeft)
      return *this;

   // we are the right-child, go up as long as we are the right child!
   while (nodes.top() != NULL && pSave == nodes.top()->pRight)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}
      
/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one. Note that this implementation uses
 *     a stack of nodes to remember where we are. This stack
 *     is called "nodes".
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
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

#endif // BST_H

