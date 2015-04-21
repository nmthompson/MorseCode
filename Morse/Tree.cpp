#include "Tree.h"

std::vector<std::string>& split(std::string message){
	//Want to split a string into strings for a vector
	std::vector<std::string> vec;
	std::string delimiter = " ";
	std::string item;
	int pos = 0;
	while ((pos = message.find(delimiter)) != std::string::npos){
		item = message.substr(0, pos);
		vec.push_back(item);
		message.erase(0, pos + 1);
	}
	vec.push_back(message);
	//partial code from StackOverflow, question 14265581
	return vec;
}

//read in from file, assign each key and its value to map
void MorseTree::build_map(){
	std::fstream in;
	in.open("morse.txt");
	std::string str;
	while (in >> str){
		code_map[str.substr(1, str.length() - 1)] = str[0];
	}
	in.close();
}
//build the tree with the map 
void MorseTree::build_tree(){
	std::map<std::string, std::string>::iterator iter;
	for (iter = code_map.begin(); iter != code_map.end(); ++iter){
		insert(iter->first, iter->second);
	}
}

void MorseTree::insert(const std::string& key, const std::string& value){
	MorseNode* node_ptr = root; //start at root
	for (int i = 0; i < key.length(); ++i){
		MorseNode this_node("*"); //initially dummy
		if (key[i] == '.'){ //create left node and move left
			node_ptr->left = &this_node;
			node_ptr = node_ptr->left;
		}
		else if (key[i] == '_'){ //move right
			node_ptr = node_ptr->right;
			node_ptr = node_ptr->right;
		}
	}
	node_ptr->letter = value; //node of this letter is established
}

void MorseTree::encode(const std::string& message){
	std::vector<std::string> vec = split(message); //vector of letter strings
	std::string encoded;
	for (int i = 0; i < vec.size(); ++i){ //for each letter message
		MorseNode* trav = root;
		while (trav != NULL){}
			//Search left tree
			//Search right tree
	}
	std::cout << encoded;
}

void MorseTree::decode(const std::string& message){
	std::vector<std::string> vec = split(message); //vector of morse codes
	std::string decoded;
	for (int i = 0; i < vec.size(); ++i){ //for each bit of code
		MorseNode* trav = root;
		std::string bit = vec[i];
		for (int j = 0; j < bit.length(); ++j){ //for each symbol in the code bit
			if (bit[j] == '.')
				trav = trav->left;
			else if (bit[j] == '_')
				trav = trav->right;
		}
		decoded.append(trav->letter);
	}
	std::cout << decoded;
}