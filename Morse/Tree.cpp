#include "Tree.h" 

//splits an encoded message into a vector by spaces for easy decoding 
std::vector<std::string> split(std::string message){ 
	std::vector<std::string> vec;
	std::string delimiter = " ";
	std::string item;
	int pos = 0;
	//code in while loop used from StackOverflow, question 14265581
	while ((pos = message.find(delimiter)) != std::string::npos){
		item = message.substr(0, pos);
		vec.push_back(item);
		message.erase(0, pos + 1);
	}
	vec.push_back(message);
	return vec;
}

//general-purpose function for converting a single character to a string
std::string to_str(char the_ch){ 
	std::stringstream ss;
	std::string the_str;
	ss << the_ch;
	ss >> the_str;
	return the_str;
}

//builds the tree and the map  
void MorseTree::build_tree(){
	std::fstream in;
	in.open("morse.txt");
	MorseNode* node_ptr; //this is the cursor pointer
	std::string key;
	std::string value;
	std::string str;
	while (in >> str){ //each line in the file contains a letter key and Morse code value
		key = to_str(str[0]); //key
		value = str.substr(1, str.length() - 1); //value
		code_map[key] = value; 
		node_ptr = root; //start at root to insert each letter in the right location in the tree
		for (int i = 0; i < value.length(); ++i){
			if (value[i] == '.'){ //move left 
				if (node_ptr->left == NULL)
					node_ptr->left = new MorseNode; //nodes created are originally dummy nodes and can be "hopped"
				node_ptr = node_ptr->left;
			    }
			else if (value[i] == '_'){ //move right 
				if (node_ptr->right == NULL)
					node_ptr->right = new MorseNode;
				node_ptr = node_ptr->right;
		    }
		}
		node_ptr->letter = key; //node of this letter is completed after traversing its Morse code "path" in the tree
	}
	in.close();
}

//encodes the message 
void MorseTree::encode(const std::string& message){
	std::string encoded;
	for (int i = 0; i < message.length(); i++){ //each letter in the message 
		if (message[i] == ' ') //in case the message consists of words separated by spaces, provide a double-space
			encoded += " ";
		else{
			try{
				if (message[i] < 'a' || message[i] > 'z') //if character is not a letter, it is invalid
					throw message[i];
				std::string key = to_str(message[i]);
				std::string code = code_map[key]; //find Morse code value using this letter as the key
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

//decodes the message 
void MorseTree::decode(const std::string& message){
	std::vector<std::string> vec = split(message); //vector of Morse codes 
	std::string decoded;
	MorseNode* trav; //cursor for traversing the tree along Morse code "paths" to find corresponding letters
	for (int i = 0; i < vec.size(); ++i){ //each code representing a letter 
		trav = root;
		std::string bit = vec[i];
		for (int j = 0; j < bit.length(); ++j){ //each symbol in the code
			if (bit[j] == '.')
				trav = trav->left;
			else if (bit[j] == '_')
				trav = trav->right;
		}
		try{
			if ((trav->letter) == "*") //dummy node reached - invalid - dummy nodes do not contain letters
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

