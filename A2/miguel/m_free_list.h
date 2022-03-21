#ifndef M_FREE_LIST_H
#define M_FREE_LIST_H

#include <inttypes.h>
#include <stdbool.h> 

typedef uint16_t heapIndex;

struct node {
  int _idx; // index of the node
  bool _is_free; // true if index is free in heap, false otherwise
  
  // if node is free, prev and next points to the closest
  // free node before and after itself, respectively

  // if node is not free, prev and next just points to the node
  // before and after itself respectively, 
  // i.e. with indices (_idx - 1) and (_idx + 1)
  
  struct node *_prev; 
  struct node *_next;
};

struct free_list_t {
  struct node **_lst; // pointer to list of node pointers
  struct node *_first_free; // pointer to the first free node in the list

  // frees node at index idx
  void (*free_idx)(heapIndex idx, struct free_list_t *this);

  // mark a free node as not free and returns its index
  heapIndex (*get)(struct free_list_t *this);

  // return true if the list is empty, i.e. no more free nodes
  // and false otherwise
  bool (*is_empty)(struct free_list_t *this);
};

// turn-around to use functions in C structures
extern const struct free_list_class {
  // creates a new free list of the specified size
  // with all nodes initially free, and returns it
	struct free_list_t (*new)(uint16_t size);
} free_list_t;

#endif