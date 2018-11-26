# Tutorial 01

## Bare Linked Lists
Consider this “bare” linked list definition from the lecture.
```C
typedef char Item;

typedef struct node *link;
typedef struct node {
    Item item;
    link next;
} node;
```
A Lengthy Matter
How would you write a function int list_length (link l), that takes a link to the first element of a list and returns the length of the list?
### Solution
```C
int list_length (link l)
{
    int i;
    for (i = 0; l; i++) {
        l = l->next;
        i++;
    }
    return i; 
}
```


## Duplicity
How would you write a function link list_duplicate (link l), that takes a link to the first element of a list and returns a “deep copy” of the list (i.e., a new list that contains the same data in the same order)?

Here are some prototypes and implementations of functions you may wish to use for this task:
```C
// Creates a new node, initialised with the item provided.
// Returns pointer to node (link).
link node_new (Item item)
{
    link n = malloc (sizeof (*n));
    if (n == NULL)
        err (1, "couldn't allocate");
    n->item = item;
    n->next = NULL;
    return n;
}

// Insert a new node into a given non-empty list.
// The node is inserted directly after the head of the list ls.
void list_insert_next (link ls, link node)
{
    assert (ls != NULL);
    assert (node != NULL);
    node->next = ls->next;
    ls->next = node;
}
```
### Solution
```C
link list_duplicate (link l)
{
    if (!l) return NULL;
    link n = new_node(l->item);
    link head = n;
    while (l->next) {
        n->next = new_node(l->next->item);
        n = n->next;
        l = l->next;
    }
    return head;
}
```


## Lists of Characters
It’s not especially efficient, nor is it particularly nice in C, but many languages (notably some functional languages) use linked lists where we would use arrays.

Assume we have these functions:
```C
// Prints each character of the list.
void list_print (link l);

// Take a regular C-style string (i.e., a `\0`-terminated array of
// characters), and produce a linked list of characters.
link list_from_cstr (const char *str);

// Take a linked list and return it, reversed.
link list_reverse (link l);
```
Here’s a simple program; what does it print?
```C
int main (int argc, char *argv[])
{
    link ls = list_from_cstr ("hello world!");
    link ls2 = list_duplicate (ls);

    list_print (ls);
    list_print (ls2);
    list_print (list_reverse (ls));
    list_print (ls);
    list_print (ls2);

    return 0;
}
```
### Solution
HEAD -> h -> e -> l -> l -> o ->   -> w -> o -> r -> l -> d -> ! -> TAIL
HEAD -> h -> e -> l -> l -> o ->   -> w -> o -> r -> l -> d -> ! -> TAIL
HEAD -> ! -> d -> -> l -> r -> o -> w ->  -> o -> l -> l -> e -> h -> TAIL
HEAD -> h -> TAIL  // Assuming list_reverse doesn't change the original head of l2
HEAD -> h -> e -> l -> l -> o ->   -> w -> o -> r -> l -> d -> ! -> TAIL


## Doubly-Linked Lists
A doubly-linked list is similar to a regular linked list, but each nodes has pointers to both the next and previous nodes in the list. Consider the following doubly linked list definition:
```C
typedef char Item;
typedef struct dnode *dlink;

struct dnode {
    Item item;
    dlink prev, next;
};
```
Write a function append which attaches the list list2 at the end of list1 and returns the resulting list.
### Solution
```C
dlink append (dlink list1, dlink list2)
{
    dlink head = list1;
    for (; list1->next; list1 = list1->next)
    list2->prev = list1;
    return head;
}
```
dlink append (dlink list1, dlink list2);
Is it necessary to return the resulting list? Could we instead get away with the following interface?
void append (dlink list1, dlink list2);
### Answer
Yes, if we temporarily store the pointer for list1, we can then call `void append(list1, list2)` and and assume that temporarily stored pointer to list1 is the start of the appended list.
```C
void append (dlink list1, dlink list2)
{
    for (; list1->next; list1 = list1->next)
    list2->prev = list1;
}
```


# Extra C
## switched on
Here’s two switch statements.
```C
// S1
switch (ch) {
case 'a': printf ("eh? "); break;
case 'e': printf ("eee "); break;
case 'i': printf ("eye "); break;
case 'o': printf ("ohh "); break;
case 'u': printf ("you "); break;
}
printf ("\n");
// S2
switch (ch) {
case 'a': printf ("eh? ");
case 'e': printf ("eee ");
case 'i': printf ("eye ");
case 'o': printf ("ohh ");
case 'u': printf ("you ");
}
printf ("\n");
```
What differs in the behaviour (and the final result) of these switch statements?
### Answer
S1 early exits out of the switch as soon as the condition has been met.
S2 doesn't early exit, and even after the condition has been met, it continues checking each case.

What will be printed for each of the following values for ch: u, o, e?
### Answer
ch = u:
you 
ch = o:
ohh 
ch = e:
eee
^ Same for both S1 and S2.

## caseing the joint
Consider the following function to convert a number in the range 0..6 into a weekday name. 0 returns "Sun", 1 returns "Mon", 2 returns "Tue", and so on.
```C
char *numToDay (int n)
{
    assert (0 <= n && n <= 6);
    char *day;
    if (n == 0) {
        day = "Sun";
    } else if (n == 1) {
        day = "Mon";
    } else if (n == 2) {
        day = "Tue";
    } else if (n == 3) {
        day = "Wed";
    } else if (n == 4) {
        day = "Thu";
    } else if (n == 5) {
        day = "Fri";
    } else if (n == 6) {
        day = "Sat";
    }
    return day;
}
```
Suggest at least two alternative, more concise ways of achieving the same result. Include the assert(...) in each case.
### Solution 1: Using Switch
```C
char *numToDay (int n)
{
    assert (0 <= n && n <= 6);
    char *day;
    switch (n) {
    case 0: day = "Sun"; break;
    case 1: day = "Mon"; break;
    case 2: day = "Tue"; break;
    case 3: day = "Wed"; break;
    case 4: day = "Thu"; break;
    case 5: day = "Fri"; break;
    case 6: day = "Sat"; break;
    }
    return day;
}
```
### Solution 2: Using an Array
```C
char *numToDay (int n)
{
    assert (0 <= n && n <= 6);
    char *days = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    return days[n];
}
```

## breaking out
Give an if statement equivalent to the following switch statement:
```C
assert (islower (ch));
switch (ch) {
case 'a':
case 'e':
case 'i':
case 'o':
case 'u':
    printf ("vowel");
    break;
default:
    printf ("consonant");
    break;
}
```
### Solution
```C
if (ch == 'u') {
    printf("vowel");
} else {
    printf("consonant")
}
```

## One good ternary deserves…
Use a conditional expression (a ternary) to replace the if in the following code:
```C
ch = getchar();
if (isdigit (ch))
    type = "digit";
else
    type = "non-digit";
printf ("'%c' is a %s\n", ch, type);
```
How should each of the variables (ch and type) be declared?
### Solution
```C
ch = getchar();
type = isdigit(ch) ? "digit" : "non-digit";
printf ("'%c' is a %s\n", ch, type);
```

## while away the time
What while loop is equivalent to the following for statement?
```C
for (ch = getchar (); ch != EOF; ch = getchar ()) {
    putchar (ch);
}
```
### Solution
```C
ch = getchar ();
while (ch != EOF) {
    putchar (ch);
    ch = getchar ();
}
```

## continue-ity
Consider a function to check whether the elements in an array occur in ascending order. Duplicates are allowed in the array, as long as they are adjacent.

The condition we are testing for can be stated more formally as a post-condition on the function as below:
```C
// Pre:
// - a[] is a valid pointer to the start of an array of ints
// - n is a positive int indicating how many elements in a[]
// Post:
// - return value = ∀ i ∈ { 0 .. n-2 }, a[i] ≤ a[i+1]
bool is_sorted (int *a, int n)
{
    ...
}
```
Implement this function in two styles:
* using a while loop with no break or return, and
* using for, and with a loop early-exit via break or return.
### Solution 1 - using while without early exit
```C
#define TRUE 1
#define FALSE 0

bool is_sorted (int *a, int n)
{
    int i = 0;
    int sorted = TRUE;
    while (i < n-1) {
        if (a[i] > a[i+1]) sorted = FALSE;
        i++;
    }
    return sorted;
}
```
### Solution 1 - using for with early exit
```C
bool is_sorted (int *a, int n)
{
    for (int i; i < n-1; i++)
        if (a[i] > a[i+1]) return FALSE;
    return TRUE;
}
```

When might an early-exit be undesirable?
### Answer
When we want to keep track of how many times / positions of values that are not in ascending order in the array segment.