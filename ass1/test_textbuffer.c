//////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-14 Chris Joy <z5113243@unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "textbuffer.h"

// void parse (const char *text);
// void parse (const char *text)
// {
// 	char *mutable_text, *line;
// 	mutable_text = strdup (text);
// 	while ((line = strsep (&mutable_text, "\n"))) {
// 		printf("line: %s\n", line);
// 	}
// }

int main (void)
{
	const char *text = "hello world \n this was a \n\n triumph \n ending the textfile now \0 sneaky";
	Textbuffer tb = textbuffer_new(text);
	// printf("last line: %s", tb->line);
	return EXIT_SUCCESS;
}
