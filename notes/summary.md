# ADTs
* ADT Interfaces:
-  Opaque view of a data structure (eg. `typedef struct t *T`, we don't know `struct t`)
-  Function signatures for all operations
-  Semantics of operations (via documentation, etc)
- A contract between ADT and clients
* ADT implementations
- Concrete defintion of the data structures
- Function implementations for all operations

# Linked Lists
* A sequence of collection of 'nodes' holding value + pointer(s)
* No random access
* Easy to add, rearrange, remove nodes...
* List nodes references other list nodes:
  * Singly Linked List: `next`
  * Doubly Linked List: `next` `prev`

* Operations
  - Insertion ~ O(N)
  - Deletion ~ O(N)
  - Search ~ O(N)
  - Intersection ~ O(N+M)

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

* Array Implementation
```C
struct stack {
    int top;
    Item *items;
};
```
- Allocate an array with a maximum number of elements
- Fill items sequentially
- Maintain a counter of the number of pushed / popped items (ie. the top)
- Push: Increment top and set new top array index to value ~ O(1)
- Pop: Decrement top and return the last hightest value
- Disadvantage: Fixed size stack (Unless it's a dyanamically growing array)

# Queues
* FIFO (First In First Out) data structure
* List Implementation
```C
struct queue {
    struct node *head;
    struct node *tail;
}

struct node {
    Item item;
    struct node *next;
}
```
- Insert: O(N) - without tail pointer in struct, otherwise O(1)
- Deletion: O(1)

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

* Black-box testing: checks behaviour using only the interface (ie the ADT interface)
* White-box testing: checks internal behaviour (when we can see and test the ADT implementation)

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
* Complexity Classes
- O(1)          - Constant - Constant time execution, independant of input size.
- O(log n)      - Logarithmic - Some divide-and-conquer algorithms with trivial split/recombine operations.
- O(n)          - Linear - Every element of the input has to be processed
- O(n log n)    - n-log-n - Divide and conquer algorithms, where split / recombine is proportional to input
- O(n^2)        - Quadratic - Compute every input with every other input
- O(n^3)        - Cubic - misery
- O(n!)         - Factorial - what the...
- O(2^n)        - Exponential - nope

* N^2 Algo ie. when N=1000 takes 1.2seconds, how long for
  - N=2000      x2      ->   x4         4.8 seconds
  - N=10,000    x10     ->   x100       120 seconds
  - N=100,000   x100    ->   x10000     12000 seconds
  - N=1000000   x1000   ->   x1000000   1200000 seconds
* Apply ^2 to how much times number of items increases. Multiple that number with base case.

* Tractable: have a polynomial time ('P') algorithm
* Intractable: no tractable algorithm exists (usually 'NP')
* Non-computable: no algorithm exists

# Recursion
* Base case (or stopping case): where no recursive call is needed
* Recursive case: calls the function on a smaller version of the problem.
* Steps:
  1. Solve as if you're not using recursion for basic subset of problem
  2. Use self for solving the rest
* eg. n! = (n-1)! x n
  - f(0)=1 f(1) = 1 else f(n) = n*f(n-1)
* Usually iterative and recusrive has same time complexity (ie. arry_max, binary_search)

# Trees
* Trees are branches data structures of nodes and edges with no cycles.
* Each node contains a value
* Each node has edges <=k other nodes (k = 2 for binary trees)
* Node is parent if it has outgoing edges
* Node is child if it has incoming edges
* Depth (or height) is the number of edges from the root to that node;
* A leaf is a node with no children.
* Trees can be viewed as set of nested structures
* Values in the left subtree has to be less than the node value
* Vice versa for right subtree.
* Degenerate: maximal height 
* Balanced: minimal height
  - Size: |size(L) - size(R)| < 2
  - Height: |height(L) - height(R)| < 2
* Advantages
- Faster search O(log n) - compared with linked lists
- Faster inseartion O(log n) - compared with array O(N)

## Binary trees
* A binary tree with n nodes has a height of at most n-1, if degenerate or least floor(log n) if balanced
* Insertion: balanced ~ O(log n), degenerate ~ O(n) ie. have to traverse the tree, like a llist
* Search / Deletion: balanced ~ O(log n), degenerate O(n)
* All nodes in left are less than and vice versa
* Structure determined by order of insertion

## Tree Traversals
* Depth First:
  - Pre-order traversal (NLR)
  - In-order traversal (LNR)
  - Post-order traversal (LRN)
* Breath First:
  - Level-order traversal: visit node and all its children 
    - ie. Like a BFS, where you use a queue

# Priority Queue (Using Heaps)
* Process in order of key or priority.
* Altered `enqueue` and `dequeue` operations
* `Enqueue`: join item with a priority.
  - FixUp operation has to be done, since we insert node at bottom.
* `Dequeue`: remove item with highest priority Q.
  - FixDown operation has to be done, since we remove top node, by swapping with last item. Last item may not be ideal canditate for top root.
## Heaps
* Commonly viewed as trees, implemented using arrays.
* Two properties to maintain:
  1. heap order property
  2. complete tree property
* Heaps have **top-to-bottom**  ordering (whereas binary trees have left to right ordering)
* Heaps are complete trees!
  - Every level is filled before adding nodes to the next level
  - Nodes in given level are filled left-to-right with ni breaks
* Arrays are good for heaps
  -  parent(i) = i/2
  -  left_child(i) = 2i
  -  right_child(i) = 2i+1
* Inserting:
  1. Add new element at the bottom-most, right-most position (to ensure complete tree property)
  2. Reorganise values along the path to the root (to ensure it maintains heap order)
    - We call this the heap fixup operation
  - O(log n)

* Deleting is a three-step process:
  1. Swap root value with bottom-most, right-most value (ie. last element of array)
  2. Remove that element
  3. Reorganise values along the path from root (to ensure it maintains heap order)
    - We call this the heap fix down operation
  - O(log n)

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
  - |E| approach |V|^2
- Density ~ more connections between nodes
  - |V| approach |V|

* Subgraph: subset of vertices and associate edges
![Sub graph](./img/subgraph.png)

* Path: Sequence of connected vertices ie [(v,e) elem 1]
* Simple path: no repeating vertices
* Cycle: path with start and end vertex as the same.
![Path](./img/path.png)

* Connected graph: a path exists from every node to every other node
* Tree: connected graph with no cycles
![Connected](./img/connected.png)

* Connected components: set of connected subgraphs


* Spanning tree: (of graph) subgraph that connects all its verteces
* Minimum spanning tree: spanning tree that has the least total weight
* Spanning forest: (of graph) subgraph that contains all its vertices and is a set of ›trees
* Clique: complete subgraph





* Euler and Hamilton Paths and Tours
  - **Euler path**: path in graph that visits every edge exactly once. Starts and ends with different vertices.
  - **Euler tour**: path in graph that uses every edge of a exactly once. Starts and ends on same vertex.
  - **Hamilton path**: path in graph that visits each vertex exactly once.
  - **Hamilton tour**: hamiltonian path that's a cycle.




# Sorting
## Bubble Sort
* Steps:
  1. Swap adjacent nodes if left > right
  2. Repeat the above
* best: Ω(n^2) ~ EE: O(n)
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

* Amortisation: reducing average work over time 

# Hash Tables

* Collision Resolution
- Chaining
  - Using a linked list
  - Using a tree (a bit more efficent O(log n) search)

- Linear Probing
- Double Hashing
  - If key already exists, hash again and add the new value to the incremented index (ie. index = hash1(key) + hash2(key))
- Resize table
  - You'll need to rehash and insert into table again.