/******************************************************************************/
/*
\file	TextBranch.h
\author Chong Jun Xiang
\brief
Creating and assigning attributes to the branch
Idea inspired by Tng Kah Wei.
Original code by Tng Kah Wei but modified to fit personal usage
*/
/******************************************************************************/
#ifndef TEXT_BRANCH_H
#define TEXT_BRANCH_H

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

// An attribute consist of its name and value. The attribute name will then be matched against the various variable and assign the value to the respective variable
struct Attribute
{
	string name;
	string value;

	Attribute(string _name = "", string _value = "")
	{
		Set(_name, _value);
	}

	void Set(string _name = "", string _value = "")
	{
		this->name = _name;
		this->value = _value;
	}
};

// A branch (can) consists of a vector of attributes as well as sub/child branches
struct Branch
{
	string branchName;
	vector<Attribute> attributes;
	vector<Branch> childBranches;

	Branch (string _name = "")
	{
		branchName = _name;
	}

	void printBranch()
	{
		for (vector<Branch>::iterator branch = childBranches.begin(); branch != childBranches.end(); ++branch)
		{
			std::cout << branch->branchName << std::endl;
			for (vector<Attribute>::iterator branchAtt = branch->attributes.begin(); branchAtt != branch->attributes.end(); ++branchAtt)
			{
				std::cout << branchAtt->name << " << " << branchAtt->value << std::endl;
			}
			if (branch->childBranches.size() > 0)
			{
				branch->printBranch();
			}
		}
	}
};

#endif