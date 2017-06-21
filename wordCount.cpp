/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

//#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype
using namespace std;



/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
	map <string, double> counts;
	string input;
	string filename;
	Pair <string, string> userInput;
	userInput = promptUser();
	input = userInput.getFirst();
	filename = userInput.getSecond();
	while (input != "!")
	{
		readFile(counts, filename, input);
		display(input, counts);
	}

}

Pair<string, string> promptUser()
{
	Pair<string, string> userInput;
	string filename;
	string input;
	char a;
	cout << "What is the filename to be counted? ";
	getline(cin, filename);
	cout << "What word whose frequency is to be found. Type  ! when done\n";
	return userInput;
}

void readFile(map<string, double>& counts, const string & fileName, const string & search)
{
	double wordCount = 0;
	string input;
	ifstream fin(fileName); //TODO flag fileName
	if (fin.fail())
		cerr << "Unable to open file\n";
	else
		while (fin >> input)
		{
			if (input == search)
			{
				wordCount++;
			}
		}
	fin.close();
	//counts.insert(search, wordCount);
	counts[search] = wordCount;
}

void display(string input, map<string, double>& counts)
{
	cout << "\t" << input << " : " << counts[input] << "\n";
}

/*
Algorithm:
promptUser() - "What is the filename to be counted?" "What word whose frequency is to be found. Type  ! when done"
readFile() - to read the text one word at a time
	- if (string == string)
		- double++
		- insert word && #acurances into MAP
display()
	- iterate through Map
	- display Word and #accurances



*/