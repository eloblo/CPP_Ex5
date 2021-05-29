#pragma once

#include <iostream>
#include <stdexcept>

namespace ariel{
	template<typename T> class BinaryTree{
		private:
			//the nodes of the tree
			struct Node{
				Node *parent = nullptr;   //parent node
				Node *left = nullptr;     //left child
				Node *right = nullptr;    //right child
				T value;                  //the value of node
				Node(T& val, Node *p = nullptr , Node *l = nullptr, Node *r = nullptr) : parent(p), value(val), left(l), right(r) {}
			};
			
			Node *root = nullptr;   //current root
			
			//search for the first occurence of val in the tree in a pre order iteration
			Node* find(const T& val, Node* node){
				Node* res = nullptr;          //the node holding the value
				if(node != nullptr){
					if(node->value == val){ return node;}    //check current node 
					if(node->left != nullptr){ 
						res = find(val, node->left);     //check left child
						if(res){ return res;}
					}
					if(node->right != nullptr){             //check right child
						res = find(val, node->right);
						if(res){ return res;}
					}
				}
				return res;
			}
			//in a post order delete all nodes
			void clear(Node* node){
				if(node != nullptr){
					if(node->left != nullptr){ clear(node->left);}
					if(node->right != nullptr){ clear(node->right);}
					delete node;
				}
			}
			//in a pre order copy the tree from src to dst
			void copy(Node* dst, Node* src){
				if(src != nullptr){
					if(src->left != nullptr){ 
						dst->left = new Node(src->left->value,dst);    //create a left child node for dst with src's left child's value
						copy(dst->left, src->left);
					}
					if(src->right != nullptr){ 
						dst->right = new Node(src->right->value,dst);  //create a right child node for dst with src's right child's value
						copy(dst->right, src->right);
					}
				}
			}
			//convert the tree to a text form in a in order format
			void print_tree(Node *node, std::ostream& os , int space=0) const{ 
				if (node != nullptr){
			    		space += 4;                             //increase distance between levels  
			    		print_tree(node->right, os, space); 
			    		os << '\n'; 
			    		for (int i = 4; i < space; i++){        //print the distance from node to node
						os << ' '; 
					}
			    		os << node->value << '\n'; 
			    		print_tree(node->left, os, space); 
			    	}
			}
		public:
			BinaryTree() = default;
			BinaryTree<T>(BinaryTree<T> &bt){   //copy constructor
				//if bt is not empty copy the nodes
				if(bt.root != nullptr){
					root = new Node(bt.root->value);
					copy(root, bt.root);
				}
				else{
					root = nullptr;
				}
			}
			BinaryTree<T>(BinaryTree<T> &&bt) noexcept{     //move constructor
				//if bt is not empty copy the nodes
				if(bt.root != nullptr){
					root = new Node(bt.root->value);
					copy(root, bt.root);
				}
				else{
					root = nullptr;
				}
				bt.clear(bt.root);   //delete all bt's nodes
				bt.root = nullptr;
			}
			BinaryTree<T>& operator= (const BinaryTree<T> &other){   //copy operator 
				//check for self copieng
				if(this == &other){
					return *this;
				}
				//delete the tree's nodes and copy
				if(other.root != nullptr){
					this->clear(root);
					root = new Node(other.root->value);
					copy(root, other.root);
				}
				else{
					root = nullptr;
				}
				return *this;
			}
			BinaryTree<T>& operator= (BinaryTree<T> &&other) noexcept{   //move operator
				//clear this tree and copy
				if(other.root != nullptr){
					this->clear(root);
					root = new Node(other.root->value);
					copy(root, other.root);
				}
				else{
					root = nullptr;
				}
				//clear the other tree
				other.clear(other.root);
				other.root = nullptr;
				return *this;
			}
			class pre_iterator{   //iterator for pre oreder iteration
				private:
					Node *current_node = nullptr;   //current node pointer
				public:
					pre_iterator(Node* ptr = nullptr) : current_node(ptr){}
					pre_iterator(const pre_iterator &other) : current_node(other.current_node){} //copy constructor
					pre_iterator(pre_iterator &&other) noexcept{   //move constructor
						current_node = other.current_node;
						other.current_node = nullptr;
					}
					pre_iterator& operator= (const pre_iterator &other){   //copy operator
						if(this != other){
							current_node = other.current_node;
						}
						return *this;
					}
					pre_iterator& operator= (pre_iterator &&other) noexcept{   //move operator
						current_node = other.current_node;
						other.current_node = nullptr;
						return *this;
					}
					T& operator*() const {
						return current_node->value;
					}
					T* operator->() const {
						return &(current_node->value);
					}
					pre_iterator& operator++() {
						//if not at end
						if(current_node != nullptr){
							//if there is a left child move left
							if(current_node->left != nullptr){ current_node = current_node->left;}
							//if there is a right child move right
							else if(current_node->right != nullptr){ current_node = current_node->right;}
							//search for a right brother/uncle and point to him
							else if(current_node->parent != nullptr){ 
								while(current_node->parent != nullptr){
									if(current_node->parent->right != nullptr && current_node->parent->right != current_node){ 
										current_node = current_node->parent->right;
										return *this;
									}
									current_node = current_node->parent;
								}
								//if there are no right brothers then we reached the end
								current_node = nullptr;
							}
							else{ current_node = nullptr;}    //there is only root node
						}
						return *this;
					}
					pre_iterator operator++(int dummy) {
						pre_iterator tmp = *this;
						++*this;
						return tmp;
					}
					bool operator==(const pre_iterator& other) const {
						return current_node == other.current_node;
					}
					bool operator!=(const pre_iterator& other) const {
						return !(*this == other);
					}
					~pre_iterator() = default;
			};
			class in_iterator{     //iterator for in oreder iteration
				private:
					Node *current_node = nullptr;   //current node pointer
				public:
					in_iterator(Node* ptr = nullptr) : current_node(ptr){}
					in_iterator(const in_iterator &other) : current_node(other.current_node){}   //copy constructor
					in_iterator(in_iterator &&other) noexcept{      //move constructor
						current_node = other.current_node;
						other.current_node = nullptr;
					}
					in_iterator& operator= (const in_iterator &other){     //copy operator
						if(this != other){
							current_node = other.current_node;
						}
						return *this;
					}
					in_iterator& operator= (in_iterator &&other) noexcept{    //move operator
						current_node = other.current_node;
						other.current_node = nullptr;
						return *this;
					}
					T& operator*() const {
						return current_node->value;
					}
					T* operator->() const {
						return &(current_node->value);
					}
					in_iterator& operator++() {
						//if not at end
						if(current_node != nullptr){
							if(current_node->right != nullptr){                          //if there a right child
								current_node = current_node->right;                  //move right
								if(current_node->left != nullptr){                   //if he has a left child
									while(current_node->left != nullptr){        //move as left as possible
										current_node = current_node->left;
									}
								}
							}
							else if(current_node->parent != nullptr){                            //if next iteration is up the tree
								while(current_node->parent != nullptr){                      //move up
									if(current_node->parent->right != current_node){     //if moving from left child
										current_node = current_node->parent;         //return the parent of the left child
										return *this;
									}
									current_node = current_node->parent; 
								}
								current_node = nullptr;   //if can only move up from right childrens we reached the end
							}
							else{ current_node = nullptr;}    //there is only root node
						}
						return *this;
					}
					in_iterator operator++(int dummy) {
						in_iterator tmp = *this;
						++*this;
						return tmp;
					}
					bool operator==(const in_iterator& other) const {
						return current_node == other.current_node;
					}
					bool operator!=(const in_iterator& other) const {
						return !(*this == other);
					}
					~in_iterator() = default;
			};
			class post_iterator{    //iterator for in oreder iteration
				private:
					Node *current_node = nullptr;    //current node pointer
				public:
					post_iterator(Node* ptr = nullptr) : current_node(ptr){}
					post_iterator(const post_iterator &other) : current_node(other.current_node){}     //copy constructor
					post_iterator(post_iterator &&other) noexcept{      //move constructor
						current_node = other.current_node;
						other.current_node = nullptr;
					}
					post_iterator& operator= (const post_iterator &other){       //copy operator
						if(this != other){
							current_node = other.current_node;
						}
						return *this;
					}
					post_iterator& operator= (post_iterator &&other) noexcept{   //move operator
						current_node = other.current_node;
						other.current_node = nullptr;
						return *this;
					}
					T& operator*() const {
						return current_node->value;
					}
					T* operator->() const {
						return &(current_node->value);
					}
					post_iterator& operator++() {
						//if not at the end
						if(current_node != nullptr){
							if(current_node->parent != nullptr){                                                                    
								if(current_node->parent->right != nullptr && current_node->parent->right != current_node){     //if there is a right brother
									current_node = current_node->parent->right;                                            //point to him
									while(current_node->left != nullptr || current_node->right != nullptr){                //move to his most left leaf
										while(current_node->left != nullptr){                                          //moves to the most left child
											current_node = current_node->left;
										}
										if(current_node->right != nullptr){ current_node = current_node->right;}       //if the child has a right child move right
									}
								}
								else{ current_node = current_node->parent;}   //if there is no right brother move up
							}
							else{ current_node = nullptr;}    //there is only root node
						}
						return *this;
					}
					post_iterator operator++(int dummy) {
						post_iterator tmp = *this;
						++*this;
						return tmp;
					}
					bool operator==(const post_iterator& other) const {
						return current_node == other.current_node;
					}
					bool operator!=(const post_iterator& other) const {
						return !(*this == other);
					}
					~post_iterator() = default;
			};
			//sets a new value to root
			BinaryTree<T>& add_root(const T &val){
				//if there is no root create a new node  
				if(root == nullptr){
					T copy = val;
					root = new Node{copy};
					}
				else{
					root->value = val;
				}
				return *this;
			}
			//sets the value of the left child of the first iteration of given node
			BinaryTree<T>& add_left(const T &node, const  T &val){
				Node* n = find(node, root);                               //get a pointer to the first iteration
				if(n != nullptr){                                         //if the node exist
					if(n->left != nullptr){ n->left->value = val;}    //set the value of the child
					else{                                             //create a new left child if there is none
						T copy = val;
						n->left = new Node{copy,n};
					}
					return *this;
				}
				throw std::invalid_argument("no such element in the tree\n");
			}
			//sets the value of the right child of the first iteration of given node
			BinaryTree<T>& add_right(const T &node, const  T &val){
				Node* n = find(node, root);                               //get a pointer to the first iteration
				if(n != nullptr){                                         //if the node exist
					if(n->right != nullptr){ n->right->value = val;}  //set the value of the child
					else{                                             //create a new right child if there is none
						T copy = val;
						n->right = new Node{copy,n};
					}
					return *this;
				}
				throw std::invalid_argument("no such element in the tree\n");
			}
			//return the first node in pre order iteration, which is the root
			pre_iterator begin_preorder(){
				return pre_iterator{root};
			}
			//return the first node in pre order iteration, which is the null
			pre_iterator end_preorder(){
				return pre_iterator{nullptr};
			}
			//return the first node in in order iteration
			in_iterator begin_inorder(){
				if(root == nullptr){ return nullptr;}    //search for the most left child
				Node* tmp = root;
				while(tmp->left != nullptr){
					tmp = tmp->left;
				}
				return in_iterator{tmp};
			}
			//return the first node in in order iteration, which is the null
			in_iterator end_inorder(){
				return in_iterator{nullptr};
			}
			//return the first node post in order iteration
			post_iterator begin_postorder(){
				if(root == nullptr){ return nullptr;}       //search for the most left leaf
				Node* tmp = root;
				while(tmp->left != nullptr || tmp->right != nullptr){
					while(tmp->left != nullptr){                      //move as left as possible
						tmp = tmp->left;
					}
					if(tmp->right != nullptr){ tmp = tmp->right;}     //if can only move right take one step right
				}
				return post_iterator{tmp};
			}
			//return the first node in post order iteration, which is the null
			post_iterator end_postorder(){
				return post_iterator{nullptr};
			}
			//default begin iterator, iterate in a in order itaretions 
			in_iterator begin(){
				return begin_inorder();
			}
			//default end iterator, iterate in a in order itaretions 
			in_iterator end(){
				return end_inorder();
			}
			~BinaryTree(){
				clear(root);   //before deconstructing delete all nodes
			}
			friend std::ostream& operator<< (std::ostream& os, const BinaryTree<T>& btree){
				btree.print_tree(btree.root, os);
				return os;
			}
	};
}
