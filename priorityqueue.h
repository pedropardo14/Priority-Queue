// priorityqueue.h
//
//  Author: Pedro Pardo
//  IDE: VsCode on MacOS
//
// This project deals with the idea of BST. But instead of a regular tree we have a third dimention of linkage.
// Within this file is all the necessary function that would make this work.
// It takes in data to create the tree allong with setting the value and priority to create a priority queue 
// in the form of a binary search tree.

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)

    void _toString(NODE* node, ostream& output){ //makes a string based on the bst
        if (node == nullptr) { //return if tree is empty
            return;
        } 
        else{ //if tree is populated
            _toString(node->left, output); //traverses left
            if (node->dup == true) { //when there is a link present 
                output << node->priority << " value: " << node->value << "\n";
                NODE* temp = node->link; //make temp to traverse through linked list
                while (temp) { //keeps traversing if there is a link
                    output << temp->priority << " value: " << temp->value << "\n";
                    temp = temp->link;
                }
            }
            if (node->dup != true) { //when there isnt a link
                output << node->priority << " value: " << node->value << "\n";
            }
            _toString(node->right, output); //traverses right 
        }
    }
    
    void _clear(NODE* node) { //helper function to clear a bst
        if (node == nullptr) { //when tree is empty return
            return;
        } 
        else {
            _clear(node->left); //traverse left
            _clear(node->right); //traverse right
            if (node->dup == true) { //when there is a link
                NODE* cur = node->link; //temp for link
                NODE* next; //temp for the next lin
                while (cur != nullptr) { //when the link isnt null
                   next = cur->link; //sets next node to the link
                   delete cur; //delets memory for the link node
                   cur = next; //sets curr to next
                   size--; //decreases size
                }
            }
            delete node; //deletes the node
            size--; //decrease size
        }
    }

    NODE* _copy(NODE* original, NODE* parent){ //helper function for copy constructor
        if (original == nullptr) { //return when BST is empty
            return nullptr;
        }
        else{ //if bst isnt empty
            NODE* newNode = new NODE; //creates a new node for copy
            newNode->priority = original->priority;
            newNode->value = original->value;
            newNode->dup = original->dup;
            newNode->parent = parent;
            newNode->link = nullptr;
            newNode->left = nullptr;
            newNode->right = nullptr;
            size++;

            if(original->dup == true){ //checks if the first bst contains a link
                NODE* prev = newNode; //sets new node for previous traversal
                NODE* cur = original->link; //sets current to the link node
                NODE* next = nullptr;
                while (cur != nullptr) { //when there is still a link when traversing through the list
                    next = cur->link; //setting next to the next link
                    NODE* newLinkedNode = new NODE; //sets a new node for the copy of a linked list
                    //copy over all the values of nodes
                    newLinkedNode->priority = cur->priority;
                    newLinkedNode->value = cur->value;
                    newLinkedNode->dup = true;
                    newLinkedNode->parent = prev;
                    newLinkedNode->link = nullptr;
                    prev->link = newLinkedNode;
                    prev = newLinkedNode;
                    cur = cur->link;
                    size++; //increase size 
                }
            }
            newNode->left = _copy(original->left, newNode); //traverses through the left 
            newNode->right = _copy(original->right, newNode); //travserses through the right
            return newNode; //returns the copied nodes
        }
    }

    const bool _equal(NODE* curr, const NODE* othercurr) const { //helper funciton for ==constructor
        if (curr == nullptr && othercurr == nullptr) { //checking if both trees are empty
            return true;
        } 
        else if (curr == nullptr) { //checking if one tree is empty
            return false;
        } 
        else if (othercurr == nullptr) { //checking if the other three is empty
            return false;
        } 
        else {
            if ((curr->link == nullptr && othercurr->link != nullptr) || (curr->link != nullptr && othercurr->link == nullptr)) { //checking if the one has links and the other doesnt
                return false;
            }
            else{
                NODE* currTemp = curr; //sets temp for current
                const NODE* otherTemp = othercurr; //sets temp for other tree
                while (currTemp != nullptr) { //check if the first tree doesnt run into any nullptrs
                    if (currTemp->value != otherTemp->value) { //if the values dont match up
                        return false;
                    }
                    else if(currTemp->value == otherTemp->value) { //if the values do match up for link
                        currTemp = currTemp->link;
                        otherTemp = otherTemp->link;
                    }
                }
            }
            if(_equal(curr->left, othercurr->left) && (curr->value == othercurr->value) && (_equal(curr->right, othercurr->right))) { //if every think for the trees match up
                return true;
            } 
            else { //if something doesnt match 
                return false;
            }
        }

    }

    T _peek(NODE *node){ //helper function for peek
        if (node->left == NULL){ //checking if the left nost node is empty
            return node->value; //returns that value
        }
        return _peek(node->left); //keep traversing until null
    }



public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //

    priorityqueue() { //sets all values to blank so they can be used fresh
        root = nullptr; //sets the root to null
        curr = nullptr; //sets curr node to null
        size = 0; //sets size to 0
    }
    
    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //

    priorityqueue& operator=(const priorityqueue& other) { //this function will copy a BST to another one making it a duplicate
        clear();   //clear tree
        NODE *original = other.root; //set temp node to the other root
        NODE *newCopy = nullptr;
        newCopy = _copy(original, newCopy); //creates a copt of the tree based on this new node and the other tree
        this->root = newCopy; //makes the main root into the new bst
        return *this; //returns the copied tree
    }
    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //


    void clear() { //main call for delete
        _clear(root); //calls the helper function to clear the tree staring from the root
        size = 0;
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() { //i dont know how too get this to work LMAO 

        /* Calling clear gives me an bad malloc error?????????????????????*/
        // clear();
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    void enqueue(T value, int priority) { //this function will create the tree and the links if found
        NODE *prev = nullptr; //sets a node for storing the previous node for parent use
        NODE *cur = root; //sets all values to whats called within the function

        while(cur != nullptr){ //when the cur node lookin at isnt null
            if(priority == cur->priority){ //check for dups
                cur->dup = true; //sets the bool for node to true
                NODE* temp = cur;
                while (temp->link != nullptr) { //while the temp node isnt null
                    temp = temp->link; //keep adding to the link until done
                }
                NODE* n = new NODE; //create another temp node ans set its values for duplicates
                n->priority = priority;
                n->value = value;
                n->dup = true;
                n->link = nullptr;
                n->left = nullptr;
                n->right = nullptr;
                n->parent = temp; //set parent for the temp
                temp->link = n;
                size++; //increase size 
                return;
            }
            else if(priority < cur->priority){ //goes left
                prev = cur;//sets the previous to current
                cur = cur->left; //sets curr equal to the left value
            }
            else if(priority > cur->priority){ //goes right
                prev = cur;//sets the previous to current
                cur = cur->right; //sets curr equal to the right value
            }
        }

        NODE* n = new NODE; //creates anther temp node for use
        n->priority = priority;
        n->value = value;
        n->dup = false;
        n->link = nullptr;
        n->left = nullptr;
        n->right = nullptr;
        n->parent = prev; //set parent to node just looked at

        if(prev == nullptr){ //if there isnt any nodes 
            root = n; //set root equal to this temp node
        }
        else if(priority < prev->priority){ //if value is less then the previous
            prev->left = n; //set the value to the left
        }
        else if(priority > prev->priority){ //if value is more then the other
            prev->right = n; //set it to the right
        }
        size++; //increase size 
    }
    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //

    T dequeue() {
        T valueOut;
        int priority, value = 0;
        if((size == 0) || (root = nullptr)){ //empty tree 
            return;
        }
        this->begin(); //points to the first node gotten by begin

        if(curr->dup != true){ //checks if dups arent present
            if(curr == root){ //when curr is set to the root
                if(curr->left == nullptr && curr->right == nullptr){ //when both leaf nodes are null
                    root = nullptr; //since there isnt any leaf nodes its empty
                    valueOut = curr->value; //output value to root
                    delete curr; //delete node
                    size--; //decrease size 
                    return valueOut; //return rhe value
                }
                else if(curr->left == nullptr && curr->right == nullptr){//when both leaf nodes arent null
                    valueOut = curr->value;
                    NODE* prev = curr;
                    NODE* newNode = this->next(); //sets temp node to the next node
                    root = newNode; //root is set to temp
                    newNode->parent = prev->parent; //sets parent to the previous 
                    if(newNode->left == nullptr && newNode->right == nullptr){ //when both sides are empty
                        delete prev; //delete the prev note
                        return valueOut;
                    }
                    else if (newNode->left != nullptr && newNode->right != nullptr) { //when the leaf nodes arent empty
                        this->begin(); //sets the first node
                        delete prev; //deletes the previous
                        return valueOut;
                    }
                }
            }
            if(curr->left ==nullptr && curr->right != nullptr){ //when curr is not  
                valueOut = curr->value; //sets value to current value
                NODE* prev = curr;
                NODE* newNode = this->next();
                if(newNode->right == prev){ //when temp node->right is equal to previous
                    newNode->right = nullptr;
                }
                if(newNode->left == prev){//when temp node->left is equal to  
                    newNode->left = nullptr;
                }
                delete prev; //delete prev 
                return valueOut;
            }
            else if(curr->left == nullptr && curr->right == nullptr){ //when root has leaf nodes
                valueOut = curr->value;
                NODE* prev = curr;
                NODE* newNode = this->next(); //newnode is set to next node
                if(prev->parent->right == prev){ //when the right value is set to prev
                    prev->parent->right = newNode;
                    newNode->parent = prev->parent;
                }
                if(prev->parent->left == prev){ //when lift side is equal to previous
                    prev->parent->left = newNode;
                    newNode->parent = prev->parent;
                }
                delete prev; //delete node
                return valueOut;
            }
        }      
        else if (curr->dup == true){ // dup is true
            NODE* prev = curr;
            NODE* newNode = this->next(); //sets temp to next node
            newNode->parent = prev->parent;
            newNode->right = prev->right;
            newNode->left = prev->left;
            if (prev->parent == nullptr) { //when parent is null
                root = newNode;
            }
            else if (prev->parent->right == prev) { //when the right of parent is previous
                prev->parent->right = newNode;
            }
            else if (prev->parent->left == prev) { //when the left of parent is previous
                prev->parent->left = newNode;
            } 
            else{
                prev->parent->left = nullptr;
                prev->parent->right = nullptr;
            }

            if (newNode->link == nullptr) { //link is null
                newNode->dup = false;
            } 
            else { //when link isnt null
                newNode->link->parent = newNode;
            }

            valueOut = prev->value;
            delete curr; //delete node
            return valueOut;
        }  
        return valueOut;
    }
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        return size; //return the size of BST
    }
    
    //
    // begin:
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;

    void begin() {
        NODE *temp = root; //set temp node to root
        curr = nullptr; //set curr to nothing for use
        if (root == nullptr){ //tree is empty
            curr = nullptr;
        }
        if(size == 0) { //size is empty
            curr = nullptr;
        }
        else{ //when left subtree isnt empty
            if (temp->left != nullptr) {
                while(temp->left != nullptr) { //continue until it hits nullptr on the left
                    curr = temp->left;
                    temp = temp->left;
                }
            } 
            else if (temp->left == nullptr) { //if there isnt any more left leaf nodes
                curr = temp;
            }
        }
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //

    bool next(T& value, int &priority) {
        NODE *temp = curr; //set temp equal to the current node
        if(temp != nullptr){
            if (temp->dup == true){ //checks for linked list
                if (temp->link == nullptr) { //run until null on linked list
                    value = temp->value;// set value to temp value
                    priority = temp->priority; //set priority to temp priority
                    NODE* parent = temp->parent; //set parent node to temp parent
                    while (parent->dup != false) { //runs when there isnt a link
                        temp = parent;
                        parent = parent->parent;
                    }
                    curr = temp->parent; //set current to parent
                    return true;
                }
                else if (temp->link != nullptr) { //when there isnt a link
                    value = temp->value;
                    priority = temp->priority;
                    curr = temp->link;
                    return true;
                }
            }
            value = curr->value; //set value to currents value
            priority = curr->priority; //set priority to currents value
            if (temp->right == nullptr) { //when right hits null
                NODE* parent = temp->parent;
                while (temp->priority > parent->priority) { //when the parent is smaller then temp
                    temp = parent;
                    if (parent->parent != nullptr) { //when parent isnt null
                        parent = parent->parent;
                    } 
                    else{ //when parent is null
                        return false;
                    }
                }
                curr = parent; //set curr to parent
                return true;
            }  
            else if (temp->right != nullptr) { //when right isnt null
                curr = temp->right; //set curr to the right leaf
                return true;
            }
        }
        return false;
    }
    
    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //

    string toString() {
        if (this->size == 0) { //when tree is empty
            return ""; //return empty string
        } 
        else{ //when tree is populated
            stringstream ss; 
            _toString(root, ss); //call the helper with root and the stringstream
            string str = ss.str();
            return str;
        }
    }
    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //

    T peek() {
        T valueOut;
        curr = root; //set curr to the root
        valueOut = _peek(curr); //set value to the helper return
        return valueOut; 
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST

    bool operator==(const priorityqueue& other) const {
        if (size != other.size){ // when size doesnt equal it wont equal
            return false;
        }
        else{
            return _equal(this->root, other.root); //run helper function
        }
    }

    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
