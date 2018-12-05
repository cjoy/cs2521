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
// #define TEST_STR		"hello\n2"

	Textbuffer tb = textbuffer_new (TEST_STR);
	
	printf("Number of valid lines: %zu\n", textbuffer_lines(tb));
	printf("Total number of bytes in textbuffer: %zu\n", textbuffer_bytes(tb));
	printf("Original String: %s\n", textbuffer_to_str(tb));


	textbuffer_drop (tb);

	printf("All tests passed. You are awesome!");
	return EXIT_SUCCESS;
}
