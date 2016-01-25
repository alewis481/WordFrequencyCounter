#include <iostream>      // for cout, cerr
#include <fstream>       // for ostream
#include <string>        // for string, getline
#include <sstream>       // for stringstream
#include <vector>        // for vector
#include <cctype>        // for isupper, islower, tolower
#include <regex>         // for regex, regex_replace
#include <algorithm>     // for max

#include "hashed_splays.h"

const int ALPHABET_SIZE = 26;  //splay tree for every alphabet char, no case

//set table's size to 1 if size parameter is not positive
HashedSplays::HashedSplays(int size) : table_(std::max(1, size)) {}

HashedSplays::~HashedSplays() {}

void HashedSplays::processWordsFromFile(std::string file_name) {
  const int INITIAL_NODE_FREQ = 1;  //used when initializing new node

  //does nothing if file is invalid
  std::ifstream in_file{file_name};
  if(!in_file.is_open()) {
    std::cerr << "Error in opening file!\n";
    return;
  }
  
  std::string file_line;
  while(std::getline(in_file, file_line)) {
    //stringstream used to parse through individual words in line
    std::stringstream str_in{file_line};
    //is good while there are words remaining to be parsed
    while(str_in.good()) {
      std::string word;
      str_in >> word;
      std::string formatted_word{formatString(word)};
      Node new_node(formatted_word, INITIAL_NODE_FREQ);
      if (formatted_word == "")
	continue;
      //send to splay tree at index defined by first letter of word
      else if(!table_[getIndex(formatted_word[0])].contains(new_node))
	table_[getIndex(formatted_word[0])].insert(new_node);
      //word already exists in tree, increment frequency counter
      else
	table_[getIndex(formatted_word[0])].incrementValue();       
    }
  }
  in_file.close();
}

void HashedSplays::printTree(char letter) {
  if (isalpha(letter)) {
    table_[getIndex(letter)].printTree();
    std::cout << "This tree has " << table_[getIndex(letter)].getSplayCount()
	      << " splays.\n";
  }
  else 
    std::cerr << "ERROR: invalid input to printTree(char)!\n";
}

void HashedSplays::printTree(int index) {
  if (index < ALPHABET_SIZE) {
    table_[index].printTree();
    std::cout << "This tree had " << table_[index].getSplayCount()
	      << " splays.\n";
  }
  else
    std::cerr << "ERROR: invalid input to printTree(int)!\n";
}

void HashedSplays::printHashCountResults() {
  for (int i = 0; i < ALPHABET_SIZE; ++i) {
    if (!table_[i].isEmpty()) {
      std::cout << "This tree starts with ";
      table_[i].printRoot();
      std::cout << "and has " << table_[i].getNodeCount() << " nodes.\n";
    }
    else
      std::cout << "This tree has no nodes.\n";
  }
}

void HashedSplays::findAll(std::string in_part) {
  std::cout << "Printing the results of the nodes that start with '"
	    << in_part << "'\n";
  Node str_node(in_part, 1);
  //SplayTree's findAll function does the printing
  table_[getIndex(in_part[0])].findAll(str_node);
}

int HashedSplays::getIndex(char in_letter) {
  if (isupper(in_letter))
    return in_letter - 'A';
  else if (islower(in_letter))
    return in_letter - 'a';
  else {
    std::cerr << "ERROR: bad input passed to getIndex\n";
    return 0;
  }
}

std::string HashedSplays::formatString(std::string in_str) {
  //regex to filter out non-alphebetic characters
  std::regex special_chars_re{R"(\W|\s|\d)"};
  //removes special characters and returns formatted string
  return std::regex_replace(in_str, special_chars_re, "");
}
