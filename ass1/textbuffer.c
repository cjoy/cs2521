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
#define TEST_STR_1 "0\n1\n2\n3\n4\n"
#define TEST_STR_2 "this was a triumph.\ni am making a note here...\nHUGE SUCCESS!\n"
#define TEST_STR_3 "the cat sat mat\nthe cat ate hat\ncat had a bat\n"
#define TEST_STR_4 "a+\nb+\nc+\n"
#define TEST_STR_5 "a-\nb-\nc-\n"
#define TEST_STR_6 "a\nb\nc\n"
#define TEST_STR_7 "a\nb\nc\nd\ne\n"

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
  size_t size;  /* total number of nodes in text buffer */
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

// Replace string match and dynamically resize new string buffer
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
      assert (tb->head == tb->tail);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing consecutive new lines");
      Textbuffer tb = textbuffer_new ("\n\n\n");
      assert (tb->size == 3);
      assert (tb->head != tb->tail);
      assert (strcmp (tb->head->data, "") == 0);
      assert (strcmp (tb->head->next->data, "") == 0);
      assert (strcmp (tb->head->next->next->data, "") == 0);
      assert (strcmp (tb->head->next->next->data, "") == 0);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing string with consecutive new lines");
      Textbuffer tb = textbuffer_new ("hello world\nanother one\n\nblah\n");
      assert (tb->size == 4);
      assert (strcmp (tb->head->data, "hello world") == 0);
      assert (tb->head == tb->head->next->prev);
      assert (tb->head->next == tb->head->next->next->prev);
      assert (strcmp (tb->head->data, "hello world") == 0);
      assert (strcmp (tb->head->next->data, "another one") == 0);
      assert (strcmp (tb->head->next->next->data, "") == 0);
      assert (strcmp (tb->head->next->next->next->data, "blah") == 0);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing string that terminates early");
      Textbuffer tb = textbuffer_new ("this is cool\nblah blah\n\0\nblah\n");
      assert (tb->size == 2);
      assert (tb->head == tb->head->next->prev);
      assert (tb->head->next == tb->tail);
      assert (strcmp (tb->head->data, "this is cool") == 0);
      assert (strcmp (tb->head->next->data, "blah blah") == 0);
      textbuffer_drop (tb);
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_bytes ():");
    {
      puts ("- testing empty text buffer");
      Textbuffer tb = textbuffer_new (EMPTY_STR);
      assert (textbuffer_bytes (tb) == strlen (EMPTY_STR) + 1);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing simple multiline text buffer");
      Textbuffer tb = textbuffer_new (TEST_STR_6);
      assert (textbuffer_bytes (tb) == strlen (TEST_STR_6));
      textbuffer_drop (tb);
    }
    {
      puts ("- testing multiple empty lines");
      const char *str = "\n\n\n\n\n\n\n\n";
      Textbuffer tb = textbuffer_new (str);
      assert (textbuffer_bytes (tb) == strlen (str));
      textbuffer_drop (tb);
    }
    {
      puts ("- testing multiline / empty line text buffer");
      Textbuffer tb = textbuffer_new ("1\n2\n3\n4\n5\n6\ninserting\nlinked\n\nlist\n");
      assert (textbuffer_bytes (tb) == 35);
      textbuffer_drop (tb);
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_to_str ():");
    {
      puts ("- testing an empty textbuffer");
      Textbuffer tb = textbuffer_new (EMPTY_STR);
      assert (strcmp (textbuffer_to_str (tb), "\n") == 0);
      assert (tb->size == 1);
      assert (tb->head == tb->tail);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing one line textbuffer");
      const char* str = "this is a one line textbuffer\n";
      Textbuffer tb = textbuffer_new (str);
      assert (strcmp (textbuffer_to_str (tb), str) == 0);
      assert (tb->size == 1);
      assert (tb->head == tb->tail);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing a textbuffer with consecutive new lines");
      const char* str = "\n\n\n435\n3234\n";
      Textbuffer tb = textbuffer_new (str);
      assert (strcmp (textbuffer_to_str (tb), str) == 0);
      Textbuffer tb_clone = textbuffer_new (textbuffer_to_str (tb));
      assert (tb->size == tb_clone->size);
      textbuffer_drop (tb);
      textbuffer_drop (tb_clone);
    }
    {
      puts ("- testing a textbuffer with consecutive new lines");
      const char* str = "\n\n\n435\n3234\ntest\n\n\n";
      Textbuffer tb = textbuffer_new (str);
      assert (strcmp (textbuffer_to_str (tb), str) == 0);
      Textbuffer tb_clone = textbuffer_new (textbuffer_to_str (tb));
      assert (tb->size == tb_clone->size);
      textbuffer_drop (tb);
      textbuffer_drop (tb_clone);
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_swap ():");
    {
  		puts ("- testing case: H <-[]-> <-[pos1]-> <-[]-> <-[pos3]-> <-[]-> T");
      Textbuffer tb = textbuffer_new (TEST_STR_1);
      size_t pos1 = 1;
      size_t pos2 = 3;
      dlink n1 = dlink_lookup (tb->head, pos1);
      dlink n2 = dlink_lookup (tb->head, pos2);
      textbuffer_swap (tb, pos1, pos2);
      assert (strcmp (textbuffer_to_str (tb), "0\n3\n2\n1\n4\n") == 0);
      assert (n1 == dlink_lookup (tb->head, pos2));
      assert (n2 == dlink_lookup (tb->head, pos1));
      textbuffer_drop (tb);
    }
    {
  		puts ("- testing case: H <-[pos0]-> <-[]-> <-[]-> <-[]-> <-[pos4]-> T");
      Textbuffer tb = textbuffer_new (TEST_STR_1);
      size_t pos1 = 0;
      size_t pos2 = 4;
      dlink n1 = dlink_lookup (tb->head, pos1);
      dlink n2 = dlink_lookup (tb->head, pos2);
      textbuffer_swap (tb, pos1, pos2);
      assert (strcmp (textbuffer_to_str (tb), "4\n1\n2\n3\n0\n") == 0);
      assert (n1 == dlink_lookup (tb->head, pos2));
      assert (n2 == dlink_lookup (tb->head, pos1));
      textbuffer_drop (tb);
    }
    {
  		puts ("- testing case: H <-[pos0]-> <-[]-> <-[]-> <-[pos3]-> <-[]-> T");
      Textbuffer tb = textbuffer_new (TEST_STR_1);
      size_t pos1 = 0;
      size_t pos2 = 3;
      dlink n1 = dlink_lookup (tb->head, pos1);
      dlink n2 = dlink_lookup (tb->head, pos2);
      textbuffer_swap (tb, pos1, pos2);
      assert (strcmp (textbuffer_to_str (tb), "3\n1\n2\n0\n4\n") == 0);
      assert (n1 == dlink_lookup (tb->head, pos2));
      assert (n2 == dlink_lookup (tb->head, pos1));
      textbuffer_drop (tb);
    }
    {
  		puts ("- testing case: H <-[]-> <-[pos1]-> <-[]-> <-[]-> <-[pos4]-> T");
      Textbuffer tb = textbuffer_new (TEST_STR_1);
      size_t pos1 = 1;
      size_t pos2 = 4;
      dlink n1 = dlink_lookup (tb->head, pos1);
      dlink n2 = dlink_lookup (tb->head, pos2);
      textbuffer_swap (tb, pos1, pos2);
      assert (strcmp (textbuffer_to_str (tb), "0\n4\n2\n3\n1\n") == 0);
      assert (n1 == dlink_lookup (tb->head, pos2));
      assert (n2 == dlink_lookup (tb->head, pos1));
      textbuffer_drop (tb);
    }
    {
  		puts ("- testing case: H <-[]-> <-[pos1]-> <-[pos2]-> <-[]-> <-[]-> T");
      Textbuffer tb = textbuffer_new (TEST_STR_1);
      size_t pos1 = 1;
      size_t pos2 = 2;
      dlink n1 = dlink_lookup (tb->head, pos1);
      dlink n2 = dlink_lookup (tb->head, pos2);
      textbuffer_swap (tb, pos1, pos2);
      assert (strcmp (textbuffer_to_str (tb), "0\n2\n1\n3\n4\n") == 0);
      assert (n1 == dlink_lookup (tb->head, pos2));
      assert (n2 == dlink_lookup (tb->head, pos1));
      textbuffer_drop (tb);
    }
    {
		puts ("- testing case: H <-[pos0]-> <-[pos1]-> <-[]-> <-[]-> <-[]-> T");
      Textbuffer tb = textbuffer_new (TEST_STR_1);
      size_t pos1 = 0;
      size_t pos2 = 1;
      dlink n1 = dlink_lookup (tb->head, pos1);
      dlink n2 = dlink_lookup (tb->head, pos2);
      textbuffer_swap (tb, pos1, pos2);
      assert (strcmp (textbuffer_to_str (tb), "1\n0\n2\n3\n4\n") == 0);
      assert (n1 == dlink_lookup (tb->head, pos2));
      assert (n2 == dlink_lookup (tb->head, pos1));
      textbuffer_drop (tb);
    }
    {
  		puts ("- testing case: H <-[]-> <-[]-> <-[]-> <-[pos3]-> <-[pos4]-> T");
      Textbuffer tb = textbuffer_new (TEST_STR_1);
      size_t pos1 = 3;
      size_t pos2 = 4;
      dlink n1 = dlink_lookup (tb->head, pos1);
      dlink n2 = dlink_lookup (tb->head, pos2);
      textbuffer_swap (tb, pos1, pos2);
      assert (strcmp (textbuffer_to_str (tb), "0\n1\n2\n4\n3\n") == 0);
      assert (n1 == dlink_lookup (tb->head, pos2));
      assert (n2 == dlink_lookup (tb->head, pos1));
      textbuffer_drop (tb);
    }
    {
  		puts ("- testing case: H <-[]-> <-[]-> <-[]-> <-[pos3|pos3]-> <-[]-> T");
      Textbuffer tb = textbuffer_new (TEST_STR_1);
      size_t pos1 = 3;
      size_t pos2 = 3;
      dlink n1 = dlink_lookup (tb->head, pos1);
      dlink n2 = dlink_lookup (tb->head, pos2);
      textbuffer_swap (tb, pos1, pos2);
      assert (strcmp (textbuffer_to_str (tb), "0\n1\n2\n3\n4\n") == 0);
      assert (n1 == dlink_lookup (tb->head, pos2));
      assert (n2 == dlink_lookup (tb->head, pos1));
      textbuffer_drop (tb);
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_insert ():");
    {
      puts ("- testing front insertion");
      Textbuffer tb1 = textbuffer_new (TEST_STR_4);
      Textbuffer tb2 = textbuffer_new (TEST_STR_5);
      textbuffer_insert (tb1, 0, tb2);
      assert (strcmp (textbuffer_to_str (tb1), "a-\nb-\nc-\na+\nb+\nc+\n") == 0);
      assert (tb1->head == tb2->head);
      assert (tb1->size == 6);
      textbuffer_drop (tb1);
    }
    {
      puts ("- testing back insertion");
      Textbuffer tb1 = textbuffer_new (TEST_STR_4);
      Textbuffer tb2 = textbuffer_new (TEST_STR_5);
      textbuffer_insert (tb1, 3, tb2);
      assert (strcmp (textbuffer_to_str (tb1), "a+\nb+\nc+\na-\nb-\nc-\n") == 0);
      assert (tb1->tail == tb2->tail);
      assert (tb1->size == 6);
      textbuffer_drop (tb1);
    }
    {
      puts ("- testing somewhere in the middle");
      Textbuffer tb1 = textbuffer_new (TEST_STR_4);
      Textbuffer tb2 = textbuffer_new (TEST_STR_5);
      textbuffer_insert (tb1, 2, tb2);
      assert (tb1->size == 6);
      assert (strcmp (textbuffer_to_str (tb1), "a+\nb+\na-\nb-\nc-\nc+\n") == 0);
      textbuffer_drop (tb1);
    }
    {
      puts ("- testing insert single line tb2 into multiline tb1 middle");
      Textbuffer tb1 = textbuffer_new (TEST_STR_6);
      Textbuffer tb2 = textbuffer_new ("yep\n");
      textbuffer_insert (tb1, 2, tb2);
      assert (tb1->size == 4);
      assert (strcmp (textbuffer_to_str (tb1), "a\nb\nyep\nc\n") == 0);
      textbuffer_drop (tb1);
    }	
    {
      puts ("- testing insert single line tb2 into multiline tb1 start");
      Textbuffer tb1 = textbuffer_new (TEST_STR_6);
      Textbuffer tb2 = textbuffer_new ("yep\n");
      textbuffer_insert (tb1, 0, tb2);
      assert (tb1->head == tb2->head);
      assert (tb1->size == 4);
      assert (strcmp (textbuffer_to_str (tb1), "yep\na\nb\nc\n") == 0);
      textbuffer_drop (tb1);
    }	
    {
      puts ("- testing insert single line tb2 into multiline tb1 end");
      Textbuffer tb1 = textbuffer_new (TEST_STR_6);
      Textbuffer tb2 = textbuffer_new ("yep\n");
      textbuffer_insert (tb1, 3, tb2);
      assert (tb1->size == 4);
      assert (strcmp (textbuffer_to_str (tb1), "a\nb\nc\nyep\n") == 0);
      textbuffer_drop (tb1);
    }	
    {
      puts ("- testing insert multi-line line tb2 into single tb1 start");
      Textbuffer tb1 = textbuffer_new ("yep\n");
      Textbuffer tb2 = textbuffer_new (TEST_STR_6);
      textbuffer_insert (tb1, 0, tb2);
      assert (tb1->head == tb2->head);
      assert (tb1->size == 4);
      assert (strcmp (textbuffer_to_str (tb1), "a\nb\nc\nyep\n") == 0);
      textbuffer_drop (tb1);
    }
    {
      puts ("- testing insert multi-line line tb2 into single tb1 end");
      Textbuffer tb1 = textbuffer_new ("yep\n");
      Textbuffer tb2 = textbuffer_new (TEST_STR_6);
      textbuffer_insert (tb1, 1, tb2);
      assert (tb2->tail == tb1->tail);
      assert (tb1->size == 4);
      assert (strcmp (textbuffer_to_str (tb1), "yep\na\nb\nc\n") == 0);
      textbuffer_drop (tb1);
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_paste ():");
    {
      puts ("- testing pasting into an empty textbuffer");
      Textbuffer tb1 = textbuffer_new (EMPTY_STR);
      Textbuffer tb2 = textbuffer_new (TEST_STR_6);
      textbuffer_paste (tb1, 0, tb2);
      assert (tb1->size == 4);
      assert (strcmp (textbuffer_to_str (tb1), "a\nb\nc\n\n") == 0);
      assert (tb2->size == 3);
      assert (strcmp (textbuffer_to_str (tb2), TEST_STR_6) == 0);
      assert (strcmp (tb1->head->data, tb2->head->data) == 0);
      assert (tb1->head != tb2->head);
      assert (tb1->tail != tb2->tail);
      textbuffer_drop (tb1);
      textbuffer_drop (tb2);
    }
    {
      puts ("- testing pasting a textbuffer of equal length into another textbuffer");
      Textbuffer tb1 = textbuffer_new (TEST_STR_4);
      Textbuffer tb2 = textbuffer_new (TEST_STR_5);
      textbuffer_paste (tb1, 2, tb2);
      assert (tb1->size == 6);
      assert (strcmp (textbuffer_to_str (tb1), "a+\nb+\na-\nb-\nc-\nc+\n") == 0);
      assert (tb2->size == 3);
      assert (strcmp (textbuffer_to_str (tb2), TEST_STR_5) == 0);
      textbuffer_drop (tb1);
      textbuffer_drop (tb2);
    }
    {
      puts ("- testing pasting a textbuffer into the end");
      Textbuffer tb1 = textbuffer_new (TEST_STR_6);
      Textbuffer tb2 = textbuffer_new ("d\ne\nf\n");
      textbuffer_paste (tb1, 3, tb2);
      assert (tb1->size == 6);
      assert (strcmp (textbuffer_to_str (tb1), "a\nb\nc\nd\ne\nf\n") == 0);
      assert (tb2->size == 3);
      assert (strcmp (textbuffer_to_str (tb2), "d\ne\nf\n") == 0);
      textbuffer_drop (tb1);
      textbuffer_drop (tb2);
    }
    {
      puts ("- testing pasting a textbuffer into the start");
      Textbuffer tb1 = textbuffer_new (TEST_STR_6);
      Textbuffer tb2 = textbuffer_new ("d\ne\nf\n");
      textbuffer_paste (tb1, 0, tb2);
      assert (tb1->size == 6);
      assert (strcmp (textbuffer_to_str (tb1), "d\ne\nf\na\nb\nc\n") == 0);
      assert (tb2->size == 3);
      assert (strcmp (textbuffer_to_str (tb2), "d\ne\nf\n") == 0);
      assert (tb1->head != tb2->head);
      textbuffer_drop (tb1);
      textbuffer_drop (tb2);
    }    
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_cut ():");
    {
      puts ("- testing cutting an one-line textbuffer");
      Textbuffer tb = textbuffer_new (EMPTY_STR);
      assert (tb->head != NULL);
      assert (tb->tail != NULL);
      Textbuffer cut = textbuffer_cut (tb, 0, 0);
      assert (strcmp (textbuffer_to_str (tb), EMPTY_STR) == 0);
      assert (strcmp (textbuffer_to_str (cut), "\n") == 0);
      assert (tb->size == 0);
      assert (cut->size == 1);
      assert (tb->head == NULL);
      assert (tb->tail == NULL);
      textbuffer_drop (tb);
      textbuffer_drop (cut);
    }
    {
      puts ("- testing cutting a section within the middle");
      Textbuffer tb = textbuffer_new (TEST_STR_7);
      Textbuffer cut = textbuffer_cut (tb, 1, 3);
      assert (strcmp (textbuffer_to_str (tb), "a\ne\n") == 0);
      assert (strcmp (textbuffer_to_str (cut), "b\nc\nd\n") == 0);
      assert (tb->size == 2);
      assert (cut->size == 3);
      textbuffer_drop (tb);
      textbuffer_drop (cut);
    }
    {
      puts ("- testing cutting a section from the beginning to middle");
      Textbuffer tb = textbuffer_new (TEST_STR_7);
      Textbuffer cut = textbuffer_cut (tb, 0, 2);
      assert (strcmp (textbuffer_to_str (tb), "d\ne\n") == 0);
      assert (strcmp (textbuffer_to_str (cut), TEST_STR_6) == 0);
      assert (tb->size == 2);
      assert (cut->size == 3);
      textbuffer_drop (tb);
      textbuffer_drop (cut);
    }
    {
      puts ("- testing cutting a section from the middle to end");
      Textbuffer tb = textbuffer_new (TEST_STR_7);
      Textbuffer cut = textbuffer_cut (tb, 2, 4);
      assert (strcmp (textbuffer_to_str (tb), "a\nb\n") == 0);
      assert (strcmp (textbuffer_to_str (cut), "c\nd\ne\n") == 0);
      assert (tb->size == 2);
      assert (cut->size == 3);
      textbuffer_drop (tb);
      textbuffer_drop (cut);
    }
    {
      puts ("- testing cutting the whole textbuffer");
      Textbuffer tb = textbuffer_new (TEST_STR_7);
      Textbuffer cut = textbuffer_cut (tb, 0, 4);
      assert (strcmp (textbuffer_to_str (tb), EMPTY_STR) == 0);
      assert (strcmp (textbuffer_to_str (cut), TEST_STR_7) == 0);
      assert (tb->size == 0);
      assert (cut->size == 5);
      textbuffer_drop (tb);
      textbuffer_drop (cut);
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_copy ():");
    {
      puts ("- testing copy an empty line");
      Textbuffer tb = textbuffer_new (EMPTY_STR);
      Textbuffer cp = textbuffer_copy (tb, 0, 0);
      assert (strcmp (textbuffer_to_str (cp), "\n") == 0);
      assert (tb->size == 1);
      assert (cp->size == 1);
      textbuffer_drop (tb);
      textbuffer_drop (cp);
    }
    {
      puts ("- testing simple copy");
      Textbuffer tb = textbuffer_new (TEST_STR_7);
      Textbuffer cp = textbuffer_copy (tb, 1, 3);
      assert (strcmp (textbuffer_to_str (cp), "b\nc\nd\n") == 0);
      assert (tb->size == 4);
      assert (cp->size == 3);
      textbuffer_drop (tb);
      textbuffer_drop (cp);
    }
    {
      puts ("- testing copy whole textbuffer");
      const char *str = TEST_STR_7;
      Textbuffer tb = textbuffer_new (str);
      Textbuffer cp = textbuffer_copy (tb, 0, 4);
      assert (strcmp (textbuffer_to_str (cp), str) == 0);
      assert (tb->size == 4);
      assert (cp->size == 4);
      textbuffer_drop (tb);
      textbuffer_drop (cp);
    }
    {
      puts ("- testing copy one line");
      Textbuffer tb = textbuffer_new (TEST_STR_7);
      Textbuffer cp = textbuffer_copy (tb, 1, 1);
      assert (strcmp (textbuffer_to_str (cp), "b\n") == 0);
      assert (tb->size == 4);
      assert (cp->size == 1);
      assert (cp->head == cp->tail);
      textbuffer_drop (tb);
      textbuffer_drop (cp);
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_delete ():");
    {
      puts ("- testing deleting only one line in one line textbuffer");
      Textbuffer tb = textbuffer_new ("a\n");
      textbuffer_delete (tb, 0, 0);
      assert (strcmp (textbuffer_to_str (tb), EMPTY_STR) == 0);
      assert (tb->size == 0);
      assert (tb->head == tb->tail);      
      textbuffer_drop (tb);
    }
    {
      puts ("- testing deleting first line in two line textbuffer");
      Textbuffer tb = textbuffer_new ("a\nb\n");
      textbuffer_delete (tb, 0, 0);
      assert (strcmp (textbuffer_to_str (tb), "b\n") == 0);
      assert (tb->size == 1);
      assert (tb->head == tb->tail);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing deleting tail in two line textbuffer");
      Textbuffer tb = textbuffer_new ("a\nb\n");
      textbuffer_delete (tb, 1, 1);	
      assert (strcmp (textbuffer_to_str (tb), "a\n") == 0);
      assert (tb->size == 1);
      assert (tb->head == tb->tail);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing delete all lines");
      Textbuffer tb = textbuffer_new (TEST_STR_7);
      assert (tb->size == 5);
      textbuffer_delete (tb, 0, 4);
      assert (strcmp (textbuffer_to_str (tb), EMPTY_STR) == 0);
      assert (tb->size == 0);
      assert (tb->head == tb->tail);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing delete from first line to middle");
      Textbuffer tb = textbuffer_new (TEST_STR_7);
      assert (tb->size == 5);
      textbuffer_delete (tb, 0, 2);
      assert (strcmp (textbuffer_to_str (tb), "d\ne\n") == 0);
      assert (tb->size == 2);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing delete from middle line to last line");
      Textbuffer tb = textbuffer_new (TEST_STR_7);
      assert (tb->size == 5);
      textbuffer_delete (tb, 2, 4);
      assert (strcmp (textbuffer_to_str (tb), "a\nb\n") == 0);
      assert (tb->size == 2);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing delete multiple middle lines");
      Textbuffer tb = textbuffer_new (TEST_STR_7);
      assert (tb->size == 5);
      textbuffer_delete (tb, 1, 3);	
      assert (strcmp (textbuffer_to_str (tb), "a\ne\n") == 0);
      assert (tb->size == 2);
      textbuffer_drop (tb);
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_search ():");
    {
      puts ("- testing a simple text buffer");
      Textbuffer tb = textbuffer_new (TEST_STR_3);
      assert (textbuffer_search (tb, "cat", false) == 3);
      assert (textbuffer_search (tb, "sat", false) == 1);
      assert (textbuffer_search (tb, "the", false) == 2);
      assert (textbuffer_search (tb, "banana", false) == -1);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing a simple text buffer in reverse");
      Textbuffer tb = textbuffer_new (TEST_STR_3);
      assert (textbuffer_search (tb, "cat", true) == 3);
      assert (textbuffer_search (tb, "sat", true) == 1);
      assert (textbuffer_search (tb, "the", true) == 2);
      assert (textbuffer_search (tb, "banana", true) == -1);
      textbuffer_drop (tb);
    }
    puts (EMPTY_STR);
  }
  {
    puts ("textbuffer_replace ():");
    {
      puts ("- testing replace empty match with text buffer");
      Textbuffer tb = textbuffer_new (TEST_STR_2);
      textbuffer_replace (tb, EMPTY_STR, "cat");
      assert (strcmp (textbuffer_to_str (tb), TEST_STR_2) == 0);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing replace non-empty match with empty text buffer");
      Textbuffer tb = textbuffer_new (TEST_STR_3);
      textbuffer_replace (tb, "cat", EMPTY_STR);
      assert (strcmp (textbuffer_to_str (tb), "the  sat mat\nthe  ate hat\n had a bat\n") == 0);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing replacing a multiple line textbuffer");
      Textbuffer tb = textbuffer_new (TEST_STR_3);
      textbuffer_replace (tb, "cat", "dog");
      assert (strcmp (textbuffer_to_str (tb), "the dog sat mat\nthe dog ate hat\ndog had a bat\n") == 0);
      textbuffer_drop (tb);
    }
    {
      puts ("- testing replacing a multiple line textbuffer of different size");
      Textbuffer tb = textbuffer_new (TEST_STR_3);
      size_t pre_bytes = textbuffer_bytes (tb);
      size_t pre_size = tb->size;
      textbuffer_replace (tb, "cat", "elephant");
      size_t post_bytes = textbuffer_bytes (tb);
      size_t post_size = tb->size;
      assert (strcmp (textbuffer_to_str (tb), "the elephant sat mat\nthe elephant ate hat\nelephant had a bat\n") == 0);
      assert (pre_bytes < post_bytes);
      assert (pre_size == post_size);
      textbuffer_drop (tb);
    }
    puts (EMPTY_STR);
  }
}

