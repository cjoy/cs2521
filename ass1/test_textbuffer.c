//////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-14 Chris Joy <z5113243@unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "textbuffer.h"

int main (void)
{
	const char *text = "hello world \n this was a \n\n triumph \n ending the textfile now \0 sneaky";
	Textbuffer tb = textbuffer_new(text);
	
	// for (Textbuffer curr = tb; curr; curr = curr->next)
	// 	printf("[%s]->", curr->line);

	textbuffer_drop(tb);
	// puts("");
	// for (Textbuffer curr = tb; curr; curr = curr->next)
	// 	printf("[%s]->", curr->line);

	return EXIT_SUCCESS;
}
