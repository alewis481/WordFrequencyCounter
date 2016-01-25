/** 
 *
 */

#ifndef HASHED_SPLAYS_H_
#define HASHED_SPLAYS_H_

#include <string>
#include <vector>

#include "node.h"
#include "splay_tree.h"

/** 
 * HashedSplays is a class that contains a vector that holds a splay tree for
 *   each letter of the alphabet. It provides a few operations for outputting 
 *   information about the splay trees and the contents of the nodes contained
 *   therein. 
 */
class HashedSplays {
 public:
  /** 
   * HashedSplays 1-arg constructor. 
   *   Initializes table to be of the size indicated by the size parameter. 
   *   Will initialize to a vector of size 1 if the input parameter is not 
   *   a positive value. 
   *   @param size What the size of the table member variable should be. 
   */
  HashedSplays(int size);
  
  /** 
   * HashedSplays destructor. 
   *   Currently does nothing extra besides the default. 
   */
  ~HashedSplays();
  
  /** 
   * Collects all of the words in the file specified by file_name, and 
   *   puts them in the appropriate splay tree in table_ as a node. Increments
   *   the frequency of the word if it is already in a tree. 
   *   @param file_name The name of the file to collect words from. Function 
   *     will do nothing if the file_name is invalid. 
   */
  void processWordsFromFile(std::string file_name);
  
  /** 
   * Prints the contents of the tree containing every word that begins with 
   *  the letter specified by the input parameter. 
   *  @param letter Specifies which of the trees should have their contents
   *   inserted into the std output stream. 
   *   Can be uppercase or lowercase letter. 
   *   Will do nothing if letter is not A-Z | a-z.
   */
  void printTree(char letter);
  
  /** 
   * Prints the contents of the tree containing every word at the position in 
   *  the vector specified by the input parameter. 
   *  @param index Specifies the location of the tree in the vector that should
   *    have its contents inserted into the std output stream.
   *    Will do nothing if index < 0 or index > table_.size() - 1.
   */
  void printTree(int index);
  
  /** 
   * Prints the contents of the root node of every splay tree in table_, 
   *   as well as the number of nodes in each tree. 
   */
  void printHashCountResults();
  
  /** 
   * Prints every node whose word begins with the string specified by the 
   *   input parameter. 
   *   @in_part Specifies what every word to be printed must start with
   */
  void findAll(std::string in_part);
  
 private:
  /** 
   * Returns the index value that corresponds to the letter that is passed into
   *   the function. 
   *   @param in_letter The letter for which the index of the corresponding
   *    tree is desired. 
   */
  int getIndex(char in_letter);
  
  /** 
   * Removes any non-alphabetic characters from the input string. 
   *   @param in_str The letter for which special characters are to be removed. 
   */
  std::string formatString(std::string in_str);

  // Contains splay tree for each alphabetic character.
  std::vector<SplayTree<Node>> table_;   
                                         
  // int trees_;                       
  
};


#endif //HASHED_SPLAYS_H_
