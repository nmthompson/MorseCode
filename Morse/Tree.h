#pragma once 
#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>

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
	//Destructor 
	~MorseNode() {}
};

class MorseTree{
public:
	MorseTree(){
		root = new MorseNode;
		build_tree(); //build tree and map
	}
	void build_tree();
	void decode(const std::string& message);
	void encode(const std::string& message);

private:
	MorseNode* root;
	std::map<std::string, std::string> code_map; //used for encoding a message
};