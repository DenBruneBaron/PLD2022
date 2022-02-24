#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

typedef uint32_t heapNode;
typedef uint16_t heapIndex;

heapNode heap[0x8000] = {0};

/* Nodes are represented as follows:                  */
/* 0 represents (), the empty list                    */
/* An odd value represents an integer                 */
/* A number 0 <= n < 2^30 is represented as 2n+1      */
/* A value v where the two least significant bits     */
/*    of v are 10 represents a pair                   */
/*    where (v>>17) & 0x7fff is the index of the head */
/*    and (v>>1) &  0x7fff is the index of the tail   */
/* Note that the most significant bit is not used, so */
/*    (node & 0x7ffffffff) == 0                       */
/* This means that you can use this bit for marking   */

heapIndex nextFreeNode = 1; /* index of next free node */

/* Note: Index 0 contains 0, so represents ().  This should not chance */

/* You might want to change the initialisation to suit your GC method */
/* But do not change that heap[0] == 0 */

heapIndex allocateNumber(uint32_t n) /* allocate number node */
{
  if (n>0x7fffffff) {
    fprintf(stderr, "Number too big to represent: %"PRIx32"\n", n);
    exit(1);
  }
  heap[nextFreeNode] = (n<<1) + 1;
  return nextFreeNode++;
}

uint32_t getNumber(heapIndex v) /* get number value of number node */
{
  heapNode node = heap[v];
  if (node & 1 == 0) {
    fprintf(stderr, "Not a number node: (%"PRIx32"\n", node);
    exit(1);
  }
  return node >> 1;
}

heapIndex cons(heapIndex head, heapIndex tail) /* allocate pair node */
{
  if (head > 0x7fff || tail > 0x7fff) {
    fprintf(stderr, "Illegal pair: (%"PRIx32", %"PRIx32")\n", head, tail);
     exit(1);
  }
  heap[nextFreeNode] = (head<<17) | (tail<<2) | 2;
  return nextFreeNode++;
}

heapIndex car(heapIndex value) /* take head of pair node */
{
  
  heapNode node = heap[value];
  if (node & 3 != 2) {
    fprintf(stderr, "Not a pair node: (%"PRIx32"\n", node);
    exit(1);
  }
  return (node>>17) & 0x7fff;
}

heapIndex cdr(heapIndex value) /* take tail of pair node */
{
  
  heapNode node = heap[value];
  if (node & 3 != 2) {
    fprintf(stderr, "Not a pair node: (%"PRIx32"\n", node);
    exit(1);
  }
  return (node>>2) & 0x7fff;
}

/* You can add and modify code above this line */
  
heapIndex gc(heapIndex root) /* garbage collect and return new root */
{
  int liveCount = 0;

  /* insert code here */

  fprintf(stderr,"%d live nodes\n", liveCount);
  return root;
}

/* Don't change anything below this line */

heapIndex iota(uint32_t n) /* make a list of integers from 1 to n */
{
  heapIndex list = 0; /* empty list */
  while (n > 0) {
    heapIndex head = allocateNumber(n--);
    list = cons(head, list);
  }
  return(list);
}

heapIndex filterDivides(heapIndex list, uint32_t n)
/* removes elements that divide evenly by n */
{
  if (list == 0) return list;  /* empty list */
  uint32_t m = getNumber(car(list));
  if (m % n == 0)
    return filterDivides(cdr(list), n);
  return cons(car(list), filterDivides(cdr(list), n));
}

heapIndex makeTree(int n)
/* Make tree of depth n */
{
  if (n < 1) return 0;
  heapIndex tree = makeTree(n-1);
  return cons(tree,cons(allocateNumber(n),tree));
}

void printTree(heapIndex v) /* print tree */
{
  if (v == 0) { printf("()"); return; }
  heapNode n = heap[v];
  if (n & 1) {
    printf("%"PRIu32"",getNumber(v));
    return;
  }
  printf("(");
  printTree(car(v));
  printf(".");
  printTree(cdr(v));
  printf(")");
}

int main(int ac, char **av)
{
  heapIndex numbers = iota(1000); /* list of 1 .. n */
  numbers = cdr(numbers); /* drop first element */
  heapIndex primes = 0; /* will contain primes */
  while (numbers != 0) /* until end of list */
  {
    primes = cons(car(numbers), primes);
    uint32_t n = getNumber(car(numbers));
    numbers = filterDivides(numbers, n);
  }
  
  primes = gc(primes);

  printf("\n");
  printTree(primes);
  printf("\n\n");

  heapIndex tree = makeTree(8);

  tree = gc(tree);

  printf("\n");
  printTree(tree);
  printf("\n\n");

  numbers = iota(1000); /* list of 1 .. n */
  numbers = cdr(numbers); /* drop first element */
  primes = 0; /* will contain primes */
  while (numbers != 0) /* until end of list */
  {
    primes = cons(car(numbers), primes);
    uint32_t n = getNumber(car(numbers));
    numbers = filterDivides(numbers, n);
  }
  
  primes = gc(primes);
  
  exit(0);

}
