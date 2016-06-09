#pragma once
//
//  TreeNode.h - define node for binary search tree
//  Program1
//

#ifndef __Program1__TreeNode__
#define __Program1__TreeNode__

#include <cstdint>
#include <memory>
#include <string>
#include <deque>
#include <algorithm>
#include "make_unique.h"
#include <iostream>
#include <deque>

class TreeNode {
public:
	// Constructor: initialize frequency
	TreeNode(const std::string &word_init) : word(word_init), frequency(1) {}

	~TreeNode() {}

	// Prevent copy/assign/move
	TreeNode(const TreeNode &other) = delete;
	TreeNode(TreeNode &&other) = delete;
	TreeNode &operator=(const TreeNode &other) = delete;
	TreeNode &operator=(TreeNode &&other) = delete;

// Insert the specified string into the tree.
// Normally called on the root node of the tree.
//
// str: string to insert
// Dies on assert if any non-alpha character in string.
void Insert(const std::string &str);
//inserts a 32KB string into the tree, by dividing the string 
//into alphanumeric words and calling insert in Parallel

void InsertBlockToTree(std::string a);
// Find the specified string in the tree.  Normally
// called on the root node of the tree.
//
// str: string to find
// returns: pointer to node, or nullptr if not found.
const TreeNode *Find(const std::string &str) const;

//Find all words in the tree which have the passed string as a stem
//Normally called on root of tree then recursively 
//
//str:the stem to find
//returns: pointers to all words with that stem
std::deque<std::string> FindStem(const std::string &str) const;

// Print all the words in the tree (mostly useful for debugging).
// Normally, call on root node.
void PrintAllWords() const;

// Get the word stored in the node
const std::string &getWord() const { return word; }

// Get the frequency value stored in this node.
int getFrequency() const { return frequency; }

private:
	// Word stored in the node
	const std::string word;

	// Frequency count: zero if no word ends at this node,
	// otherwise the number of times this word was seen in
	// the input file(s)
	int frequency;

	// Descendants.
	std::unique_ptr<TreeNode> left;
	std::unique_ptr<TreeNode> right;
};

#endif /* defined(__Program1__TreeNode__) */

