#include "TreeNode.h"

void TreeNode::InsertBlockToTree(std::string a)
{
	std::string w;
	int location = 0;
	#pragma omp parallel
	while (location < a.length())
	{
			location++;
			while (iswalpha(a[location]))
			{
				if (iswalpha(a[location]) && location < a.length())
				{
					w += tolower(a[location]);
					location++;
				}
			}
			if (w != "")
			#pragma omp critical
			{
				this->Insert(w);
			}
			//std::cout << location << "	word: " << w << std::endl;
			w.clear();
	}
}
void TreeNode::Insert(const std::string &str)
{
	#pragma omp critical
{
	int compare = str.compare(this->word);
	if (compare == 0)
	{
		this->frequency++;
	}
	if (compare < 0 && this->left != NULL)
	{
		this->left->Insert(str);
	}
	else if (compare < 0)
	{
		this->left = make_unique<TreeNode>(str);
	}
	if (compare > 0 && this->right != NULL)
	{
		this->right->Insert(str);
	}
	else if (compare > 0)
	{
		this->right = make_unique<TreeNode>(str);
	}
}
}

// Find the specified string in the tree.  Normally
// called on the root node of the tree.
//
// str: string to find
// returns: pointer to node, or nullptr if not found.
const TreeNode *TreeNode::Find(const std::string &str) const 
{
	int compare = str.compare(this->getWord());
	if (compare == 0)
	{
		return this;
	}
	if (compare < 0 && this->left == NULL)
	{
		return NULL;
	}
	else if (compare < 0)
	{
		return this->left->Find(str);
	}
	if (compare > 0 && this->right == NULL)
	{
		return NULL;
	}
	else if (compare > 0)
	{
		return this->right->Find(str);
	}
}

std::deque<std::string> TreeNode::FindStem(const std::string &str) const
{
	int compare = str.compare(this->getWord());
	std::string subs = this->getWord().substr(0, str.length());
	bool sub = (subs == str);
	if (sub)
	{
		if(this->right != NULL && this->left != NULL)
		{
			std::deque<std::string> a;
			a.push_back(this->getWord() + ": " + std::to_string(this->getFrequency()) + ", ");
			std::deque<std::string> temp = this->right->FindStem(str);
			std::deque<std::string> temp2 = this->left->FindStem(str);
			a.insert(a.end(), temp.begin(), temp.end());
			a.insert(a.end(), temp2.begin(), temp2.end());
			return a;
		}
		if (this->left != NULL)
		{
			std::deque<std::string> a2;
			a2.push_back(this->getWord() + ": " + std::to_string(this->getFrequency()) + ", ");
			std::deque<std::string> temp = this->left->FindStem(str);
			a2.insert(a2.end(), temp.begin(), temp.end());
			return a2;
		}
		if (this->right != NULL)
		{
			std::deque<std::string> a3;
			a3.push_back(this->getWord() + ": " + std::to_string(this->getFrequency()) + ", ");
			std::deque<std::string> temp = this->right->FindStem(str);
			a3.insert(a3.end(), temp.begin(), temp.end());
			return a3;
		}
		std::deque<std::string> a4;
		a4.push_back(this->getWord() + ": " + std::to_string(this->getFrequency()) + ", ");
		return a4;
	}
	if (compare <0)
	{
		if (this->left != NULL)
		{
			return this->left->FindStem(str);
		}
	}
	else if (compare > 0)
	{
		if (this->right != NULL)
		{
			return this->right->FindStem(str);
		}
	}
	std::deque<std::string> a4;
	a4.push_back("");
	return a4;
}

// Print all the words in the tree (mostly useful for debugging).
// Normally, call on root node.
void TreeNode::PrintAllWords() const
{
	std::cout << this->word <<": "<< this->frequency << "\n";
	if (left != NULL)
	{
		left->PrintAllWords();
	}
	if (right != NULL)
	{
		right->PrintAllWords();
	}
}

