////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-14 Chris Joy <z5113243@unsw.edu.au>

#include <stdio.h> /* Remove before submission */
#include "textbuffer.h"


typedef struct dll *dlink;
struct dll {
  char *data;
  // dlink prev;
  dlink next;
};

struct textbuffer {
  dlink cursor; /* current buffer node */
  dlink head; /* first node in text buffer */
  dlink tail;  /* last node in text buffer */
  size_t size; /* total number of nodes */
};

Textbuffer textbuffer_new (const char *text)
{
  Textbuffer tb = malloc(sizeof(*tb));
  dlink curr = malloc(sizeof(struct dll));;
  tb->head = curr;

	char *line, *text_dup, *to_free;
  to_free = text_dup = strdup(text);
  for (size_t i = 0; (line = strsep(&text_dup, "\n")); i++) {

    // code here
    curr->data = (char *)malloc(strlen(line) + 1);
    strcpy(curr->data, line);


    curr->next = malloc(sizeof(struct dll));
    curr = curr->next;


	}
  free(to_free);
  
  for (dlink cur = tb->head; cur; cur=cur->next)
    printf("[%s]->", cur->data);
  
  return tb;
}


// Textbuffer textbuffer_new (const char *text)
// {
// 	char *line, *text_dup, *to_free;
//   to_free = text_dup = strdup(text);
//   for (size_t i = 0; (line = strsep(&text_dup, "\n")); i++) {

// 	}
//   free(to_free);
//   return NULL;
// }








#if 0
struct textbuffer {
  char *line;
  Textbuffer prev;
  Textbuffer next;
};

Textbuffer textbuffer_new (const char *text)
{
	char *line, *text_dup, *to_free;
  to_free = text_dup = strdup(text);
  Textbuffer prev = NULL;
  Textbuffer new_node = malloc(sizeof(struct textbuffer));
  Textbuffer head = new_node;
  for (size_t i = 0; (line = strsep(&text_dup, "\n")); i++) {
    if (i > 0) {
      new_node = malloc(sizeof(struct textbuffer));
      prev->next = new_node;
    }
    new_node->line = (char *)malloc(strlen(line) + 1);
    strcpy(new_node->line , line);
    new_node->next = NULL;
    new_node->prev = prev;
    prev = new_node;
	}
  free(to_free);
  return head;
}

void textbuffer_drop (Textbuffer tb)
{
  Textbuffer node = NULL;
  while (tb) {
    node = tb->next;
    tb = tb->next;
    free(node);
  }
}

size_t textbuffer_lines (const Textbuffer tb)
{
  size_t i = 0;
  for (Textbuffer curr = tb; curr; curr = curr->next)
    i++;
  return i;
}
#endif
