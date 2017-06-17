/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Jones, CS 235
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
         return;
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a node";
      }
   }
   else
   {
      BinaryNode <T> * pNode = NULL;
      try
      {
         pNode = new BinaryNode <T>(t);
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a node";
      }
      BinaryNode <T> * pCurrent = root; 
	  assert(pNode!=NULL);
	  assert(pNode->data != NULL);
	  assert(pCurrent != NULL);
      // WHILE place not found
      bool isFound = false;
      while (!isFound)
      {
         // compare & traverse
         if (pNode->data > pCurrent->data)
         {
            if (pCurrent->pRight == NULL)
            {
               pCurrent->addRight(pNode);
               isFound = true;
            }
         }
         else
         {
            if (pCurrent->pLeft == NULL)
            {
               pCurrent->addLeft(pNode);
               isFound = true;
            }
         }
      }
   }
}

/***********************************************
 * BST :: REMOVE
 * Remove a value from the tree
 **********************************************/
template <class T>
void BST <T> :: remove(BSTIterator <T> & it)
{
   
}

/***********************************************
 * BST :: FIND
 * Return an iterator to a value in the tree
 **********************************************/
template <class T>
BSTIterator <T> BST <T> :: find(const T & t)
{
   return BSTIterator <T> (NULL);
}

/***********************************************
 * BST :: BEGIN
 * Return an iterator to the start of the tree
 **********************************************/
template <class T>
BSTIterator <T> BST <T> :: begin()
{
   return BSTIterator <T> (NULL); 
}

/***********************************************
 * BST :: RBEGIN
 * return a reverse iterator
 **********************************************/
template <class T>
BSTIterator <T> BST <T> :: rbegin()
{
   return BSTIterator <T> (NULL);
}


/***********************************************
 * BST ITERATOR
 * A class to iterate through the BST
 **********************************************/
template <class T>
class BSTIterator
{
   public:
      BSTIterator(BinaryNode <T> * pNode);
      BSTIterator(Stack <BinaryNode <T> *> nodes);
      
      BSTIterator <T> & operator = (const Stack <BinaryNode <T> *> rhs);
      
      bool operator == (const BSTIterator <T> & rhs) const;
      
      bool operator != (const BSTIterator <T> & rhs) const;
      
      // return const by reference to keep tree valid
      const T & operator * ()
      {
         return nodes.top();
      }
      
      BSTIterator <T> & operator -- ();
      BSTIterator <T> & operator ++ ();
      BSTIterator <T>   operator ++ (int postfix);
      
   private:
      Stack <BinaryNode <T> *> nodes;
};
 
template <class T>
BSTIterator <T> :: BSTIterator(BinaryNode <T> * pNode)
{
   
}

template <class T>
BSTIterator <T> :: BSTIterator(Stack <BinaryNode <T> *> nodes)
{
   
}

template <class T>
BSTIterator <T> & BSTIterator <T> :: operator = (const Stack <BinaryNode <T> *> rhs)
{
   
}

template <class T>
bool BSTIterator <T> :: operator == (const BSTIterator <T> & rhs) const
{
   
}

template <class T>
bool BSTIterator <T> :: operator != (const BSTIterator <T> & rhs) const
{
   
}

template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
   
}

template <class T>
BSTIterator <T> BSTIterator <T> :: operator ++ (int postfix)
{
   
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

