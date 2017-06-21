/***********************************************************************
* Header:
*    WORD COUNT
* Summary:
*    This will contain just the prototype for the wordCount()
*    function
* Author
*    Nathan Bench, Jed Billman, Jeremy Chandler, Justin Chandler
************************************************************************/

#ifndef WORD_COUNT_H
#define WORD_COUNT_H
#include <fstream>
#include <iostream>
#include "map.h"
#include <string>
#include "pair.h"
using namespace std;

// forward declaration
class Count;

/*****************************************************
* WORD COUNT
* Prompt the user for a file to read, then prompt the
* user for words to get the count from
*****************************************************/
void wordCount();
string promptUser();
void readFile(Map <string, Count> & counts, string fileName);
void display(string input, Map<string, Count>& counts);

class Count
{
   public:
      Count(): num(0) {}
      
      Count & operator += (const int & rhs)
      {
         num += rhs;
         return *this;
      }
      
      friend std::ostream & operator << (std::ostream & out, const Count & rhs);
      
      
   private:
      int num;
};
#endif // WORD_COUNT_H

