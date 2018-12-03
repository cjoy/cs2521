//////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-14 Chris Joy <z5113243@unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "textbuffer.h"

int main (void)
{
#define TEST_STR_1	"hello world\n"
#define TEST_STR_2	"this was a triumph.\n"
#define TEST_STR_3	"this is the end of the line\0"
#define TEST_STR_4	"this is a sneaky line\n"
#define TEST_STR		TEST_STR_1 TEST_STR_2 TEST_STR_3 TEST_STR_4

	Textbuffer tb = textbuffer_new (TEST_STR);
	// textbuffer_drop (tb);

	return EXIT_SUCCESS;
}
