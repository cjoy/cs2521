////////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT submission tests

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "textbuffer.h"

int main (void)
{
#define DRY01_STR_A	"1.1 abc\n"
#define DRY01_STR_B	"1.2 def\n"
#define DRY01_STR	DRY01_STR_A DRY01_STR_B

	Textbuffer tb = textbuffer_new (DRY01_STR);
	assert (tb != NULL);

	assert (textbuffer_bytes (tb) == strlen (DRY01_STR));
	assert (textbuffer_lines (tb) == 2);

	char *str = textbuffer_to_str (tb);
	assert (strcmp (str, DRY01_STR) == 0);

	textbuffer_drop (tb);
	free (str);

	return EXIT_SUCCESS;
}
