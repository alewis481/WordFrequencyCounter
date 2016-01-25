#include "splay_tree.h"

//make sure sets ints to 0
template <typename T>
SplayTree<T>::SplayTree() : root_{nullptr}, splay_counter_{0}, node_count_{0} {}


template <typename T>
SplayTree<T>::SplayTree(const SplayTree& other) {*this = other;}
					      
template <typename T>
~SplayTree<T>::SplayTree() {
  clear(root);
  root = nullptr;
}

template <typename T>
void SplayTree<T>::insert(T in_element) {
  Vertex* new_vertex {new Vertex()};
  new_vertex->element = in_element;
  
  if (!root) {
    root = new_vertex;
  }
  Vertex* temp_vertex {root};
  while (temp_vertex->left_child && in_element < temp_vertex->element){
    temp_vertex = temp_vertex->left_child;
  }
  
  if(!temp_vertex->left_child && in_element < temp_vertex->element) {
    new_vertex->parent = temp_vertex;
    temp_vertex->left_child = new_vertex;
    splay(new_vertex->element);
  }
  
  while (temp_vertex->right_child && temp_vertex->element < in_element){
    temp_vertex = temp_vertex->right_child;
  }
  if(!temp_vertex->right_child && temp_vertex->element < in_element) {
    new_vertex->parent = temp_vertex;
    temp_vertex->right_child = new_vertex;
    splay(new_vertex->element);
  }
  else {
    //double check that no extra work needs to be done here
    new_vertex->parent = temp_vertex->parent;
    new_vertex->right_child = temp_vertex;
    temp_vertex->parent = new_vertex;
    splay(new_vertex->element);
  }
  ++node_count_;
}

//needs fixing
template <typename T>
void SplayTree<T>::remove(T element) {
  Vertex* temp_vertex = findVertex(element);
  if (!temp_vertex)
    return;
  // splay(temp_vertex);
  //Vertex* left_temp = findMax(temp_vertex->left_child);
  // Vertex* right_temp = findMin(temp_vertex->right_child);
  splay(temp_vertex);

  if(!temp_vertex->left_child) {
    root_ = temp_vertex->right_child;
    root_->parent = nullptr;
  }
  else if (!temp_vertex->right_child) {
    root_ = temp_vertex->left_child;
    root_->parent = nullptr;
  }
  else {
    //to be finished when i make the splay operation
    //largest small 
    Vertex* left_max = findVertex(findMax(temp_vertex->left_child));
    if(left_max->parent != temp_vertex) {
      left_max->parent = nullptr;
      left_max->left_child = temp_vertex->left_child;
      left_max->left_child->parent = left_max;
      root_ = left_max;
    }
    left_max->right_child = temp_vertex->right_child;
    left_max->right_child->parent = left_max;
  } 
  delete temp_vertex;
  --node_count;
  //if(temp_vertex->parent->left_child == temp_vertex) {
  // temp_vertex->parent->left_child = temp_vertex->left_child;
  // Vertex* right_temp = findMax(temp_vertex->left_child);
  // right_temp->right_child = temp_vertex->right_child;
  // delete temp_vertex;
  // --node_count;
  //}
} 

//template <typename T> 
//bool SplayTree<T>::contains(T element) {return findVertex(element) != nullptr;}

//currently returns Vertex* and not T*
template <typename T>
T SplayTree<T>::findMin(Vertex* node) {
  if(!node)
    return nullptr;
  Vertex* temp_vertex {node};
  while(temp_vertex->left_child)
    temp_vertex = temp_vertex->left_child;
  // splay(temp_vertex);
  return temp_vertex->element;
}

//currently returns Vertex* and not T*
template <typename T>
T SplayTree<T>::findMax(Vertex* node) {
  if(!node)
    return nullptr;
  Vertex* temp_vertex {node};
  while(temp_vertex->right_child)
    temp_vertex = temp_vertex->right_child;
  // splay(temp_vertex);
  return temp_vertex->element;
}

//template <typename T>
//void SplayTree<T>::makeEmpty() {

//}

template <typename T>
void SplayTree<T>::printTree() const {
  printTree(root);
}

template <typename T>
void SplayTree<T>::printTree(Vertex* node) {
  if(node->left_child)
    printTree(node->left_child);
  if(node)
    std::cout << node->element << "\n";
  if(node->right_child)
    printTree(right_child);
}

template <typename T>
void SplayTree<T>::rightRotate(Vertex* node) {
  if (!node)
    return;

  Vertex* rotate_node {node->left_child};
  if(rotate_node) {
    node->left_child = rotate_node->right_child;
    rotate_node->right_child = node;
    rotate_node->parent = node->parent;
  }
  if(!node->parent)
    rotate_node = root;
  else if (node->parent->left_child = node)
    node->parent->left_child = rotate_node;
  else
    node->parent->right_child = rotate_node;

  node->parent = rotate_node;
  
}

template <typename T>
void SplayTree<T>::leftRotate(Vertex* node) {
  if (!node)
    return;

  Vertex* rotate_node {node->right_child};
  if(rotate_node) {
    node->right_child = rotate_node->left_child;
    rotate_node->left_child = node;
    rotate_node->parent = node->parent;
  }
  if(!node->parent)
    rotate_node = root;
  else if (node->parent->left_child = node)
    node->parent->left_child = rotate_node;
  else
    node->parent->right_child = rotate_node;

  node->parent = rotate_node;
}


//WIP
template <typename T> 
void SplayTree<T>::splay(T element_in) {
  if(!contains(element_in))
    return;
  
  Vertex* splay_vertex {findVertex(element_in)};
  
  if (splay_vertex == root)
    return;
  
  while(splay_vertex != root) {
    if(splay_vertex->parent == root &&
       splay_vertex->parent->left_child == splay_vertex) {
	rightRotate(splay_vertex->parent);
      }
    else if (splay_vertex->parent == root &&
	     splay_vertex->parent->right_child == splay_vertex) {
	leftRotate(splay_vertex->parent);
      }
    else if (splay_vertex->parent->left_child == splay_vertex &&
	     splay_vertex->parent->parent->left_child == splay_vertex->parent) {
	rightRotate(splay_vertex->parent->parent);
	rightRotate(splay_vertex->parent);
      }
    else if (splay_vertex->parent->right_child == splay_vertex &&
	     splay_vertex->parent->parent->right_child == splay_vertex->parent){
	leftRotate(splay_vertex->parent->parent);
	leftRotate(splay_vertex->parent);
      }
    else if (splay_vertex->parent->left_child == splay_vertex &&
	     splay_vertex->parent->parent->right_child ==
	     splay_vertex->parent->parent) {
	rightRotate(splay_vertex->parent);
	leftRotate(splay_vertex->parent);
      }
    else if (splay_vertex->parent->right_child == splay_vertex &&
	     splay_vertex->parent->parent->left_child ==
	     splay_vertex->parent->parent) {
	leftRotate(splay_vertex->parent);
	rightRotate(splay_vertex->parent);
      }
    else
      std::cerr << "Error in splay() if this prints!\n";
    

  }
}
//seems ok
template <typename T> 
Vertex* SplayTree<T>::findVertex(T element_in) {
  Vertex* tempVertex = root;
  while(tempVertex->element != element_in && tempVertex != nullptr) {
    if(tempVertex->element < element_in)
      tempVertex = tempVertex->left_child;
    else 
      tempVertex = tempVertex->right_child;
  }
  return tempVertex;
    
}

template <typename T>
void SplayTree<T>::clear(Vertex* node) {
  if (node->left) 
    clear(node->left);
  if (node->right)
    clear(node->right);
  if(node)
    delete node;
  --node_count_;
}

template <typename T>
const SplayTree<T>::SplayTree& operator=(const SplayTree& other) {
  if(this != &other) {
    clear(root);
    root = copy(other.root);
  }
  return *this;
}

template <typename T> 
Vertex* SplayTree::copy(Vertex* old) {
  if (!old)
    return nullptr;
  else {
    Vertex* new_vertex{new Vertex(old->element,
				  copy(old->left_child),
				  copy(old->right_child))};
    if(new_vertex->left_child)
      new_vertex->left_child->parent = new_vertex;
    if(new_vertex->right_child)
      new_vertex->right_child->parent = new_vertex;
    return new_vertex;
  }
}
