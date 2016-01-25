//TODO: make a more interesting application of the HashedSplays class
#include "hashed_splays.h" 
#include <iostream>

int main(int argc, char *argv[]) {
  const int ALPHABET_SIZE = 26; 
  
  //set up object to work on 
  HashedSplays word_frequecy(ALPHABET_SIZE);
  //build the trees from words in the input file
  word_frequecy.processWordsFromFile(argv[1]);
  //few tests to show the results
  word_frequecy.printHashCountResults();
  word_frequecy.printTree(19); //19th character of alphabet is "t"
  char in_char = 'F';
  word_frequecy.printTree(in_char);
  std::string test_str = "the";
  word_frequecy.findAll(test_str); // outputs all chars starting w/ "the"
  std::cout << '\n';
}
