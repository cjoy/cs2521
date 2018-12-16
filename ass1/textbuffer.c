////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-14 Chris Joy <z5113243@unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "textbuffer.h"

#define EMPTY_STR ""

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
  dlink head;   /* first node in text buffer */
  dlink tail;   /* last node in text buffer */
  size_t size;  /* total number of nodes */
};

// Helper function prototypes
Textbuffer textbuffer_new_node (void);
dlink dlink_new_node (char *data);
size_t dlink_drop (dlink list);
dlink dlink_lookup (dlink list, size_t index);
char *str_replace (const char *string, const char *match, const char *replace);

// Task 1
Textbuffer textbuffer_new (const char *text)
{
  Textbuffer tb = textbuffer_new_node (); /* init a new textbuffer */
  dlink prev = NULL; /* temp prev node, so we can set dlink->prev */
	char *line, *text_dup, *to_free;
  to_free = text_dup = strdup (text);
  if (*text_dup && text_dup[strlen (text_dup)-1] == '\n')
    text_dup[strlen (text_dup)-1] = '\0'; /* remove trailing new line */
  for (; (line = strsep (&text_dup, "\n")); tb->size++) {
    dlink node = dlink_new_node (line); /* create  new dlink node */
    if (!tb->head) tb->head = node;     /* set head as first node */
    if (prev) prev->next = node;        /* set pre node's next to the new node */
    node->prev = prev;                  /* set prev */
    prev = node;                        /* new node now becomes prev */
	}
  free (to_free);          /* free duplicate text */
  tb->tail = prev;        /* set tail as the last created node */
  return tb;
}

// Task 2
void textbuffer_drop (Textbuffer tb)
{
  if (!tb) return;
  dlink_drop (tb->head);
  free (tb);
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
    bytes += strlen (curr->data) + 1; /* + 1 for new line */
  return bytes;
}

// Task 5
char *textbuffer_to_str (Textbuffer tb)
{
  char *buff = NULL;
  size_t buff_len = 0;
  size_t i = 0;
  for (dlink curr = tb->head; curr; curr = curr->next, i++) {
    buff_len = (buff ? strlen (buff) : 0) + strlen (curr->data) + 2;
    buff = realloc (buff, buff_len);
    if (i == 0) strcpy (buff, curr->data);
    if (i > 0) strcat (buff, curr->data);
    strcat (buff, "\n"); /* concatenate new line to end of string */
  }
  char *result = buff;
  if (i == 0) {
    result = malloc (sizeof (char*));
    strcpy (result, "");
  }
  return result;
}

// Task 6
void textbuffer_swap (Textbuffer tb, size_t pos1, size_t pos2)
{
  if (pos1 >= tb->size || pos2  >= tb->size) {
    fprintf (stderr, "pos{1|2} out of range");
    abort ();
  }
  /* initialise positions in ascending order where p1 < p2 */
  size_t p1; size_t p2;
  if (pos1 < pos2) {
    p1 = pos1; p2 = pos2;
  } else {
    p1 = pos2; p2 = pos1;
  }
  /* retrieve nodes */
  dlink A = dlink_lookup (tb->head, p1);
  dlink B = dlink_lookup (tb->head, p2);
  /* if nodes are the same do nothing */
  if (A == B) return;
  /* change head and tail if swap node at ends of list */
  if (tb->head == A) tb->head = B;
  if (tb->tail == B) tb->tail = A;
  /* tmp array keeps track of A & B links */
  dlink tmp[] = { A->prev, B->prev, A->next, B->next };
  /* if neighbors no need to replace outer nodes... */
  if (( A->next == B && B->prev == A ) || ( A->prev == B && B->next == A )) {
    A->prev = tmp[2];
    B->prev = tmp[0];
    A->next = tmp[3];
    B->next = tmp[1];
  } else {
    A->prev = tmp[1];
    B->prev = tmp[0];
    A->next = tmp[3];
    B->next = tmp[2];
  }
  /* relink outer nodes if they exist */
  if (A->prev) A->prev->next = A;
  if (A->next) A->next->prev = A;
  if (B->prev) B->prev->next = B;
  if (B->next) B->next->prev = B;
}

// Task 7
void textbuffer_insert (Textbuffer tb1, size_t pos, Textbuffer tb2)
{
  assert(tb1);
  assert(tb2);
  if (tb1->size < pos) {
    fprintf (stderr, "pos out of range");
    abort ();
  }

  /* account for edge cases */
  if (tb1 == tb2) return;
  if (tb1->size == 0) { tb1 = tb2; return; } 
  if (tb2->size == 0) return;

  dlink A_start = dlink_lookup (tb1->head, pos);
  dlink B_start = tb2->head;
  dlink B_end = tb2->tail;

  if (pos == 0) {
    /* inserting at start of tb1 */
    tb1->head = B_start;
    B_end->next = A_start;
    A_start->prev = B_end;
  } else if (pos == tb1->size) {
    /* inserting at end of tb1 */
    tb2->head->prev = tb1->tail;
    tb1->tail->next = tb2->head;
    tb1->tail = tb2->tail;
  } else {
    /* somewhere in the middle */
    A_start->prev->next = B_start;
    B_end->next = A_start;
    B_start->prev = A_start->prev;
    A_start->prev = B_end;
  }
 
  tb1->size += tb2->size;
}

// Task 8
void textbuffer_paste (Textbuffer tb1, size_t pos, Textbuffer tb2)
{
  textbuffer_insert (tb1, pos, textbuffer_new (textbuffer_to_str (tb2)));
}

// Task 9
Textbuffer textbuffer_cut (Textbuffer tb, size_t from, size_t to)
{
  Textbuffer tb_copy = textbuffer_copy (tb, from, to);
  textbuffer_delete (tb, from, to);
  return tb_copy;
}

// Task 10
Textbuffer textbuffer_copy (Textbuffer tb, size_t from, size_t to)
{
  if (from > to || tb->size-1 < to || tb->size-1 < from) {
    fprintf (stderr, "'from' or 'to' out of range");
    abort ();
  }
  Textbuffer tb_copy = textbuffer_new_node ();
  dlink prev = NULL;
  dlink curr = tb->head;
  for (size_t i = 0; curr; curr = curr->next, i++) {
    if (from <= i && i <= to) {
      dlink node = dlink_new_node (curr->data);
      if (!tb_copy->head) tb_copy->head = node;
      if (prev) prev->next = node;
      node->prev = prev;
      prev = node;
      tb_copy->size++;
    }
  }
  tb_copy->tail = prev;
  return tb_copy;
}

// Task 11
void textbuffer_delete (Textbuffer tb, size_t from, size_t to)
{
  if (tb->size-1 < from || tb->size-1 < to) {
    fprintf (stderr, "'from' or 'to' out of range");
    abort ();
  }
  if (from > to) return;

  dlink from_node = dlink_lookup (tb->head, from);
  dlink to_node = dlink_lookup (tb->head, to);

  if (tb->head == from_node && tb->tail == to_node) {
    tb->head = NULL;
    tb->tail = NULL;
  } else if (tb->head == from_node) {
    tb->head = to_node->next;
    to_node->next->prev = NULL; 
    to_node->next = NULL;
  } else if (tb->tail == to_node) {
    tb->tail = from_node->prev;
    from_node->prev->next = NULL;
  } else {
    from_node->prev->next = to_node->next;
    to_node->next->prev = from_node->prev;
    to_node->next = NULL;
  }

  tb->size -= dlink_drop (from_node);
}


// Task 12
ssize_t textbuffer_search (Textbuffer tb, char *match, bool rev)
{
  ssize_t found = 0;
  dlink curr = rev ? tb->tail : tb->head;
  for (; curr; curr = rev ? curr->prev : curr->next)
    if (strstr (curr->data, match)) found++;
  return (found == 0 ? -1 : found);
}

// Task 13
void textbuffer_replace (Textbuffer tb, char *match, char *replace)
{
  assert(tb);
  if (strcmp(match, "") == 0) return;
  for (dlink curr = tb->head; curr; curr = curr->next)
    if (strstr (curr->data, match)) {
      char *old = curr->data;
      curr->data = str_replace(curr->data, match, replace);
      free(old);
    }
}


// Helper Functions

// Initialise a new textbuffer
Textbuffer textbuffer_new_node(void)
{
  Textbuffer tb = malloc (sizeof (*tb));
  tb->head = NULL;
  tb->tail = NULL;
  tb->size = 0;
  return tb;
}

// Initialise a new doubly-linked list node
dlink dlink_new_node (char *data)
{
  dlink node = malloc (sizeof (*node));
  node->next = NULL;
  node->prev = NULL;
  node->data = malloc (strlen (data) + 1);
  strcpy (node->data, data);
  return node;
}

// Free nodes of doubly-linked list
size_t dlink_drop (dlink list)
{
  size_t i = 0;
  for (dlink next = NULL; list; list = next, i++) {
    next = list->next;
    free (list);
  }
  return i;
}

// Linear look up of node in list, given an index
dlink dlink_lookup (dlink list, size_t index)
{
  for (size_t i = 0; list; i++, list = list->next)
    if (i == index) return list;
  return NULL;
}

// Given a array to a string, create a new array buffer that 
// replaces matches with the given string.
char *str_replace (const char *string, const char *match, const char *replace) 
{
  size_t i, len = 0;
  size_t replacelen = strlen (replace);
  size_t matchlen = strlen (match);
  /* count occurrences of new string */ 
  for (i = 0; string[i] != '\0'; i++) {
    if (strstr (&string[i], match) == &string[i]) {
      len++;
      i += matchlen - 1;
    }
  }
  /* allocate block for new string */
  char *result = malloc (i + len * (replacelen - matchlen) + 1); 
  i = 0;
  while (*string) { 
    /* compare the substring with the result */
    if (strstr (string, match) == string) { 
      strcpy (&result[i], replace); 
      i += replacelen;
      string += matchlen;
    }
    else result[i++] = *string++; 
  }
  result[i] = '\0'; 
  return result; 
}

// White-box tests
void white_box_tests ()
{
  {
    puts ("textbuffer_new ():");
    {
      puts ("- testing empty string");
      Textbuffer tb = textbuffer_new (EMPTY_STR);
      assert (tb->size == 1);
      assert (tb->head = tb->tail);
      textbuffer_drop (tb);
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_bytes ():");
    {
      puts ("- testing ");
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_to_str ():");
    {
      puts ("- testing ");
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_swap ():");
    {
      puts ("- testing ");
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_insert ():");
    {
      puts ("- testing ");
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_paste ():");
    {
      puts ("- testing ");
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_cut ():");
    {
      puts ("- testing ");
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_copy ():");
    {
      puts ("- testing ");
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_delete ():");
    {
      puts ("- testing ");
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_search ():");
    {
      puts ("- testing ");
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_replace ():");
    {
      puts ("- testing ");
    }
    puts (EMPTY_STR);
  }
}

