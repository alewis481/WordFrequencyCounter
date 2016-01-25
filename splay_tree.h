/** 
 *
 */
#ifndef SPLAY_TREE_H_
#define SPLAY_TREE_H_

#include <iostream>   // for cout, cerr


/** 
 * SplayTree is an implementation of the splay tree data structure. A splay 
 *   tree is a modified binary search tree that sets the last accessed node in 
 *   the tree to be the root through an operation called splaying. This class 
 *   provides a variety of functions for accessing, modifying and printing
 *   the contents of the tree. The type of the template parameter is assumed to
 *   have the less-than "<" relational operator defined, as it is utilized in 
 *   this implementation.  
 */
template <typename T>
class SplayTree {
 public:
  /** 
   * SplayTree no-arg constructor. 
   *   Sets root to nullptr, and counter values to 0.
   */
  SplayTree();
  
  /** 
   * SplayTree copy constructor. 
   *   Initializes a new tree by making a deep copy of the contents of 
   *   the tree in other. 
   *   @param other The tree whose contents are to be copied. 
   */
  SplayTree(const SplayTree& other);
  
  /** 
   * SplayTree destructor.
   *   Frees all the memory used by the nodes in the tree. 
   */
  ~SplayTree();
  
  /** 
   * Inserts the element into the splay tree. Splays the tree afterwards to 
   *   make the node containing element_in the root. Increments node_count also.
   *   @param element_in The object to be inserted into the splay tree. 
   */
  void insert(T element_in);
  
  /** 
   * Removes the first vertex discovered that contains element_in from the tree.
   *   Decrements node_count as well. 
   *   @param element The object to be removed from the splay tree. 
   */
  void remove(T element);
  
  /** 
   * Returns true if there is a vertex in the tree that contains element. 
   *   @param element The object to be searched for in the tree. 
   */
  bool contains(T element) {return findVertex(element) != nullptr;}
  
  /** 
   * Returns true if there are no nodes in the tree. 
   */
  bool isEmpty() const {return node_count_ == 0;}
  
  /** 
   * Prints the contents of each vertex in the tree in sorted order to the std
   *   output stream. 
   */
  void printTree();
  
  /** 
   * Returns the number of times that the splay function has been invoked. 
   */
  int getSplayCount() const  {return splay_counter_;}

  /** 
   * Increments the frequency counter of the object contained in the root 
   *   vertex. Utilized by the Node class for this project. 
   */
  void incrementValue()  {(root_->element).incrementFrequency();}
  
  /** 
   * Returns the number of vertices in the splay tree. 
   */
  int getNodeCount() const  {return node_count_;}
  
  /** 
   * Assignment operator. 
   *   Deletes the current contents of the tree, and makes a deep copy 
   *   of the contents of the tree in other. 
   *   @param other The tree whose contents are to be copied. 
   */
  const SplayTree& operator=(const SplayTree& other);

  /** 
   * Inserts the root element into the std output stream. Assumes the 
   *   insertion operator "<<" is defined for the template parameter type. 
   */
  void printRoot() const;
  
  /** 
   * Inserts each element x from the tree into the std output stream 
   *   that satisfies element_in % x. Assumes the modulus operator "%" is 
   *   defined for the template parameter type. 
   */
  void findAll(const T& element_in);
  
  /** 
   * Performs the splay operation on the vertex containing the input parameter. 
   *   The vertex that contains element_in becomes the new root after 
   *   completion. If no vertex contains element_in, the function does nothing. 
   *   The splay_count_ value is incremented by 1 after successful completion. 
   *   @param element_in The object whose containing vertex is to be set as the 
   *     root of the tree. 
   */
  void splay(T element_in);

 private:
  /** 
   * Vertex is the storage container for objects to be inserted into the 
   *   splay tree. It holds the location of its children, as well as its 
   *   parent. If it has no parent, then it is the root, and parent is set
   *   to nullptr. 
   */
  struct Vertex {
    T element;           
    Vertex* left_child;
    Vertex* right_child;
    Vertex* parent;
    
    /** 
     * Vertex default constructor. 
     *   Calls default initializer on element, and sets each pointer to nullptr.
     */
  Vertex() : element{},
      left_child{nullptr},
      right_child{nullptr},
      parent{nullptr} {}
    
    /** 
     * Vertex 4 arg constructor.
     *   Initializes each of the member variables to the values in their 
     *   corresponding input parameters. 
     *   @param in_element Copies in_element to the member variable element.
     *   @param left_vertex Contains the location of the vertex's left child.
     *   @param right_vertex Contains the location of the vertex's right child.
     *   @param parent_vertex Contains the location of the vertex's parent. 
     */
  Vertex(const T& in_element,
	 Vertex* left_vertex,
	 Vertex* right_vertex,
	 Vertex* parent_vertex) :
    element{in_element}, left_child{left_vertex},
      right_child{right_vertex}, parent{parent_vertex} {}
  };
  
  /** 
   * Deletes the vertex specified by the parameter as well as any 
   *   descendants of the vertex. 
   *   @param node The vertex that is to be deleted along with its descendants. 
   */
  void clear(Vertex* node);

  /** 
   * Rotates node to the left by making the right child of node the parent of  
   *   node. Preserves the order of the tree. 
   *   @param node The vertex to be rotated. 
   */
  void leftRotate(Vertex* node);
  
  /** 
   * Rotates node to the right by making the left child of node the parent of  
   *   node. Preserves the order of the tree. 
   *   @param node The vertex to be rotated. 
   */
  void rightRotate(Vertex* node);
  
  /** 
   * Returns the element contained in the leftmost descendant of node. 
   *   @param node The vertex whose smallest descendant's object is to be 
   *     returned. 
   */
  T findMin(Vertex* node);

  /** 
   * Returns the element contained in the rightmost descendant of node. 
   *   @param node The vertex whose largest descendant's object is to be 
   *     returned. 
   */
  T findMax(Vertex* node);
  
  /** 
   * Prints the object contained by node as well as each of node's descendants 
   *   in order. 
   *   @param node The vertex whose contents and whose descendant's contents 
   *     are to be printed. 
   */
  void printTree(Vertex* node);
  
  /** 
   * Inserts each element x from node and its descendants
   *   into the std output stream that satisfies element_in % x. 
   *   Assumes the modulus operator "%" is defined for the template 
   *   parameter type. 
   *   @param element_in The object to compare the vertex's objects to w/ %.
   *   @param node The vertex whose descendants are to be checked. 
   */
  void findAll(const T& element_in, Vertex* node);
  
  /** 
   * Makes a new vertex and copies the contents of the old vertex to it. 
   *   @param old The vertex whose contents are to be copied. 
   */
  Vertex* copy(Vertex* old) {
    if (!old)
      return nullptr;
    else {
      Vertex* new_vertex{new Vertex(old->element,
				    copy(old->left_child),
				    copy(old->right_child))};
      //set the parent of children to new_vertex
      if(new_vertex->left_child)
	new_vertex->left_child->parent = new_vertex;
      if(new_vertex->right_child)
	new_vertex->right_child->parent = new_vertex;
      return new_vertex;
    }
  }
  
  /** 
   * Searches the tree for a vertex containing element_in. If a vertex is 
   *   found, a pointer to the vertex is returned. If no vertex is found, 
   *   nullptr is returned. 
   *   @param element_in The object to be searched for in the tree. 
   */
  Vertex* findVertex(T element_in) {
    Vertex* temp_vertex = root_;
    while(temp_vertex && !(temp_vertex->element == element_in)) {
      if(element_in < temp_vertex->element)
	temp_vertex = temp_vertex->left_child;
      else 
	temp_vertex = temp_vertex->right_child;
    }
    return temp_vertex;    
  }

  Vertex* root_;      // holds the root vertex for the tree
  int splay_counter_; // counter for the number of splays performed on tree
  int node_count_;    // holds the number of vertices in the tree
};


// Function definitions below
// TODO: Rearrange definitions to be in the same order as declarations

template <typename T>
SplayTree<T>::SplayTree() : root_{nullptr}, splay_counter_{0}, node_count_{0} {}


template <typename T>
SplayTree<T>::SplayTree(const SplayTree& other) {*this = other;}

template <typename T>
SplayTree<T>::~SplayTree() {
  //clear deletes all the vertices
  clear(root_);
  root_ = nullptr;
}



template <typename T>
void SplayTree<T>::insert(T in_element) {
  //creates the vertex holding in_element to be inserted into the tree
  Vertex* new_vertex {new Vertex()};
  new_vertex->element = in_element;

  Vertex* temp_vertex {root_};
  //after while loop below, parent holds vertex of new parent to new_vertex
  Vertex* parent {temp_vertex};
  
  while(temp_vertex) {
    //when temp_vertex == nullptr, parent will hold correct parent of new_node
    parent = temp_vertex;
    if (in_element < temp_vertex->element)
      temp_vertex = temp_vertex->left_child;
    else
      temp_vertex = temp_vertex->right_child;
  }
  
  new_vertex->parent = parent;
  
  if (!root_)
    root_ = new_vertex;
  else if (in_element < parent->element)
    parent->left_child = new_vertex;
  else
    parent->right_child = new_vertex;

  //if new_vertex is not root, set it to root
  splay(new_vertex->element);
  ++node_count_;
}

template <typename T>
void SplayTree<T>::remove(T element) {
  Vertex* temp_vertex = findVertex(element);
  if (!temp_vertex)
    return;

  //sets the node to be removed to root position
  splay(temp_vertex->element);

  //no left children
  if(!temp_vertex->left_child) {
    root_ = temp_vertex->right_child;
    root_->parent = nullptr;
  }
  //no right children
  else if (!temp_vertex->right_child) {
    root_ = temp_vertex->left_child;
    root_->parent = nullptr;
  }
  // left & right children, set largest left descendant as root and right_child
  // of new_vertex to the right_child of left_max
  else {
    Vertex* left_max = findVertex(findMax(temp_vertex->left_child));
    //true when temp_vertex's parent is not root
    if(left_max->parent != temp_vertex) {
      left_max->parent->right_child = nullptr;
      left_max->parent = nullptr;
      left_max->left_child = temp_vertex->left_child;
      left_max->left_child->parent = left_max;
    }
    //left_max is < right_child of temp_vertex, so ordering holds
    left_max->right_child = temp_vertex->right_child;
    left_max->right_child->parent = left_max;
    root_ = left_max;
  }

  //temp_vertex's existence was verified at beginning of function, so no
  //fear of deleting unallocated memory
  delete temp_vertex;
  --node_count_;
} 


//currently returns T and not Vertex*
template <typename T>
T SplayTree<T>::findMin(Vertex* node) {
  if(!node)
    //return default initialized T object
    return T{};
  
  Vertex* temp_vertex {node};
  while(temp_vertex->left_child)
    temp_vertex = temp_vertex->left_child;
  splay(temp_vertex->element);
  
  return temp_vertex->element;
}

//currently returns T and not Vertex*
template <typename T>
T SplayTree<T>::findMax(Vertex* node) {
  if(!node)
    //return default initialized T object
    return T{};
  
  Vertex* temp_vertex {node};
  while(temp_vertex->right_child)
    temp_vertex = temp_vertex->right_child;
  splay(temp_vertex->element);
  
  return temp_vertex->element;
}

template <typename T>
void SplayTree<T>::printTree() {
  //calls internal print function
  printTree(root_);
}

//recursive function, called for each descendant of node
template <typename T>
void SplayTree<T>::printTree(Vertex* node) {
  if(node->left_child)
    printTree(node->left_child);
  if(node)
    //assumes insertion operator "<<" is defined for T
    std::cout << node->element << "\n";
  if(node->right_child)
    printTree(node->right_child);
}

template <typename T>
void SplayTree<T>::printRoot() const {
  if(root_)
    std::cout << root_->element;
}


template <typename T>
void SplayTree<T>::rightRotate(Vertex* node) {
  if (!node)
    return;

  //node's left child will become node's new parent
  Vertex* rotate_node {node->left_child};
  //modify the new relations for rotate_node when it exists
  if(rotate_node) {
    node->left_child = rotate_node->right_child;
    if(rotate_node->right_child) {rotate_node->right_child->parent = node;}
    rotate_node->right_child = node;
    rotate_node->parent = node->parent;
  }

  if(!node->parent)
    root_ = rotate_node;
  //replace parent's relationship w/ node to w/ rotate_node 
  else if (node->parent->left_child == node)
    node->parent->left_child = rotate_node;
  else
    node->parent->right_child = rotate_node;
  
  //node is now a child of rotate_node
  node->parent = rotate_node;  
}

template <typename T>
void SplayTree<T>::leftRotate(Vertex* node) {
  if (!node)
    return;

  //node's right child will become node's new parent
  Vertex* rotate_node {node->right_child};
  //modify the new relations for rotate_node when it exists
  if(rotate_node) {
    node->right_child = rotate_node->left_child;
    if(rotate_node->left_child) {rotate_node->left_child->parent = node;}
    rotate_node->left_child = node;
    rotate_node->parent = node->parent;
  }
  if(!node->parent)
    root_= rotate_node;
  //replace parent's relationship w/ node to w/ rotate_node 
  else if (node->parent->left_child == node)
    node->parent->left_child = rotate_node;
  else
    node->parent->right_child = rotate_node;  
  
  //node is now a child of rotate_node
  node->parent = rotate_node;
}

template <typename T> 
void SplayTree<T>::splay(T element_in) {
  if(!contains(element_in))
    return;
  //vertex to become the new root 
  Vertex* splay_vertex {findVertex(element_in)};
  
  if (splay_vertex == root_)
    return;

  //continue rotations until splay_vertex is root
  while(splay_vertex != root_) {
    //when splay_vertex is left child of root
    if(splay_vertex->parent == root_ &&
       splay_vertex->parent->left_child == splay_vertex) {
      rightRotate(splay_vertex->parent);    
    }
    //when splay_vertex is right child of root
    else if (splay_vertex->parent == root_ &&
	     splay_vertex->parent->right_child == splay_vertex) {
      leftRotate(splay_vertex->parent);          
    }
    //when splay_vertex is left child of parent, and parent is the left
    //child of grandparent
    else if (splay_vertex->parent->left_child == splay_vertex &&
	     splay_vertex->parent->parent->left_child == splay_vertex->parent) {
      rightRotate(splay_vertex->parent->parent);
      rightRotate(splay_vertex->parent);           
    }
    //when splay_vertex is right child of parent, and parent is right child
    //of grandparent
    else if (splay_vertex->parent->right_child == splay_vertex &&
	     splay_vertex->parent->parent->right_child == splay_vertex->parent){
      leftRotate(splay_vertex->parent->parent);
      leftRotate(splay_vertex->parent);        
    }
    //when splay_vertex is left child of parent, and parent is the right child
    //of grandparent
    else if (splay_vertex->parent->left_child == splay_vertex &&
	     splay_vertex->parent->parent->right_child ==
	     splay_vertex->parent) {
      rightRotate(splay_vertex->parent);
      leftRotate(splay_vertex->parent);          
    }
    //when splay_vertex is right child of parent, and parent is left child of
    //grandparent
    else if (splay_vertex->parent->right_child == splay_vertex &&
	     splay_vertex->parent->parent->left_child ==
	     splay_vertex->parent) {
      leftRotate(splay_vertex->parent);
      rightRotate(splay_vertex->parent);         
    }
    //all cases should have been handled, so error if I get here
    else {
      std::cerr << "Error in splay() if this prints!\n";
    }
    ++splay_counter_;
  }
}

template <typename T>
void SplayTree<T>::findAll(const T& element) {
  //call internal findAll function
  findAll(element, root_);
}


template <typename T>
void SplayTree<T>::findAll(const T& element_in, Vertex* node) {  
  if (node) {
    if (element_in % node->element) {
      findAll(element_in, node->left_child);
      std::cout << node->element << "\n";
      findAll(element_in, node->right_child);
    }
    else {
      findAll(element_in, node->left_child);
      findAll(element_in, node->right_child);
    }
  }
}

//recursive function, called for each descendant of node
template <typename T>
void SplayTree<T>::clear(Vertex* node) {
  if (node && node->left_child) 
    clear(node->left_child);
  if (node && node->right_child)
    clear(node->right_child);
  if(node)
    delete node;
  --node_count_;
}

template <typename T>
const SplayTree<T>& SplayTree<T>::operator=(const SplayTree& other) {
  if(this != &other) {
    clear(root_);
    root_ = copy(other.root_);
  }
  return *this;
}

#endif //  SPLAY_TREE_H_
