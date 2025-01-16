//
//  SkipList.h
//  Skip_List
//
//  Copyright Â© Tali Moreshet. All rights reserved.
//
//
//  This is an implementation of a Skip List class, consisting of Linked Lists, which are made up of Nodes.
//  All classes are templated, such that their types may be provided at creation.
//  Nodes contain data (which doubles as key), and pointers to all directions.

#ifndef SkipList_h
#define SkipList_h

#include <iostream>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

template<class T>
class Node {
public:
    Node(const T& data);                            // constructor
    T data;                                         // node data, doubles as key
    Node<T> *next;                                  // node next pointer
    Node<T> *prev;                                  // node previous pointer
    Node<T> *up;                                    // node above pointer
    Node<T> *down;                                  // node below pointer
    void printData();                               // prints data value
    void print();                                   // prints entire node object content
};

template <class T>
class LinkedList {
public:
    LinkedList(T minVal, T maxVal);                 // constructor: accepts -infinity, +infinity values,
                                                    //  creates linked list with two corresponding nodes
    ~LinkedList();                                  // destructor
    Node<T>* search(Node<T>* location, T data);     // search for data starting at location, return node <= data
    Node<T>* insert(Node<T>* location, T data);     // insert node with data at new node to be placed directly 
                                                    //  after node with povided location, return new node
	LinkedList<T> *up; 		// added up pointer for LinkedLists
	LinkedList<T> *down;		// added down pointer for LinkedLists
   
    void printData();                               // prints linked list data
    void print();                                   // prints linked list with all nodes pointers
    Node<T>* head;                                  // head of list
};

template <class T>
class SkipList {
public:
    SkipList(T minVal, T maxVal);                   // constructor: accepts -infinity, +infinity values,
                                                    //  creates skip list with top-level only
    ~SkipList();                                    // destructor
    Node<T>* search(T data);                        // search for data, return node <= data (existing node, or location
                                                    //  where new node should be inserted in the bottom-most list)

	Node<T>* insert(T data);                            // insert node with data, return pointer if inserted, NULL if error
    void printData();                               // prints skip list data
    void print();                                   // prints skip list with all nodes pointers
    LinkedList<T> *topList;                         // pointer to the top-most list
    int randSeed = 330;                             // to be used as seed for the getRand() function
};

//returns 0 or 1 with a 50% chance 
//When it returns 1, insert the node to next level of the skiplist
int getRand(){
    return rand()%2;
}

/********************** From here down is the content of the LinkedList.cpp file: ***********************/

/****** Implementation of Node ******/

// Constructor
template<class T>
Node<T>::Node(const T& data)
{
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
    this->up = nullptr;
    this->down = nullptr;
}

// Print node's data value
template <class T>
void Node<T>::printData()
{
    cout << data << " ";
}

// Print entire node object content (data value, object's address, and all pointers)
template <class T>
void Node<T>::print()
{
    cout << " * " << data << ": [addr: " << this << " next: " << this->next << " prev: " << this->prev << " up: " << this->up << " down: " << this->down << "]  ";
}


/****** Implementation of linked list ******/

//Constructor
template <class T>
LinkedList<T>::LinkedList(T minVal, T maxVal){
	
	head = new Node<T>(minVal);
	Node<T> *tail = new Node<T>(maxVal);
	head -> next = tail;
	tail -> prev = head;
	this->up = nullptr;
    this->down = nullptr;
}

//Destructor
template <class T>
LinkedList<T>::~LinkedList(){
	
	Node<T> *current = head;

	while(current != nullptr){
		Node<T> *nextNode = current -> next;
		delete current;
		current = nextNode;
	}

	head = nullptr;
}

//search - looking for next->data <= data to maintain order. So when conditions of while loop not satisfied
//		   either left with node containing data (if exists), or node before where new data should be inserted to maintain order
template <class T>
Node<T>* LinkedList<T>::search(Node<T>* location, T data){
	
	while(location && location -> next && (location -> next -> data <= data)){
		location = location -> next;
	}

	return location;
}

//insert - inserts new node with data 'data', at specified location 'location' if location exists, location->next exists,
//data at location is less than the new data, and the node after the new node's data should be greater than the new data.
template <class T>
Node<T>* LinkedList<T>::insert(Node<T>* location, T data){
	
	if((location) && (location->next) && (location->data < data) && (location->next->data >= data)){
		Node<T> *newNode = new Node(data);
		newNode -> next = location -> next;
		newNode -> prev = location;
		location -> next -> prev = newNode;
		location -> next = newNode;
		return newNode;
	}else{
		return nullptr;
	}
}

//printData - prints data of all nodes in linked list seperated by a space.
template <class T>
void LinkedList<T>::printData(){
	Node<T> *current = head; //from beginning

	while(current){ //printing then moving, all the way to INT_MAX from INT_MIN
		current -> printData(); //includes the space

		current = current -> next;
	}
	cout << endl;
}

//print - prints entire contents of linked list including node addresses and pointers
template <class T>
void LinkedList<T>::print(){
	Node<T> *current = head; //from beginning

	while(current){
		current -> print();
		current = current -> next;
	}

	cout << endl;
}



/****** Skip List Implementation ******/

// Constructor
template <class T>
SkipList<T>::SkipList(T minVal, T maxVal){
	srand(this -> randSeed); // seed the random number generator using the seed initialized in the SkipList class
	topList = new LinkedList<T>(minVal, maxVal);
	topList -> down = nullptr;
	topList -> up = nullptr;
}

// Destructor
template <class T>
SkipList<T>::~SkipList(){
	LinkedList<T> *current = topList;
	Node<T> *deleteNode = current -> head;

	while(deleteNode -> up != nullptr){
		while(deleteNode -> next != nullptr){
			deleteNode = deleteNode -> next;
		}

		while(deleteNode -> down != nullptr){
			deleteNode = deleteNode -> down;
		}

		while(deleteNode -> prev != nullptr){
			Node<T> *prevNode = deleteNode;
			deleteNode = deleteNode -> prev;
			delete prevNode;
		}

		Node<T> *prevNode = deleteNode;
		deleteNode = deleteNode -> up;
		prevNode = nullptr;
		delete prevNode;
	}

	delete current;
}

// Search - returns a pointer to the node if x exists, or a pointer to its predecessor
// in bottom-most list if x doesn't exist
template <class T>
Node<T>* SkipList<T>::search(T x){
	Node<T> *current = topList -> head;

	while(true){
		while(current -> next && current -> next -> data <= x){
			current = current -> next;
		}

		if(current -> down == nullptr){
			break;
		}
		current = current -> down;
	}

	return current;
}

// Insert 
template <class T>
Node<T>* SkipList<T>::insert(T data){

    Node<T> *p = search(data); 

    if(p -> data == data){ //if data already exists in the SkipList, do nothing.
        return nullptr;
    }
    
    Node<T> *inserted;
    
	int i = 1;

    while (true) { //count number of heads/tails
        int result = rand() % 2;

        if (result == 1) { 

            i++;

        } else {

            break;

        }
    }

	int height = 1;

    LinkedList<T> *bottomList = topList;
    while(bottomList -> down != nullptr){
        bottomList = bottomList -> down;
        height++; //count the height of the SkipList while bringing bottomList pointer to the bottom list
    }

    for (int h = 1; h <= i; h++) { // for every i until the height
        if(i > height){ // if i is bigger than the height, we need a new add a new LinkedList above topList

            LinkedList<T> *newList = new LinkedList<T>(INT_MIN,INT_MAX);
            newList -> down = topList;
            topList -> up = newList;
            newList -> up = nullptr;
            topList = newList; // set topList to be the new List inserted

        }

        Node<T> *newInsert = bottomList -> search(bottomList -> head, data); //search for the data value in the list
        bottomList -> insert(newInsert, data); //insert the value into bottomList (starts as the bottom list but increments up)
        bottomList = bottomList -> up;
    }
    
    return inserted; //return the pointer to the value you inserted on the bottom-most level
}



template <class T>
void SkipList<T>::printData(){
	LinkedList<T> *currentList = topList;

	while(currentList != nullptr){ //printData() of every list top to bottom
		currentList -> printData();

		currentList = currentList -> down;
	}
}

template <class T>
void SkipList<T>::print(){
	LinkedList<T> *currentList = topList;

	while(currentList != nullptr){ //print() every list top to bottom
		currentList -> print();

		currentList = currentList -> down;
	}
}

#endif /* SkipList_h */