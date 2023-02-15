// priorityqueue.h
//
// Author: Edward Plesa, Spring 2021, Proj. 5
#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  //  used to build BST
        T value;  //  stored data for the p-queue
        bool dup;  //  marked true when there are duplicate priorities
        NODE* parent;  //  links back to parent
        NODE* link;  //  links to linked list of NODES with duplicate priorities
        NODE* left;  //  links to left child
        NODE* right;  //  links to right child
    };
    NODE* root;  //  pointer to root node of the BST
    int size;  //  # of elements in the pqueue
    NODE* curr;  //  pointer to next item in pqueue (see begin and next)
    //
    //  builds a string to return to the toString() method recursively inorder
    //
    void recursiveStringBuilder(NODE* node, ostream& output) {
    	if (node == nullptr) {
    		return;
    	}
    	recursiveStringBuilder(node->left, output);
    	output << node->priority << " value: " << node->value << endl;
    	if (node->link != nullptr) {
    		recursiveStringBuilder(node->link, output);
    	}
    	recursiveStringBuilder(node->right, output);
    }
    //
    //	recursively clears the tree from the input node.
    //
    void clearTreeHelper(NODE* node) {
    	if (node == nullptr) return;
    	clearTreeHelper(node->left);
    	clearTreeHelper(node->right);
    	clearTreeHelper(node->link);
    	delete node;
    	node = nullptr;
    }
    //
    //	deep copies the tree using preOrder traversal starting from another tree
    //
    NODE* copyPreOrder(NODE* other) {
    	if (other == nullptr) return other;
    	NODE* newNode = new NODE();
    	newNode->priority = other->priority;
    	newNode->value = other->value;
    	newNode->link = copyPreOrder(other->link);
    	newNode->left = copyPreOrder(other->left);
    	newNode->right = copyPreOrder(other->right);
    	return newNode;
    }
    //
    //	returns the next inorderSuccessor and updates curr to point at it
    //
    NODE* inorderSuc() {
    	if (curr->link != nullptr) {
    		return curr->link;
    	}
    	else {
    		if (curr->dup == true) {
    			NODE* p = curr->parent;
    			while(curr->priority == p->priority) {
	    			curr = p;
	    			if (p->parent == nullptr) break;
	    			p = p->parent;
	    		}
    		}
    	}
    	if (curr->right != nullptr) {
    		curr = curr->right;
        	while (curr->left != nullptr) {
        		curr = curr->left;
	        }
	        return curr;
    	}
    	if (curr->right == nullptr) {
    		NODE* p = curr->parent;
	    	while(p != nullptr && curr == p->right) {
	    		curr = p;
	    		p = p->parent;
	    	}
	    	return p;
    	}
    	return nullptr;
    }
    //
    //	returns true if both trees are equal; false if not equal
    //
    bool isequal(NODE* mycur, NODE* othercur) const{
    	if (mycur == nullptr && othercur == nullptr) return true;
    	else if (mycur == nullptr) return false;
    	else if (othercur == nullptr) return false;
    	else {
    		return (mycur->priority == othercur->priority &&
    				mycur->value == othercur->value       &&
    				isequal(mycur->link, othercur->link)   &&
    				isequal(mycur->left, othercur->left)   &&
    				isequal(mycur->right, othercur->right));
    	}
    }
public:
    //
    //  default constructor:
    //
    //  Creates an empty priority queue.
    //  O(1)
    //
    priorityqueue() {
        root = nullptr;
        size = 0;
        curr = nullptr;
    }
    //
    //  operator=
    //
    //  Clears "this" tree and then makes a copy of the "other" tree.
    //  Sets all member variables appropriately.
    //  O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
        if (this == &other) {
    		return *this;
    	}
    	clearTreeHelper(this->root);
    	this->root = nullptr;
    	this->size = other.size;
        this->root = copyPreOrder(other.root);
        return *this;
    }
    //
    //  clear:
    //
    //  Frees the memory associated with the priority queue but is public.
    //  O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        clearTreeHelper(root);
        root = nullptr;
        size = 0;
        curr = nullptr;
    }
    //
    //  destructor:
    //
    //  Frees the memory associated with the priority queue.
    //  O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
        if (root != nullptr) {
        	clearTreeHelper(root);
        	root = nullptr;
        	curr = nullptr;
        }
    }
    //
    //  enqueue:
    //
    //  Inserts the value into the custom BST in the correct location based on
    //  priority.
    //  O(logn + m), where n is number of unique nodes in tree and m is number of
    //  duplicate priorities
    //
    void enqueue(T value, int priority) {
        NODE* prev = nullptr;
        NODE* cur = root;
        while (cur != nullptr) {
        	if (priority == cur->priority) {
        		prev = cur;
        		cur = cur->link;
        	} else if (priority < cur->priority) {
        		prev = cur;
        		cur = cur->left;
        	} else if (priority > cur->priority) {
        		prev = cur;
        		cur = cur->right;
        	}
        }
        NODE* n  = new NODE();
        n->priority = priority;
        n->value = value;
        n->link = nullptr;
        n->parent = nullptr;
        n->left = nullptr;
        n->right = nullptr;
        if (prev == nullptr) {
        	n->dup = false;
        	n->parent = nullptr;
        	root = n;
        } else if (priority < prev->priority) {
        	n->dup = false;
        	n->parent = prev;
        	prev->left = n;
        } else if (priority > prev->priority) {
        	n->dup = false;
        	n->parent = prev;
        	prev->right = n;
        } else if (priority == prev->priority) {
        	n->dup = true;
        	n->parent = prev;
        	prev->link = n;
        }
        size++;
    }
    //
    //  dequeue:
    //
    //  returns the value of the next element in the priority queue and removes
    //  the element from the priority queue.
    //  O(logn + m), where n is number of unique nodes in tree and m is number of
    //  duplicate priorities
    //
    T dequeue() {
        T valueOut;
        NODE* cur = root;
        if (size == 0) {
        	return valueOut;
        }
        while (cur->left != nullptr) {
        	cur = cur->left;
        }
        valueOut = cur->value;
        if (size == 1) {
        	size = 0;
        	root = nullptr;
        	delete cur;
        	cur = nullptr;
        	return valueOut;
        }
        if (cur->link != nullptr) {
        	NODE* temp = cur->link;
        	
        	if (cur->parent == nullptr) {
        		if (root->right != nullptr) {
        			root->right->parent = temp;
        		}
        		temp->right = root->right;
        		temp->parent = nullptr;
        		root = temp;
        		
        	}
        	else {
	    		cur->parent->left = temp;
	    		temp->parent = cur->parent;
	    		temp->right = cur->right;
	        }
    	}
    	else {
    		if (cur->right != nullptr) {
    			NODE* temp = cur->right;
    			if (cur->parent == nullptr) {
    				temp->parent = nullptr;
    				root = temp;
    			}
    			else {
    				cur->parent->left = temp;
    				temp->parent = cur->parent;
		        	
    			}
	    	}
	    	if (cur->right == nullptr) {
	    		cur->parent->left = nullptr;
	    	}
    	}
        delete cur;
        cur = nullptr;
        size--;
        return valueOut;
    }
    //
    //  Size:
    //
    //  Returns the # of elements in the priority queue, 0 if empty.
    //  O(1)
    //
    int Size() {
        return this->size;
    }
    //
    //  begin
    //
    //  Resets internal state for an inorder traversal.  After the
    //  call to begin(), the internal state denotes the first inorder
    //  node; this ensure that first call to next() function returns
    //  the first inorder node value.
    //
    //  O(logn), where n is number of unique nodes in tree
    //
    //  Example usage:
    //     pq.begin();
    //     while (tree.next(value, priority)) {
    //       cout << priority << " value: " << value << endl;
    //     }
    //     cout << priority << " value: " << value << endl;
    void begin() {
        curr = root;
        while (curr->left != nullptr) {
        	curr = curr->left;
        }
    }
    //
    //  next
    //
    //  Uses the internal state to return the next inorder priority, and
    //  then advances the internal state in anticipation of future
    //  calls.  If a value/priority are in fact returned (via the reference
    //  parameter), true is also returned.
    //
    //  False is returned when the internal state has reached null,
    //  meaning no more values/priorities are available.  This is the end of the
    //  inorder traversal.
    //
    //  O(logn), where n is the number of unique nodes in tree
    //
    //  Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {
    	priority = curr->priority;
    	value = curr->value;
    	curr = inorderSuc();  //  advance curr
    	if (curr != nullptr) {
    		return true;
    	}
    	else {
    		return false;
    	}
    }
    //
    //  toString:
    //
    //  Returns a string of the entire priority queue, in order.  Format:
    //  "1 value: Ben
    //   2 value: Jen
    //   2 value: Sven
    //   3 value: Gwen"
    //
    string toString() {
        stringstream ss;
    	recursiveStringBuilder(root, ss);
        return ss.str();
    }
    //
    //  peek:
    //
    //  returns the value of the next element in the priority queue but does not
    //  remove the item from the priority queue.
    //  O(logn + m), where n is number of unique nodes in tree and m is number of
    //  duplicate priorities
    //
    T peek() {
        T valueOut;
        
        NODE* cur = root;
        
        if (size == 0) {
        	return valueOut;
        }
        
        while (cur->left != nullptr) {
        	cur = cur->left;
        }
        
        valueOut = cur->value;
        
        
        return valueOut;
    }
    //
    //  ==operator
    //
    //  Returns true if this priority queue as the priority queue passed in as
    //  other.  Otherwise returns false.
    //  O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {
        return isequal(this->root, other.root);
    }
    //
    //  getRoot - Do not edit/change!
    //
    //  Used for testing the BST.
    //  return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
