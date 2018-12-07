////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-14 Chris Joy <z5113243@unsw.edu.au>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "textbuffer.h"

// Doubly Linked List ADT
typedef struct dll *dlink;
struct dll {
  char *data;
  dlink prev;
  dlink next;
};

// Textbuffer ADT
typedef struct textbuffer *Textbuffer;
struct textbuffer {
  dlink cursor; /* current buffer node */
  dlink head;   /* first node in text buffer */
  dlink tail;   /* last node in text buffer */
  size_t size;  /* total number of nodes */
};

// Helper function prototypes
Textbuffer textbuffer_new_node (void);
dlink dlink_new_node (char *data);
void dlink_drop (dlink list);
void print_text (Textbuffer tb);
dlink dlink_lookup (dlink list, size_t index);


// Task 1
Textbuffer textbuffer_new (const char *text)
{
  Textbuffer tb = textbuffer_new_node(); /* init a new textbuffer */
  dlink prev = NULL; /* temp prev node, so we can set dlink->prev */
	char *line, *text_dup, *to_free;
  to_free = text_dup = strdup(text);
  if (*text_dup && text_dup[strlen(text_dup)-1] == '\n')
    text_dup[strlen(text_dup)-1] = '\0'; /* remove trailing new line */
  for (; (line = strsep(&text_dup, "\n")); tb->size++) {
    dlink node = dlink_new_node(line);  /* create  new dlink node */
    if (!tb->head) tb->head = node;     /* set head as first node */
    if (prev) prev->next = node;        /* set pre node's next to the new node */
    node->prev = prev;                  /* set prev */
    prev = node;                        /* new node now becomes prev */
	}
  free(to_free);          /* free duplicate text */
  tb->tail = prev;        /* set tail as the last created node */
  tb->cursor = tb->head;  /* by default, we set the cursor at the head */
  print_text(tb);
  return tb;
}

// Task 2
void textbuffer_drop (Textbuffer tb)
{
  if (!tb) return;
  dlink_drop(tb->head);
  free(tb);
}

// Task 3
size_t textbuffer_lines (Textbuffer tb)
{
  return tb->size;
}

// Task 4
size_t textbuffer_bytes (Textbuffer tb)
{
  size_t bytes = 0;
  for (dlink curr = tb->head; curr; curr = curr->next)
    bytes = bytes + strlen(curr->data) + 1;
  return bytes;
}

// Task 5
char *textbuffer_to_str (Textbuffer tb)
{
  char *buff = NULL;
  size_t buff_len = 0;
  size_t i = 0;
  for (dlink curr = tb->head; curr; curr = curr->next) {
    buff_len = (buff ? strlen(buff) : 0) + strlen(curr->data) + 2;
    buff = realloc(buff, buff_len);
    if (i == 0) strcpy(buff, curr->data);
    if (i > 0) strcat(buff, curr->data);
    strcat(buff, "\n"); /* concatenate new line to end of string */
    i++;
  }
  return buff;
}

// Task 6
void textbuffer_swap (Textbuffer tb, size_t pos1, size_t pos2)
{
  if (pos1 >= tb->size || pos2  >= tb->size) {
    fprintf(stderr, "pos{1|2} out of range");
    abort();
  }

  /* initialise positions in ascending order where p1 < p2 */
  size_t p1; size_t p2;
  if (pos1 < pos2) {
    p1 = pos1; p2 = pos2;
  } else {
    p1 = pos2; p2 = pos1;
  }

  dlink n1 = dlink_lookup(tb->head, p1);
  dlink n2 = dlink_lookup(tb->head, p2);
  dlink t1[] = { n1->prev, n1->next };

  if (n1 == n2) return;

  /* swap textbuffer's head and tail */
  /* CASE: <-[n1]-> <-[]-> <-[]-> <-[]-> <-[n2]-> */
  if (tb->head == n1 && tb->tail == n2) {
    tb->head = n2;
    tb->tail = n1;
  }
  /* CASE: <-[n1]-> <-[]-> <-[]-> <-[n2]-> <-[]-> */
  else if (tb->head == n1 && tb->tail != n2) {
    tb->head = n2;
    n2->next->prev = n1;
  }
  /* CASE: <-[]-> <-[n1]-> <-[]-> <-[]-> <-[n2]-> */
  else if (tb->head != n1 && tb->tail == n2) {
    tb->tail = n1;
    n1->prev->next = n2;
  }
  /* CASE: <-[]-> <-[n1]-> <-[]-> <-[n2]-> <-[]-> */
  else if (tb->head != n1 && tb->tail != n2) {
    n1->prev->next = n2;
    n2->next->prev = n1;
  }

  /* swap inner nodes */
  n1->next->prev = n2;
  n2->prev->next = n1;
  /* swap n1 with n2 */
  n1->prev = n2->prev;
  n1->next = n2->next;
  /* swap n2 with n1 */
  n2->prev = t1[0];
  n2->next = t1[1];

  // puts(n1->data);
  // puts(n2->data);

  // print_text(tb);
}



// Task 7
// Task 8
// Task 9
// Task 10
// Task 11
// Task 12
// Task 13





// Helper Functions Below (ie. functions not part of spec)

// Initialise a new textbuffer
Textbuffer textbuffer_new_node(void)
{
  Textbuffer tb = malloc(sizeof(*tb));
  tb->head = NULL;
  tb->tail = NULL;
  tb->cursor = NULL;
  tb->size = 0;
  return tb;  
}

// Initialise a new doubly-linked list node
dlink dlink_new_node (char *data)
{
  dlink node = malloc(sizeof(*node));
  node->next = NULL;
  node->prev = NULL;
  node->data = malloc(strlen(data) + 1);
  strcpy(node->data, data);
  return node;
}

// Free nodes of doubly-linked list
void dlink_drop (dlink list)
{
	dlink node = NULL;
	while (list) {
		node = list;
		list = list->next;
		free(node);
	}
}

// Linear look up of node in list, given an index
dlink dlink_lookup (dlink list, size_t index)
{
  for (size_t i = 0; list; i++, list = list->next)
    if (i == index) return list;
  return NULL;
}


/**
 * Print the text buffer from start to finish
 * Forwards & Backwards
 */
void print_text (Textbuffer tb)
{
  printf("\n------------------------------------------------------------------\n");
  printf("Size: %zu\n", tb->size);
  printf("Forward: ");
  for (dlink curr = tb->head; curr; curr = curr->next)
    printf("[%s]", curr->data);
  printf("\nBackward: ");
  for (dlink curr = tb->tail; curr; curr = curr->prev)
    printf("[%s]", curr->data);
  printf("\n------------------------------------------------------------------\n");
}
