# Linked Lists
* A sequence of collection of 'nodes' holding value + pointer(s)
* No random access
* Easy to add, rearrange, remove nodes...
* List nodes references other list nodes:
  * Singly Linked List: `next`
  * Doubly Linked List: `next` `prev`

# Stacks
* LIFO (Last In First Out) data structure
* List implementation:
```C
struct stack {
    struct node *head;
    struct node *tail;
    size_t size;
};

struct node {
    Item item;
    struct node *next;
}
```
- Push: Append node to head of the list ~ O(1)
- Pop: Remove and return head ~ O(1)

# Queues
* FIFO (First In First Out) data structure


# Analysis 
* Emperical: executing and measuring
* Theoretical: proving and deriving

* Factors:
  - Correctness: returns expected output
  - Robustness: behaves sensibly for non-valid inputs
  - Efficiency: returns results reasonably quickly
  - Clarity: clear code
  - Consistency: interface is clear & consistent

* We will only focus on **correctness** and **efficiency**.

## Testing (Correctness)
* Postel's Robustness Principle: *"Be conservative in what you do; be liberal in what you accept from others"*

* TDD (Test Driven Development): write tests first, then write the function & repeat
* Regression testing: Keep a test suite and always run the tests after each update to the program

* Black-box testing: checks behaviour using only the interface
* White-box testing: checks internal behaviour

## Complexity (Efficency)
* Alorithm runtime tends to be a function of input size
* Focus on asymptotic worst-case execution time
* Take into account all possible input ranges
* Cases: **Best Case**  **Average Case** **Worst Case**
* Binary search example:
  * start at middle for sorted list
    * is the middle the key? if not continue
  * if item is less, we search in left range (lo, mid)
  * otherwise, we search in right range (mid+1, hi)
* Best case: O(1) ~ middle value
* Worst case:
  * t(N) = 1 + t(N/2) = log(N) + 1
  * ~ O(log n)

* O(1) < O(log n) < O(n) < O(n log n) < O (n^2) < O(n^3) < O (n!) < O(2^n)

* Tractable: have a polynomial time ('P') algorithm
* Intractable: no tractable algorithm exists (usually 'NP')
* Non-computable: no algorithm exists

# Recursion
* Base case (or stopping case): where no recursive call is needed
* Recursive case: calls the function on a smaller version of the problem.

# Trees
* Trees are branches data structures of nodes and edges with no cycles.
* Each node contains a value
* Each node has edges <=k other nodes (k = 2 for binary trees)
* Trees can be viewed as set of nested structures
* Values in the left subtree has to be less than the node value
* Vice versa for right subtree.
* Degenerate: if height is at most n-1
* Balanced:
  - Size: |size(L) - size(R)| < 2
  - Height: |height(L) - height(R)| < 2


# Priority Queue (Heaps)

# Graphs
* Models relationship between items
* A graph G is a set of vertices V and edges E
- E := {(v,w) | v,w is an element of V, (v,w) is an element of V X V}
- Basically a set of edges [(v,w)]
![Graph Types](./img/gtypes.png)

* Simple graphs
- a set of vertices
- a set of undirected edges
- no self loops
- no parallel edges

* Sparcity vs Density
- Sparcity ~ less connections between nodes
  - |E| -> |V|^2
- Density ~ more connections between nodes
  - |V| ~> |V|

* Subgraph: subset of vertices and associate edges
* Path: Sequence of connected vertices ie [(v,e) elem 1]
* Simple path: no repeating vertices
* Cycle: path with start and end vertex as the same.
* Connected graph: a path exists from every node to every other node
* Tree: connected graph with no cycles
* Connected components: set of connected subgraphs
* Spanning tree: (of graph) subgraph that connects all its verteces
  * MST: spanning tree that has the least total weight
* Spanning forest: (of graph) subgraph that contains all its vertices and is a set of trees
* Clique: complete subgraph

# Sorting
## Bubble Sort
* Steps:
  1. Swap adjacent nodes if left > right
  2. Repeat the above
* best: Ω(n^2)  -- EE:O(n)
* worst: O(n^2)
* stable / in place

## Selection Sort
* Steps:
  1. Look for smallest items from i+1 to n
  2. swap i+1 with min (found min index)
  3. repeat the above with i++
* best: O(n^2)
* worst: O(n^2)

## Insertion Sort

## Shell Sort

## Merge Sort
* Divide and conquer

## Quick Sort
* Divide and conquer

## Key-Indexed
* Non-comparison

## Heap
* Non-comparison
* Steps:
  1. Add all items to pqueue.
  2. Remove items from pqueue into original array.
* best: Ω(n log(n))
* worst: O(n log(n))
* not stable

## Radix Sort
* Non-comparison

# Balanced Trees
* Size balanced: |size(t.L) - size(t.R)| < 2
* height balanced: |height(t.L) - height(t.R)| < 2


# Hash Tables
