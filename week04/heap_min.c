#include <stdbool.h>
#include <stdlib.h>

#include "heap_min.h"

/**
 * Return `true` if the array heap with a sepcified number of items is
 * in heap order.  You must assume that the heap items are in indexes
 * 1..heap_size, and that index 0 is empty and not used to store items.
 */
bool heap_min_p (int heap[], size_t heap_size)
{
	for (size_t i = 1; i < heap_size; i++)
		if ((2*i <= heap_size && heap[2*i] < heap[i]) || 
			(2*i + 1 <= heap_size && heap[2*i + 1] < heap[i]))
			return false;
	return true;
}
