/***********************************************************************
* Module:
*    Week 10, WORD COUNT
*    Brother Helfrich, CS 235
* Author:
*    Nathan Bench, Jed Billman, Jeremy Chandler, Justin Chandler
* Summary:
*    This program will implement the wordCount() function
************************************************************************/

#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype

/*****************************************************
* WORD COUNT
* Prompt the user for a file to read, then prompt the
* user for words to get the count from
*****************************************************/
void wordCount()
{
	Map <string, Count> counts;
	string input;
	string filename;
	filename = promptUser();
   
   readFile(counts, filename);
	while (input != "!")
	{
		cout << "> ";
		getline(cin, input);
		if (input == "!")
			return;
		
		display(input, counts);
	}

}

string promptUser()
{
	string filename;
	cout << "What is the filename to be counted? ";
	cin.ignore();
	getline(cin, filename);
	cout << "What word whose frequency is to be found. Type ! when done\n";
	return filename;
}

void readFile(Map<string, Count>& counts, string fileName)
{
	string input;
	ifstream fin(fileName.c_str());
	if (fin.fail())
		cerr << "Unable to open file\n";
	else
		while (fin >> input)
		{
         counts[input];
         counts[input] += 1;
		}
	fin.close();
}

void display(string input, Map<string, Count>& counts)
{
	cout << "\t" << input << " : " << counts[input] << "\n";
}

std::ostream & operator << (std::ostream & out, const Count & rhs)
{
   out << rhs.num;
   return out;
}

