
#include <iostream>
#include "LinkedList.h"

// constructor, initialize class variables and pointers here if need.
LinkedList::LinkedList() {
  top_ptr_ = nullptr;
}

// deconstructor,
LinkedList::~LinkedList() {}

// creates a new node struct for the list
node* LinkedList::init_node(int data) {
  node* ret(new node);
  ret->data = data;
  ret->next = nullptr;
  return ret;
}

string LinkedList::report() {
  string ret = "";
  node* cursor = top_ptr_;
  while (cursor != nullptr){
    ret.append(to_string(cursor->data) + " ");
    cursor = cursor->next;
  }
  return ret;
}

void LinkedList::append_data(int data) {
  auto new_node = init_node(data);
  append(new_node);
}

void LinkedList::append(node* new_node) {
  node* cursor = top_ptr_;
  if (cursor == nullptr){
    top_ptr_ = new_node;
    return;
  }
  // Using cursor->next here because we want to go until the NEXT node is empty.
  while (cursor->next != nullptr){
    cursor = cursor->next;
  }
  cursor->next = new_node;
  return;
}

void LinkedList::insert_data(int offset, int data) {
  // Check size of offset
  if(offset < 0 || offset > size()){return;}
  node* cursor = top_ptr_;

  if (offset == 0) {
    // Insert at top
    node* temp = cursor;
    auto new_node = init_node(data);
    top_ptr_ = new_node;
    new_node->next = temp;
    return;
  }
  else if (offset == size()){
    // Insert at end
    auto new_node = init_node(data);
    append(new_node);
    return;
  }
  //Insert at another point
  for (int i = 0; i < offset-1; i++)
  {
    cursor = cursor->next;
  }
  node* temp = cursor->next;
  auto new_node = init_node(data);
  cursor->next = new_node;
  new_node->next = temp;
  return;
}

void LinkedList::insert(int offset, node* new_node) {
   // Check size of offset
  if(offset < 0 || offset > size()){return;}
  node* cursor = top_ptr_;

  if (offset == 0) {
    // Insert at top
    node* temp = cursor;
    top_ptr_ = new_node;
    new_node->next = temp;
    return;
  }
  else if (offset == size()){
    // Insert at end
    append(new_node);
    return;
  }
  //Insert at another point
  for (int i = 0; i < offset-1; i++)
  {
    cursor = cursor->next;
    cout << i << " " << cursor->data << endl;
  }
  node* temp = cursor->next;
  cursor->next = new_node;
  new_node->next = temp;
  return;


}

void LinkedList::remove(int offset) {
  // Check size of offset
  if(offset < 0 || offset > size())     {return;}
  node* cursor = top_ptr_;

  if (offset == 0) {
    // Remove at top by tarversing 1 node.
    node* dead_node = cursor;
    top_ptr_ = cursor->next;
    delete dead_node;
    return;
  }

  //Remove at another point
  // Get to previous entry
  for (int i = 0; i < offset - 1; i++)
  {
    cursor = cursor->next;
  }
  // look two ahead for new cursor
  node* dead_node = cursor->next;
  cursor->next = cursor->next->next;
  delete dead_node;
  return;
}

int LinkedList::size() {
  int ret = 0;
  node* cursor = top_ptr_;
  while (cursor != nullptr){
    ret++;
    cursor = cursor->next;
  }
  return ret;
}

bool LinkedList::contains(int data) {
  node* cursor = top_ptr_;
  while (cursor != nullptr){
    if (cursor->data == data) {return true;}
    cursor = cursor->next;
  }
  return false;
}

// This function is implemented for you
// It returns the top pointer
node* LinkedList::get_top() { return top_ptr_; }

// This function is implemented for you
// It sets a given pointer as the top pointer
void LinkedList::set_top(node* top_ptr) { top_ptr_ = top_ptr; }
