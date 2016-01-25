#include <algorithm>

#include "node.h"

Node::Node() : word_{}, frequency_{0} {}

Node::Node(std::string in_word, int freq) : word_{in_word}, frequency_{freq} {}

Node::~Node() {}

std::string Node::getWord() const {return word_;}

int Node::getFrequency() const {return frequency_;}

void Node::incrementFrequency() {++frequency_;}

bool Node::operator<(const Node& other) const {return word_ < other.word_;}

bool Node::operator==(const Node& other) const {return word_ == other.word_;}

Node Node::operator=(const Node& other) {
  if (!(this == &other)) {
    word_ = other.word_;
    frequency_ = other.frequency_;
  }
  return *this;
}

bool Node::operator%(const Node& other) const {
  //compares lowercase forms of words, transform converts each string to lower
  std::string text {getWord()};
  std::transform(text.begin(), text.end(), text.begin(), ::tolower);
  std::string compared {other.getWord()};
  std::transform(compared.begin(), compared.end(), compared.begin(), ::tolower);

  //returns false if node's word is not a substring of other's word
  if(text.length() > compared.length())
    return false;
  else if(!(text.find(compared)==std::string::npos))
    return false;
  else
    return true;
}

std::ostream& operator<<(std::ostream& out, const Node& in_node) {
  out << "Node [word=" << in_node.getWord() << ", frequency=";
  out << in_node.getFrequency() << "]";
 return out;
}


