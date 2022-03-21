#include "my_free_list.h"
#include <stdio.h>
#include <stdlib.h>



static const void free_idx(heapIndex idx, struct free_list_t *this) {
  // assumes idx is in the range

  struct node *ptr = this->_lst_pointer[idx];

  if (ptr->_is_free) return;

  ptr->_is_free = true;
  if (ptr->_previous_node) ptr->_previous_node->_next_node = ptr;
  if (ptr->_next_node) ptr->_next_node->_previous_node = ptr;
  
  if (!this->_first_free || this->_first_free->_idx > idx)
    this->_first_free = ptr;
}



// assumes (this) is not empty
static const heapIndex get(struct free_list_t *this) {
  struct node *ptr = this->_first_free;

  ptr->_is_free = false;

  if (ptr->_previous_node) ptr->_previous_node->_next_node = ptr->_next_node;
  else this->_first_free = ptr->_next_node;

  if (ptr->_next_node) ptr->_next_node->_previous_node = ptr->_previous_node;

  return ptr->_idx;
}



static const bool is_empty(struct free_list_t *this) {
  return !this->_first_free;
}



static struct free_list_t new(uint16_t size) {
  struct free_list_t this = (struct free_list_t){
    .free_idx=&free_idx, .get=&get, .is_empty=&is_empty,
    ._lst_pointer=(struct node **) malloc(size * sizeof(struct node))
  };


  for (uint16_t i = 1; i < size; ++i) {
    this._lst_pointer[i] = (struct node *) malloc(sizeof(struct node));
    this._lst_pointer[i]->_idx = i;
    this._lst_pointer[i]->_is_free = true;
    this._lst_pointer[i]->_next_node = this._lst_pointer[i]->_previous_node = NULL;
  }


  for (uint16_t i = 2; i + 1 < size; ++i) 
    this._lst_pointer[i]->_next_node = this._lst_pointer[i + 1],
    this._lst_pointer[i]->_previous_node = this._lst_pointer[i - 1];

  this._lst_pointer[1]->_next_node = this._lst_pointer[2];
  this._lst_pointer[size - 1]->_previous_node = this._lst_pointer[size - 2];

  this._first_free = this._lst_pointer[1];

  return this;
}

const struct free_list_class free_list_t={.new=&new};