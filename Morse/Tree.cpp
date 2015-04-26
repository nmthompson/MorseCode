#include "Tree.h"

//split an encoded message into a vector for easy iteration
std::vector<std::string> split(std::string message){
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
	MorseNode* node_ptr;
	for (iter = code_map.begin(); iter != code_map.end(); ++iter){
		std::string key = iter->first;
		std::string value = iter->second;
		node_ptr = root; //start at root
		for (int i = 0; i < key.length(); ++i){
			if (key[i] == '.'){ //move left
				if (node_ptr->left == NULL)
					node_ptr->left = new MorseNode;
				node_ptr = node_ptr->left;
			}
			else if (key[i] == '_'){ //move right
				if (node_ptr->right == NULL)
					node_ptr->right = new MorseNode;
				node_ptr = node_ptr->right;
			}
		}
		node_ptr->letter = value; //node of this letter is established
	}
}

//encode the message
void MorseTree::encode(const std::string& message){
	std::string encoded;
	MorseNode* trav = root;
	for (int i = 0; i < message.length(); ++i){ //for each letter
		std::string let = "";
		let += message[i];
		search(trav, let, ""); // get code for letter
		encoded += coded_let;
		encoded += " ";
	}
	std::cout << encoded << std::endl;
}

//get the code for each letter by traversing the tree
std::string MorseTree::search(MorseNode* loc_root, std::string let, std::string str){
	static std::string good_str;
	if (loc_root->is_leaf() && loc_root->letter != let) //if leaf is reached and the letter not found
		return "";
	else if (loc_root->letter == let){ //if letter has been found
		coded_let = str; //the correct string should be complete
		return str; //but the rest of the tree must be searched to complete the function (how can this be improved?)
	}
	else{
		if (loc_root->left != NULL){
			str += ".";
			search(loc_root->left, let, str);
			str = str.substr(0, str.length() - 1); //done searching left, erase unneeded part of path
		}
		if (loc_root->right != NULL){
			str += "_";
		    search(loc_root->right, let, str);
			str = str.substr(0, str.length() - 1); //done searching right, erase unneeded part of path
		}
	}
	return str;
}

//decode the message
void MorseTree::decode(const std::string& message){
	std::vector<std::string> vec = split(message); //vector of morse codes
	std::string decoded;
	MorseNode* trav;
	for (int i = 0; i < vec.size(); ++i){ //for each bit of code
		trav = root;
		std::string bit = vec[i];
		for (int j = 0; j < bit.length(); ++j){ //for each symbol in the code bit
			if (bit[j] == '.')
				trav = trav->left;
			else if (bit[j] == '_')
				trav = trav->right;
		}
		decoded += (trav->letter);
	}
	std::cout << decoded << std::endl;
}