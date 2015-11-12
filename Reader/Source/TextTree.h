/******************************************************************************/
/*
\file	TextTree.h
\author Chong Jun Xiang
\brief
Handle all reading & writing of files using this class
Idea inspired by Kah Wei
Original code by Kah Wei but modified to fit personal usage

Handles all txt file that are written in the same format

Format:
Made up of branches {} which contains Attributes [attribute name] <attribute value>
A branch can child branches

*Note*
All attribute name will be in CAPS for consistency purposes

E.g.
{
	[NAME] Parent Branch
	[ATTRIBUTE] Parent variable value

	{
		[NAME] Child Branch
		[ATTRIBUTE] Child variable value
	}
}
*/
/******************************************************************************/
#ifndef TEXT_TREE_H
#define TEXT_TREE_H

#include "TextBranch.h"
#include <fstream>

using std::ofstream;
using std::ostringstream;

// A class created to handle any txt files that are written in the same format
class TextTree
{
private:
	static const char BRANCH_START = '{';
	static const char BRANCH_END = '}';
	static const char ATTRIBUTE_START = '[';
	static const char ATTRIBUTE_END = ']';
	static const char COMMENT = '#';

public:
	static Branch FileToRead(const string fileName);
	static void FileToWrite(const string fileName, Branch mainBranch);

	static vector<string> ReadFile(const string fileName);
	static Branch ProcessFile(vector<string> branch);
	static void WriteFile(ofstream& file, Branch branch);
	
	static string Trim(const string str);
	static string Indent(int line);
};

#endif