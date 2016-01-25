/** 
 *
 */
#ifndef NODE_H_
#define NODE_H_

#include <string>   //  for string
#include <ostream>  //  for ostream

/** 
 * Node is a class for storing words that are collected from a text file.
 * It stores the frequency of occurence of the stored word in the text file as
 * well. A few operations have been overloaded for this class for practice. They
 * are utilized in the HashedSplays class, as well as the SplayTree class.  
 */
class Node {
 public:
  /** 
   * Default no-arg constructor. 
   *   Calls default initializer on word_, and 
   *   initializes frequency_ to 0. 
   */
  Node();

  /** 
   * 2 argument Node constructor. 
   *   Initializes word_ to in_word, and frequency_ to frequency. 
   *   @param in_word    A word from the text file. 
   *   @param frequency  The frequency that the word arises in the file. 
   */
  Node(std::string in_word, int frequency);

  /** 
   * Node Destructor. 
   *   Currently does nothing beyond the default. 
   */
  ~Node();
  
  /** 
   *  Returns the word stored in word_. 
   */
  std::string getWord() const;
  
  /** 
   * Returns the value stored in frequency_.
   */
  int getFrequency() const;
  
  /** 
   * Increments the value of frequency_ by 1. 
   */
  void incrementFrequency();
  
  /** 
   * < operator. 
   *   Compares the two strings in each node. 
   *   Returns true if word_ < other.word_. 
   *   @param other Node to compare this to. 
   */
  bool operator<(const Node& other) const;
  
  /** 
   * == operator. 
   *   Compares the two strings in each node. 
   *   Returns true if word_ == other.word_.
   *   @param other Node to compare this to. 
   */
  bool operator==(const Node& other) const;
  
  /** 
   * Assignment operator. 
   *   Sets the value of word_ to other, and the value of frequency_ to 
   *   other.frequency_.
   *   @param other Node to compare this to. 
   */  
  Node operator=(const Node& other);
  
  /** 
   * % operator. 
   *   Returns true if lowercase word_ is a substring of lowercase other.word_. 
   *   @param other Node to compare this to. 
   */
  bool operator%(const Node& other) const;
  
  /** 
   * Insertion operator. 
   *   Inserts the word as well as the date in a formatted output to out.
   *   @param out The ostream object that data is inserted into
   *   @param in_node The node the data is taken from. 
   */
  friend std::ostream& operator<<(std::ostream& out, const Node& in_node);
  
  
 private:
  std::string word_;    // stores a word from file
  int frequency_;       // stores frequency of word in file
};



#endif //NODE_H_
