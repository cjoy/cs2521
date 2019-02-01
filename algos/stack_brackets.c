#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXITEMS 100

char* readline();

typedef struct StackRep *Stack;

Stack newStack(int);         // set up empty stack
void dropStack(Stack);       // remove unwanted stack
void StackPush(Stack, char); // insert an Item on top of stack
char StackPop(Stack);        // remove Item from top of stack
bool StackIsEmpty(Stack);    // check whether stack is empty

typedef struct StackRep {
  char *item;
  int top;
} StackRep;


// Complete the isBalanced function below.

// Please either make the string static or allocate on the heap. For example,
// static char str[] = "hello world";
// return str;
//
// OR
//
// char* str = "hello world";
// return str;
//
char* isBalanced(char* s) {
  int size = strlen(s);
  // if (size % 2 != 0) return "NO";

  char *res = "YES";

  Stack stack = newStack((size/2) + 1);

  for (size_t i = 0; i < size; i++) {
    switch (s[i]) {
      case '{':
      case '[':
      case '(':
          StackPush(stack, s[i]);
          break;
      case ')': {
          if (StackIsEmpty(stack) || (stack->item[stack->top] != '(')) 
              return "NO";    
          StackPop(stack);
          break;
      }
      case ']': {
          if (StackIsEmpty(stack) || (stack->item[stack->top] != '['))
              return "NO";
          StackPop(stack);
          break;
      }
      case '}': {
        if (StackIsEmpty(stack) || (stack->item[stack->top] != '{'))
          return "NO";
        StackPop(stack);
        break;
      }
    }
  }

  return StackIsEmpty(stack) ? "YES" : "NO";
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* t_endptr;
    char* t_str = readline();
    int t = strtol(t_str, &t_endptr, 10);

    if (t_endptr == t_str || *t_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int t_itr = 0; t_itr < t; t_itr++) {
      char* s = readline();

      char* result = isBalanced(s);

      fprintf(fptr, "%s\n", result);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
  size_t alloc_length = 1024;
  size_t data_length = 0;
  char* data = malloc(alloc_length);

  while (true) {
    char* cursor = data + data_length;
    char* line = fgets(cursor, alloc_length - data_length, stdin);

    if (!line) { break; }

    data_length += strlen(cursor);

    if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

    size_t new_length = alloc_length << 1;
    data = realloc(data, new_length);

    if (!data) { break; }

    alloc_length = new_length;
}

  if (data[data_length - 1] == '\n') {
    data[data_length - 1] = '\0';
  }

  data = realloc(data, data_length);

  return data;
}



// set up empty stack
Stack newStack(int n) {
  Stack s;
  s = malloc(sizeof(StackRep));
  assert(s != NULL);
  s->item = malloc(n * sizeof(char));
  assert(s->item != NULL);
  s->top = -1;
  return s;
}

// remove unwanted stack
void dropStack(Stack s) {
  assert(s != NULL);
  free(s->item);
  free(s);
}

// insert Item on top of stack
void StackPush(Stack s, char it) {
  assert(s->top < MAXITEMS - 1);
  s->top++;
  int i = s->top;
  s->item[i] = it;
}

// remove Item from top of stack
char StackPop(Stack s) {
  assert(s->top > -1);
  int i = s->top;
  char it = s->item[i];
  s->top--;
  return it;
}

// check whether stack is empty
bool StackIsEmpty(Stack s) { return (s->top < 0); }

