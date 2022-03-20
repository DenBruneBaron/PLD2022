#include "free_list.h"

#include <stdio.h>
#include <stdlib.h>

static const void free_idx(heapIndex idx, struct free_list_t *this) {
  // assumes idx is in the range

  struct node *ptr = this->_lst[idx];

  if (ptr->_is_free) return;

  ptr->_is_free = true;
  if (ptr->_prev) ptr->_prev->_next = ptr;
  if (ptr->_next) ptr->_next->_prev = ptr;
  
  if (!this->_first_free || this->_first_free->_idx > idx)
    this->_first_free = ptr;
}

// assumes (this) is not empty
static const heapIndex get(struct free_list_t *this) {
  struct node *ptr = this->_first_free;

  ptr->_is_free = false;

  if (ptr->_prev) ptr->_prev->_next = ptr->_next;
  else this->_first_free = ptr->_next;

  if (ptr->_next) ptr->_next->_prev = ptr->_prev;

  return ptr->_idx;
}

static const bool is_empty(struct free_list_t *this) {
  return !this->_first_free;
}

static struct free_list_t new(uint16_t size) {
  struct free_list_t this = (struct free_list_t){
    .free_idx=&free_idx, .get=&get, .is_empty=&is_empty,
    ._lst=(struct node **) malloc(size * sizeof(struct node))
  };

  for (uint16_t i = 1; i < size; ++i) {
    this._lst[i] = (struct node *) malloc(sizeof(struct node));
    this._lst[i]->_idx = i;
    this._lst[i]->_is_free = true;
    this._lst[i]->_next = this._lst[i]->_prev = NULL;
  }

  for (uint16_t i = 2; i + 1 < size; ++i) 
    this._lst[i]->_next = this._lst[i + 1],
    this._lst[i]->_prev = this._lst[i - 1];

  this._lst[1]->_next = this._lst[2];
  this._lst[size - 1]->_prev = this._lst[size - 2];

  this._first_free = this._lst[1];

  return this;
}

const struct free_list_class free_list_t={.new=&new};