#pragma once 
#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>

//node for the Morse code tree
struct MorseNode{ 
	std::string letter;
	MorseNode* left;
	MorseNode* right;
	//constructor 
	MorseNode(){
		letter = "*"; //default letter value for a node
		left = NULL;
		right = NULL;
	}
	//destructor 
	~MorseNode() {}
};

//the tree object
class MorseTree{
public:
	//constructor
	MorseTree(){
		root = new MorseNode;
		build_tree(); 
	}
	void build_tree();
	void decode(const std::string& message);
	void encode(const std::string& message);

private:
	MorseNode* root;
	std::map<std::string, std::string> code_map; //used for encoding a message
};