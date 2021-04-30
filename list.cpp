/*list.cpp*/

//
// Author: Prof. Hummel, U. of I. Chicago, Spring 2021
// 
// Implements a one-way linked-list with optimized insertion at
// head and tail of list. The nodes contain 2 data values, a string
// and an integer.
//
//
// Author: Latif Vaid, UIC, Spring 2021
//
//Project 06 Part 02

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include "list.h"

using namespace std;



//
// private member functions:
//

//
// inits this list then makes deep copy of other
//
// Time complexity: O(N)
//
void List::initAndDeepCopy(const List& other)
{
   //
   // DONE: init this list, then make copy of other
   //
    this->Head = nullptr;     //initalizing other list
    this->Tail = nullptr;
    this->Count = 0;
    
    //making a deeping copy using push_back function
    Node* cur = other.Head;
    string value1;
    int value2;
    while(cur != nullptr){  //storing in seprate list (deep copy)
        value1 = cur->Data.Value1;
        value2 = cur->Data.Value2;
        push_back(value1, value2);
        cur = cur->Next;
    }
}


// 
// free the nodes in the list and resets to empty
//
// Time complexity: O(N)
//
void List::freeAndReset()
{
   //
   // DONE: free this list, then reset to empty
   //
    Node* temp;
    Node* cur = this->Head;
    this->Head = nullptr;
    this->Tail = nullptr;
    while(cur != nullptr){  //deleting every element till nullptr
        temp = cur;
        cur = cur->Next;
        delete temp;
    }
    this->Count = 0; //after list is empty
}



//
// public member functions:
//

//
// default constructor
//
// Initializes the list to empty.
// 
// Time complexity: O(1)
//
List::List()
{
   this->Head = nullptr;
   this->Tail = nullptr;
   this->Count = 0;
}

//
// copy constructor
//
// Makes a deep copy of the other list into this list.
// 
// Time complexity: O(N)
//
List::List(const List& other)
{
   this->initAndDeepCopy(other);
}

//
// destructor
//
// Frees all memory related to this list, and then resets to empty.
// 
// Time complexity: O(N)
//
List::~List()
{
   this->freeAndReset();
}

//
// assignment operator (e.g. L2 = L;)
//
// Makes a deep copy of the other list into this list; since this
// list already exists, the existing elements of this list are freed
// before the copy is made.
// 
// Time complexity: O(N)
//
List& List::operator=(const List& other)
{
   if (this == &other)  // special case: check for L = L;
      return *this;     // do nothing and just return THIS object back

   //
   // This is different from a copy constructor, because "this" list
   // exists and contains nodes.  So we have to free "this" list before
   // we copy the "other" list:
   //
   this->freeAndReset();
   this->initAndDeepCopy(other);

   return *this;  // done, return THIS object back
}

//
// size
//
// Returns the # of elements in the list.
//
// Time complexity: O(1)
//
int List::size()
{

   return this->Count;   //count which is size of the list
}

//
// empty
//
// Returns true if empty, false if not.
//
// Time complexity: O(1)
//
bool List::empty()
{
   //
   // DONE:
   //
    //if true empty else not
    if(this->Count == 0){
        return true;
    }
    return false;
}

//
// search
//
// Search the list for the first occurence of the string value.
// If found, its position in the list is returned. Positions are 
// 0-based, meaning the first node is position 0. If the value is
// not found, -1 is returned.
//
// Time complexity: on average O(N)
//
int List::search(string value)
{
    Node* cur = this->Head;
    int counter = 0;
    while(cur != nullptr){ //loops till it finds the value
        if(cur->Data.Value1 == value){
            return counter;  //position
        }
        cur = cur->Next;
        counter++;
    }
    if(cur == nullptr){ //if not found
        return -1;
    }
    
   return -1;
}

//
// retrieve
//
// Retrieve's the data from node at the given position; the list 
// remains unchanged. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("List::retrieve: invalid position");
//
// Time complexity: on average O(N)
//
void List::retrieve(int pos, string& value1, int& value2)
{
   //
   //
    if(pos < 0 or pos >= this->Count){ //do not want negtive or over the size of the list
        throw invalid_argument("List::retrieve: invalid position");
    }
    Node* cur = this->Head;
    int counter = 0;
    while(cur != nullptr)
    {
        if(pos == counter){
            value1 = cur->Data.Value1;
            value2 = cur->Data.Value2;
        }
        counter++;
        cur = cur->Next;
    }
}

//
// insert
//
// Inserts the given data in the list such that after
// the insertion, the value is now at the given
// position.
//
// Positions are 0-based, which means a position of 0 
// denotes the data will end up at the head of the list,
// and a position of N (where N = the size of the list)
// denotes the data will end up at the tail of the list.
// If the position is invalid, throws an exception, i.e.
// throw invalid_argument("List::insert: invalid position");
//
// Time complexity: on average O(N)
//




void List::insert(int pos, string value1, int value2)
{
    Node* cur = this->Head;
    Node* prev = nullptr;
    int counter = 0;
    if (this->Head == nullptr) { //if list is empty
        if (pos != 0) {  //list empty and position is >0
            throw invalid_argument("List::insert: invalid position");
        }
        Node* newN = new Node;
        newN->Data.Value1 = value1;
        newN->Data.Value2 = value2;
        newN->Next = nullptr;
        this->Head = newN; //sets pointers
        this->Tail = newN;
        this->Count++;
    }  else if (pos == 0) {
        Node* newN = new Node;
        newN->Data.Value1 = value1;
        newN->Data.Value2 = value2;
        newN->Next = this->Head;
        this->Head = newN;
        this->Count++;
    } else { //wants to insert in the middle (not front or end)
        while (cur != nullptr) {
            if (counter == pos) {
                Node* newN = new Node;
                newN->Data.Value1 = value1;
                newN->Data.Value2 = value2;
                newN->Next = cur;
                prev->Next = newN;
                this->Count++;
                return;
            }
            counter++;
            prev = cur;
            cur = cur->Next;
        }
        if (counter == pos) {
            Node* newN = new Node;
            newN->Data.Value1 = value1;
            newN->Data.Value2 = value2;
            newN->Next = nullptr;
            this->Tail->Next = newN;
            this->Tail = newN;
            this->Count++;
            return;
        }
           throw invalid_argument("List::insert: invalid position");
    }
}

//
// remove
//
// Removes and deletes the node at the given position; no data is
// returned. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("List::remove: invalid position");
//
// Time complexity: on average O(N)
//
void List::remove(int pos)
{
   
    if(pos < 0 or pos >= this->Count){
        throw invalid_argument("List::remove: invalid position");
    }
    Node* cur = this->Head;
    Node* prev = nullptr;
    Node* del = nullptr;
    int counter = 0;
    while(cur != nullptr){
        if(pos == counter){
            if(counter == 0){
                del = cur;  //saves it in the del so we delete properly
                cur = this->Head->Next;
                this->Head = cur;
                delete del;
                this->Count--;
                break;
            } else if(cur == this->Tail){
                delete this->Tail;
                this->Tail = prev;
                prev->Next = nullptr;
                this->Count--;
                break;
            } else {
                del = cur;
                cur = cur->Next;
                prev->Next = cur;
                delete del;
                this->Count--;
                break;
            }
        }
        prev = cur;
        cur = cur->Next;
        counter++;
    }
    
}

//
// front
//
// Returns the data from the first node in the list. Throws an 
// exception if the list is empty, i.e.
// throw runtime_error("List::front: empty list");
// 
// Time complexity: O(1)
//
void List::front(string& value1, int& value2)
{
    if(this->Count == 0){
        throw runtime_error("List::front: empty list");
    } else {
        value1 = this->Head->Data.Value1;
        value2 = this->Head->Data.Value2;
    }
}

//
// back
//
// Returns the data from the last node in the list. Throws an 
// exception if the list is empty, i.e.
// throw runtime_error("List::back: empty list");
// 
// Time complexity: O(1)
//
void List::back(string& value1, int& value2)
{
    if(this->Count == 0){
        throw runtime_error("List::back: empty list");
    } else {
        value1 = this->Tail->Data.Value1;
        value2 = this->Tail->Data.Value2;
    }
}

//
// push_front
//
// Inserts the given data at the front of the list.
// 
// Time complexity: O(1)
//
void List::push_front(string value1, int value2)
{
    insert(0,value1,value2); //calling insert for inserting at pos 0

}

//
// push_back
//
// Inserts the given data at the back of the list.
// 
// Time complexity: O(1)
//
void List::push_back(string value1, int value2)
{
    Node* cur = this->Tail;
    Node* newN = new Node();
    newN->Data.Value1 = value1;
    newN->Data.Value2 = value2;
    if(cur == nullptr){
        this->Tail = newN;
        this->Head = this->Tail;
        newN->Next = nullptr;
        this->Count++;
    } else {
        this->Tail->Next = newN;
        this->Tail = this->Tail->Next;
        this->Tail->Next = nullptr;
        this->Count++;
    }
}
