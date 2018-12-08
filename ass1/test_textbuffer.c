//////////////////////////////////////////////////////////////////////
// COMP2521 19T0 ... assignment 1: Textbuffer ADT
//
// 2018-12-14 Chris Joy <z5113243@unsw.edu.au>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "textbuffer.h"

#define TEST_STR_1 "0\n1\n2\n3\n4\n"
#define TEST_STR_2 "this was a triumph.\ni am making a note here...\nHUGE SUCCESS!\n"
void test_tb_new (void);
void test_tb_bytes (void);
void test_tb_to_str (void);
void test_tb_swap (void);
void test_tb_insert (void);
void test_tb_paste (void);
void test_tb_cut (void);
void test_tb_copy (void);
void test_tb_delete (void);
void test_tb_search (void);
void test_tb_replace (void);

int main (void)
{
	test_tb_new ();
	// test_tb_bytes ();
	test_tb_to_str ();
	test_tb_swap ();
	test_tb_insert ();
	test_tb_paste ();
	// test_tb_cut ();
	// test_tb_copy ();
	// test_tb_delete ();
	// test_tb_search ();
	// test_tb_replace ();

	puts("All tests passed. You are awesome!");
	return EXIT_SUCCESS;
}

void test_tb_new (void)
{
	puts("textbuffer_new():");
	{
		puts("- testing empty string");
		Textbuffer tb = textbuffer_new("");
		assert(textbuffer_lines(tb) == 1);
		textbuffer_drop(tb);
	}
	{
		puts("- testing consecutive new lines");
		Textbuffer tb = textbuffer_new("\n\n\n");
		assert(textbuffer_lines(tb) == 3);
		textbuffer_drop(tb);
	}
	{
		puts("- testing string with consecutive new lines");
		Textbuffer tb = textbuffer_new("hello world\nanother one\n\nblah\n");
		assert(textbuffer_lines(tb) == 4);
		textbuffer_drop(tb);
	}
	{
		puts("- testing string that terminates early");
		Textbuffer tb = textbuffer_new("this is cool\nblah blah\n\0\nblah\n");
		assert(textbuffer_lines(tb) == 2);
		textbuffer_drop(tb);
	}
	puts("");
}

void test_tb_bytes (void)
{
	puts("textbuffer_bytes():");
	{
		puts("- testing ");
	}
	puts("");
}

void test_tb_to_str (void)
{
	puts("textbuffer_to_str():");
	{
		puts("- testing an empty textbuffer");
		Textbuffer tb = textbuffer_new("");
		assert(strcmp(textbuffer_to_str(tb), "\n") == 0);
		textbuffer_drop(tb);
	}
	{
		puts("- testing one line textbuffer");
		const char* str = "this is a one line textbuffer\n";
		Textbuffer tb = textbuffer_new(str);
		assert(strcmp(textbuffer_to_str(tb), str) == 0);
		textbuffer_drop(tb);
	}
	{
		puts("- testing a textbuffer with consecutive new lines");
		const char* str = "\n\n\n435\n3234\n";
		Textbuffer tb = textbuffer_new(str);
		assert(strcmp(textbuffer_to_str(tb), str) == 0);
		textbuffer_drop(tb);
	}
	puts("");
}

void test_tb_swap (void)
{
	puts("textbuffer_swap():");
	{
		puts("- testing case: H <-[]-> <-[pos1]-> <-[]-> <-[pos3]-> <-[]-> T");
		Textbuffer tb = textbuffer_new(TEST_STR_1);
		textbuffer_swap(tb, 1, 3);
		assert(strcmp(textbuffer_to_str(tb), "0\n3\n2\n1\n4\n") == 0);
		textbuffer_drop(tb);
	}
	{
		puts("- testing case: H <-[pos0]-> <-[]-> <-[]-> <-[]-> <-[pos4]-> T");
		Textbuffer tb = textbuffer_new(TEST_STR_1);
		textbuffer_swap(tb, 0, 4);
		assert(strcmp(textbuffer_to_str(tb), "4\n1\n2\n3\n0\n") == 0);
		textbuffer_drop(tb);
	}
	{
		puts("- testing case: H <-[pos0]-> <-[]-> <-[]-> <-[pos3]-> <-[]-> T");
		Textbuffer tb = textbuffer_new(TEST_STR_1);
		textbuffer_swap(tb, 0, 3);
		assert(strcmp(textbuffer_to_str(tb), "3\n1\n2\n0\n4\n") == 0);
		textbuffer_drop(tb);
	}
	{
		puts("- testing case: H <-[]-> <-[pos1]-> <-[]-> <-[]-> <-[pos4]-> T");
		Textbuffer tb = textbuffer_new(TEST_STR_1);
		textbuffer_swap(tb, 1, 4);
		assert(strcmp(textbuffer_to_str(tb), "0\n4\n2\n3\n1\n") == 0);
		textbuffer_drop(tb);
	}
	{
		puts("- testing case: H <-[]-> <-[pos1]-> <-[pos2]-> <-[]-> <-[]-> T");
		Textbuffer tb = textbuffer_new(TEST_STR_1);
		textbuffer_swap(tb, 1, 2);
		assert(strcmp(textbuffer_to_str(tb), "0\n2\n1\n3\n4\n") == 0);
		textbuffer_drop(tb);
	}
	{
		puts("- testing case: H <-[pos0]-> <-[pos1]-> <-[]-> <-[]-> <-[]-> T");
		Textbuffer tb = textbuffer_new(TEST_STR_1);
		textbuffer_swap(tb, 0, 1);
		assert(strcmp(textbuffer_to_str(tb), "1\n0\n2\n3\n4\n") == 0);
		textbuffer_drop(tb);
	}
	{
		puts("- testing case: H <-[]-> <-[]-> <-[]-> <-[pos3]-> <-[pos4]-> T");
		Textbuffer tb = textbuffer_new(TEST_STR_1);
		textbuffer_swap(tb, 3, 4);
		assert(strcmp(textbuffer_to_str(tb), "0\n1\n2\n4\n3\n") == 0);
		textbuffer_drop(tb);
	}
	{
		puts("- testing case: H <-[]-> <-[]-> <-[]-> <-[pos3|pos3]-> <-[]-> T");
		Textbuffer tb = textbuffer_new(TEST_STR_1);
		textbuffer_swap(tb, 3, 3);
		assert(strcmp(textbuffer_to_str(tb), "0\n1\n2\n3\n4\n") == 0);
		textbuffer_drop(tb);
	}
	puts("");
}

void test_tb_insert (void)
{
	puts("textbuffer_insert():");
	{
		puts("- testing front insertion");
		Textbuffer tb1 = textbuffer_new("a+\nb+\nc+\n");
		Textbuffer tb2 = textbuffer_new("a-\nb-\nc-\n");
		textbuffer_insert (tb1, 0, tb2);
		assert(textbuffer_lines(tb1) == 6);
		assert(strcmp(textbuffer_to_str(tb1), "a-\nb-\nc-\na+\nb+\nc+\n") == 0);
		textbuffer_drop(tb1);
	}
	{
		puts("- testing back insertion");
		Textbuffer tb1 = textbuffer_new("a+\nb+\nc+\n");
		Textbuffer tb2 = textbuffer_new("a-\nb-\nc-\n");
		textbuffer_insert (tb1, 3, tb2);
		assert(textbuffer_lines(tb1) == 6);
		assert(strcmp(textbuffer_to_str(tb1), "a+\nb+\nc+\na-\nb-\nc-\n") == 0);
		textbuffer_drop(tb1);
	}
	{
		puts("- testing somewhere in the middle");
		Textbuffer tb1 = textbuffer_new("a+\nb+\nc+\n");
		Textbuffer tb2 = textbuffer_new("a-\nb-\nc-\n");
		textbuffer_insert (tb1, 2, tb2);
		assert(textbuffer_lines(tb1) == 6);
		assert(strcmp(textbuffer_to_str(tb1), "a+\nb+\na-\nb-\nc-\nc+\n") == 0);
		textbuffer_drop(tb1);
	}
	{
		puts("- testing somewhere in the middle");
		Textbuffer tb1 = textbuffer_new("a+\nb+\nc+\n");
		Textbuffer tb2 = textbuffer_new("a-\nb-\nc-\n");
		textbuffer_insert (tb1, 1, tb2);
		assert(textbuffer_lines(tb1) == 6);
		assert(strcmp(textbuffer_to_str(tb1), "a+\na-\nb-\nc-\nb+\nc+\n") == 0);
		textbuffer_drop(tb1);
	}
	{
		puts("- testing insert single line tb2 into multiline tb1 middle");
		Textbuffer tb1 = textbuffer_new("a\nb\nc\n");
		Textbuffer tb2 = textbuffer_new("yep\n");
		textbuffer_insert (tb1, 2, tb2);
		assert(textbuffer_lines(tb1) == 4);
		assert(strcmp(textbuffer_to_str(tb1), "a\nb\nyep\nc\n") == 0);
		textbuffer_drop(tb1);
	}	
	{
		puts("- testing insert single line tb2 into multiline tb1 start");
		Textbuffer tb1 = textbuffer_new("a\nb\nc\n");
		Textbuffer tb2 = textbuffer_new("yep\n");
		textbuffer_insert (tb1, 0, tb2);
		assert(textbuffer_lines(tb1) == 4);
		assert(strcmp(textbuffer_to_str(tb1), "yep\na\nb\nc\n") == 0);
		textbuffer_drop(tb1);
	}	
	{
		puts("- testing insert single line tb2 into multiline tb1 end");
		Textbuffer tb1 = textbuffer_new("a\nb\nc\n");
		Textbuffer tb2 = textbuffer_new("yep\n");
		textbuffer_insert (tb1, 3, tb2);
		assert(textbuffer_lines(tb1) == 4);
		assert(strcmp(textbuffer_to_str(tb1), "a\nb\nc\nyep\n") == 0);
		textbuffer_drop(tb1);
	}	
	{
		puts("- testing insert mutliline line tb2 into single tb1 start");
		Textbuffer tb1 = textbuffer_new("yep\n");
		Textbuffer tb2 = textbuffer_new("a\nb\nc\n");
		textbuffer_insert (tb1, 0, tb2);
		assert(textbuffer_lines(tb1) == 4);
		assert(strcmp(textbuffer_to_str(tb1), "a\nb\nc\nyep\n") == 0);
		textbuffer_drop(tb1);
	}
	{
		puts("- testing insert mutliline line tb2 into single tb1 end");
		Textbuffer tb1 = textbuffer_new("yep\n");
		Textbuffer tb2 = textbuffer_new("a\nb\nc\n");
		textbuffer_insert (tb1, 1, tb2);
		assert(textbuffer_lines(tb1) == 4);
		assert(strcmp(textbuffer_to_str(tb1), "yep\na\nb\nc\n") == 0);
		textbuffer_drop(tb1);
	}
	puts("");
}

void test_tb_paste (void)
{
	puts("textbuffer_paste():");
	{
		puts("- testing duplicates tb2 and inserts somewhere in the middle");
		Textbuffer tb1 = textbuffer_new("a+\nb+\nc+\n");
		Textbuffer tb2 = textbuffer_new("a-\nb-\nc-\n");
		textbuffer_paste (tb1, 2, tb2);
		assert(textbuffer_lines(tb1) == 6);
		assert(strcmp(textbuffer_to_str(tb1), "a+\nb+\na-\nb-\nc-\nc+\n") == 0);
		assert(textbuffer_lines(tb2) == 3);
		assert(strcmp(textbuffer_to_str(tb2), "a-\nb-\nc-\n") == 0);
		textbuffer_drop(tb1);
	}
	puts("");
}

void test_tb_cut (void)
{
	puts("textbuffer_cut():");
	{
		puts("- testing ");
	}
	puts("");
}

void test_tb_copy (void)
{
	puts("textbuffer_copy():");
	{
		puts("- testing ");
	}
}

void test_tb_delete (void)
{
	puts("textbuffer_delete():");
	{
		puts("- testing ");
	}
}

void test_tb_search (void)
{
	puts("textbuffer_search():");
	{
		puts("- testing ");
	}
}

void test_tb_replace (void)
{
	puts("textbuffer_replace():");
	{
		puts("- testing ");
	}
	puts("");
}

