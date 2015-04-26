#pragma once
#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>

struct MorseNode{
	std::string letter;
	MorseNode* left;
	MorseNode* right;
	//Constructor
	MorseNode(){
		letter = "*"; // Letter is originally a dummy
		left = NULL;
		right = NULL;
	}
	bool is_leaf(){ // Is this node a leaf?
		if (left == NULL && right == NULL)
			return true;
		else
			return false;
	}
	//Destructor
	~MorseNode() {}
};

class MorseTree{
public:
	MorseTree(){ 
		build_map(); //get the map set up in the constructor
		root = new MorseNode;
		build_tree();
	} 
	void build_map();
	void build_tree();
	void decode(const std::string& message);
	void encode(const std::string& message); // wrapper for search of letters in the tree to encode
	std::string search(MorseNode* loc_root, std::string let, std::string str); //return value is only used inside the function

private:
	MorseNode* root; 
	std::map<std::string, std::string> code_map; //used for building the tree
	std::string coded_let; //used for encoding a message
};