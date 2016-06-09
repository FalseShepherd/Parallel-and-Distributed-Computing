#include <iostream>
#include "TreeNode.h"
#include "make_unique.h"
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <string>
#include <ctype.h>
#include <omp.h>
#include <mutex> 

void InsertTextToTree(std::string reference, TreeNode *root)
{
	std::ifstream TextToTree(reference);
	std::string text((std::istreambuf_iterator<char>(TextToTree)), std::istreambuf_iterator<char>());
	int split = 3;
	std::vector<std::string> SplitText;
	#pragma omp single
	while (split <= text.length() && split + 32000 < text.length())
	{
		if (text[split + 32000] == ' ')
		{
			SplitText.push_back(text.substr(split, 32000));
			split = split + 32000;
		}
		else
		{
			int b = 32000;
			while (text[split + b] != ' ')
			{
				b++;
			}
			SplitText.push_back(text.substr(split, b));
			split = split + b;
		}
	}
	SplitText.push_back(text.substr(split, text.length()));
	#pragma omp parallel for
	for (int i = 0; i < SplitText.size();i++)
	{
		root->InsertBlockToTree(SplitText[i]);
	}
}
std::vector<std::string> ReadAndFindStems(std::string FileName)
{
	std::ifstream TextToTree(FileName);
	std::string text((std::istreambuf_iterator<char>(TextToTree)), std::istreambuf_iterator<char>());
	std::vector<std::string> subs;
	std::string word;
	int split = 0;
	int split2 = 0;
	#pragma omp parallel
	while (split < text.length()-1)
	{
		while (text[split2] != '\n')
		{
			split2++;
		}
		subs.push_back(text.substr(split, split2-split));
		split2++;
		split = split2;
	}
	return subs;
}

int main(int argc, char* argv[]) {
	//read entire file into str
	TreeNode root("the");
	InsertTextToTree("WarAndPeace.txt", &root);
	std::vector<std::string> stems = ReadAndFindStems("teststem1.txt");
	omp_set_num_threads(1);
	for (int i = 0; i < stems.size(); i++)
	{
		std::deque<std::string> words = root.FindStem(stems[i]);
		#pragma omp parallel for
		for (int j = 0; j < words.size(); j++)
		{
			std::cout << words[j];
		}
		std::cout << "\n";
	}
}


