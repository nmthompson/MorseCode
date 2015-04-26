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
	MorseNode(std::string the_let){
		letter = the_let; // Letter is originally a dummy
		left = NULL;
		right = NULL;
	}
	bool is_leaf(){ // Is this node a leaf?
		if (left == NULL || right == NULL)
			return true;
		else
			return false;
	}
};

class MorseTree{
public:
	MorseTree(){ 
		build_map(); //get the map set up in the constructor
		MorseNode r_node("*"); //set the root
		root = &r_node;
		build_tree();
	} 
	void build_map();
	void build_tree();
	//Returns true if successfully inserted
	void insert(const std::string& key, const std::string& value);
	void decode(const std::string& message);
	void encode(const std::string& message);
	void print(const std::string& message);

private:
	MorseNode* root;
	std::map<std::string, std::string> code_map; 
};