

#ifndef MAP_H
#define MAP_H

#include "bst.h"
#include "pair.h"

// forward declaration
template <class K, class V>
class MapIterator;

template <class K, class V>
class Map
{
   public:
      // constructors, destructors, assignment
      Map() {}
      Map (const Map <K, V> & rhs) throw (const char *)
      {
         bst = rhs.bst;
      }
      
      ~Map()
      {
         bst.~BST();
      }
      
      Map <K, V> & operator = (const Map <K, V> & rhs)
      {
         bst = rhs.bst;
         return *this;
      }
      
      // std container interfaces
      bool empty()   { return bst.empty(); }
      int size()     { return bst.size();  }
      void clear()   { bst.clear();        }
      
      // map specific interfaces
      V & operator [] (const K & key);
      
      // iterators
      MapIterator<K, V> begin()  { return MapIterator<K, V>(bst.begin());   }
      MapIterator<K, V> end()    { return MapIterator<K, V>(bst.end());     }
      MapIterator<K, V> rbegin() { return MapIterator<K, V>(bst.rbegin());   }
      MapIterator<K, V> rend()   { return MapIterator<K, V>(bst.rend());     }      
      
   private:
      BST < Pair < K, V > > bst;
};

template <class K, class V>
V & Map<K, V> :: operator [](const K & key)
{
   Pair<K, V> pair(key, V());
   BSTIterator<Pair<K,V > > it = bst.find(pair);
   if (it != NULL)
      return it.getNode()->data.second;
   else
   {
      bst.insert(pair);
      it = bst.find(pair);
      return it.getNode()->data.second;
   }
}

template <class K, class V>
class MapIterator
{
   public:
      MapIterator(): it(NULL) {};
      MapIterator(BinaryNode <Pair < K,V > > * pNode)        { it = pNode;    }
      MapIterator(BSTIterator<  Pair < K, V > > rhs) : it(0) { it = rhs;      }
      MapIterator(const MapIterator <K,V> & rhs)             { it = rhs.it;   }

      // Copy Constructor
      MapIterator(MapIterator<K,V> & rhs)                    { *this = rhs;   }

      bool operator == (const MapIterator <K,V> & rhs) const
      {
         return *it == *rhs.it;
      }

      bool operator != (const MapIterator <K,V> & rhs) const
      {
         return it != rhs.it;
      }

      const MapIterator < K , V > & operator ++ ()
      {
         ++it;
         return *this;
      };

      const MapIterator < K , V > & operator -- ()
      {
         --it;
         return *this;
      };

      const V & operator * () const
      {
         return this->it.operator*().getSecond();
      }
      
   private:
      BSTIterator <Pair <K, V> > it;
};


#endif // MAP_H
