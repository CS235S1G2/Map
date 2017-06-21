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
	filename = promptUser();
	while (input != "!")
	{
		cout << "> ";
		getline(cin, input);
		if (input == "!")
			return;
		readFile(counts, filename, input);
		display(input, counts);
	}

}

string promptUser()
{
	string filename;
	cout << "What is the filename to be counted? ";
	cin.ignore();
	getline(cin, filename);
	cout << "What word whose frequency is to be found. Type  ! when done\n";
	return filename;
}

void readFile(map<string, double>& counts, string fileName, const string & search)
{
	double wordCount = 0;
	string input;
	ifstream fin(fileName.c_str());
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
	counts[search] = wordCount;
}

void display(string input, map<string, double>& counts)
{
	cout << "\t" << input << " : " << counts[input] << "\n";
}

