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

//convert character to string
std::string to_str(char the_ch){ 
	std::stringstream ss;
	std::string the_str;
	ss << the_ch;
	ss >> the_str;
	return the_str;
}

//build the tree and the map  
void MorseTree::build_tree(){
	std::fstream in;
	in.open("morse.txt");
	MorseNode* node_ptr; 
	std::string str;
	while (in >> str){ //while line in file is being read
		std::string key = to_str(str[0]); //key
		std::string value = str.substr(1, str.length() - 1); //value
		code_map[key] = value; 
		node_ptr = root; //start at root 
		for (int i = 0; i < value.length(); ++i){
			if (value[i] == '.'){ //move left 
				if (node_ptr->left == NULL)
					node_ptr->left = new MorseNode;
				node_ptr = node_ptr->left;
			    }
			else if (value[i] == '_'){ //move right 
				if (node_ptr->right == NULL)
					node_ptr->right = new MorseNode;
				node_ptr = node_ptr->right;
		    }
		}
		node_ptr->letter = key; //node of this letter is established 
	}
	in.close();
}

//encode the message 
void MorseTree::encode(const std::string& message){
	std::string encoded;
	std::map<std::string, std::string>::iterator iter;
	for (int i = 0; i < message.length(); i++){ //for each letter 
		if (message[i] == ' ')
			encoded += " ";
		else{
			try{
				if (message[i] < 'a' || message[i] > 'z') //if character is not a letter, it is invalid
					throw message[i];
				std::string key = to_str(message[i]);
				std::string code = code_map[key];
				encoded += code + " ";
			}
			catch (char ch){
				std::cout << ch << " does not have a Morse code. Message invalid." << std::endl;
				system("pause");
				exit(1);
			}
		}
	}
	std::cout << encoded << std::endl;
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
		try{
			if ((trav->letter) == "*") //dummy node reached - invalid
				throw (trav->letter);
			decoded += (trav->letter);
		}
		catch (std::string str){
			std::cout << str << " not a valid symbol to decode." << std::endl;
			system("pause");
			exit(1);
		}
	}
	std::cout << decoded << std::endl;
}

