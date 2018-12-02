////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-14 Chris Joy <z5113243@unsw.edu.au>

#include "textbuffer.h"

typedef struct textbuffer *Textbuffer;
typedef struct textbuffer {
  char *line;
  Textbuffer prev;
  Textbuffer next;
} textbuffer;

// Example text:
// hello world \n this was a triumph \n ending the textfile now \0
Textbuffer textbuffer_new (const char *text)
{
	// char *mutable_text, *line;
	// mutable_text = strdup(text);
	// Textbuffer head = NULL;
  // while ((line = strsep(&mutable_text, "\n"))) {
  //   Textbuffer node = malloc(sizeof *node);
  //   node->line = "Test";
  //   node->next = NULL;
  //   node->prev = NULL;
  //   head = node;
	// }
  // return head;
  Textbuffer node = malloc(sizeof (*node));
  node->line = "Test";
  node->next = NULL;
  node->prev = NULL;
  return node;
}
