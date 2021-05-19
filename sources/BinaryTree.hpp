#pragma once

#include <iostream>

namespace ariel{
	template<typename T> class BinaryTree{
		private:
			struct Node{
				Node *left = nullptr;
				Node *right = nullptr;
				T value;
				Node(T& val, Node *l = nullptr, Node *r = nullptr) : value(val), left(l), right(r) {}
			};
			Node *root = nullptr;
			
			void clear(Node* node){
				if(node != nullptr){
					if(node->left != nullptr){ clear(node->left);}
					if(node->right != nullptr){ clear(node->right);}
					delete node;
				}
			}
		public:
			class pre_iterator{
				private:
					Node *current_node = nullptr;
				public:
					pre_iterator(Node* ptr = nullptr) : current_node(ptr){}
					T& operator*() const {
						return current_node->value;
					}
					T* operator->() const {
						return &(current_node->value);
					}
					pre_iterator& operator++() {
						return *this;
					}
					const pre_iterator operator++(int dummy) {
						pre_iterator tmp = *this;
						return tmp;
					}
					bool operator==(const pre_iterator& other) const {
						return current_node == other.current_node;
					}
					bool operator!=(const pre_iterator& other) const {
						return !(current_node == other.current_node);
					}
			};
			class in_iterator{
				private:
					Node *current_node = nullptr;
				public:
					in_iterator(Node* ptr = nullptr) : current_node(ptr){}
					T& operator*() const {
						return current_node->value;
					}
					T* operator->() const {
						return &(current_node->value);
					}
					in_iterator& operator++() {
						return *this;
					}
					const in_iterator operator++(int dummy) {
						in_iterator tmp = *this;
						return tmp;
					}
					bool operator==(const in_iterator& other) const {
						return current_node == other.current_node;
					}
					bool operator!=(const in_iterator& other) const {
						return !(current_node == other.current_node);
					}
			};
			class post_iterator{
				private:
					Node *current_node = nullptr;
				public:
					post_iterator(Node* ptr = nullptr) : current_node(ptr){}
					T& operator*() const {
						return current_node->value;
					}
					T* operator->() const {
						return &(current_node->value);
					}
					post_iterator& operator++() {
						return *this;
					}
					const post_iterator operator++(int dummy) {
						post_iterator tmp = *this;
						return tmp;
					}
					bool operator==(const post_iterator& other) const {
						return current_node == other.current_node;
					}
					bool operator!=(const post_iterator& other) const {
						return !(current_node == other.current_node);
					}
			};
			BinaryTree<T>& add_root(const T &val){
				if(root == nullptr){
					T tmp = val;
					root = new Node{tmp};
					}
				else{
					root->value = val;
				}
				return *this;
			}
			BinaryTree<T>& add_left(const T &node, const  T &val){
				if(root != nullptr){
					T tmp = val;
					root->left = new Node{tmp};
				}
				return *this;
			}
			BinaryTree<T>& add_right(const T &node, const  T &val){
				if(root != nullptr){
					T tmp = val;
					root->right = new Node{tmp};
				}
				return *this;
			}
			pre_iterator begin_preorder(){
				return pre_iterator{root};
			}
			pre_iterator end_preorder(){
				return pre_iterator{root};
			}
			in_iterator begin_inorder(){
				return in_iterator{root};
			}
			in_iterator end_inorder(){
				return in_iterator{root};
			}
			post_iterator begin_postorder(){
				return post_iterator{root};
			}
			post_iterator end_postorder(){
				return post_iterator{root};
			}
			in_iterator begin(){
				return in_iterator{root};
			}
			in_iterator end(){
				return in_iterator{root};
			}
			~BinaryTree(){
				clear(root);
			}
			friend std::ostream& operator<< (std::ostream& os, const BinaryTree<T>& btree){
				return os;
			}
	};
}
