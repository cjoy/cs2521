////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-14 Chris Joy <z5113243@unsw.edu.au>

#include "textbuffer.h"

typedef struct textbuffer {
  char *line;
  Textbuffer prev;
  Textbuffer next;
} *Textbuffer;

Textbuffer textbuffer_new (const char *text)
{
	char *buffer, *line;
	buffer = strdup(text);
	Textbuffer head = NULL, prev = NULL;
  for (int i = 0; (line = strsep(&buffer, "\n")); i++) {
    Textbuffer node = malloc(sizeof *node);
    if (i > 0) prev->next = node;
    if (i == 0) {
      head = node;
      node->next = NULL;
    }
    node->line = line;
    node->prev = prev;
    prev = node;
	}
  return head;
}

void textbuffer_drop (Textbuffer tb)
{
  if (!tb) return;
  Textbuffer next = NULL;
  while (tb) {
    next = tb->next;
    free(tb);
    tb = next;
  }
}
