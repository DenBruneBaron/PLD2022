#ifndef MY_FREE_LIST_H
#define MY_FREE_LIST_H

#include <inttypes.h>
#include <stdbool.h> 

typedef uint16_t heapIndex;

struct node {
  int _idx; // index of a given node
  bool _is_free; // true if index is free in heap, false otherwise
  
  /*
    if a node is free, the pointers "previous_node" and
    "next_node" will point to the closet free node with
    respect to the current node location

    if a node is marked (thus not free) the "previous_node" and
    "next_node" will point to the node that's before and after
    the marked node.
  */
  struct node *_previous_node; 
  struct node *_next_node;
};


struct free_list_t {
  struct node **_lst_pointer; // pointer to list of node pointers
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