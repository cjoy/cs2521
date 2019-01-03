# Edgy Matters
Implement a function

```C
bool graph_has_edge_p (Graph g, edge e);
```
that tests whether a given edge is present in the graph. The function should return true if the edge exists in the graph, and false otherwise.

Implement this function for both the adjacency-matrix and the adjacency-list representations.

## Sol
```C
// Adj Matrix
bool graph_has_edge_p (Graph g, edge e)
{
  return g->adj_matrix[e.v][e.w];
}

// Adj list
bool graph_has_edge_p (Graph g, edge e)
{
  adj_node *pivot = g->adj_list[e.v];
  for ( ; pivot; pivot = pivot->next)
    if (pivot->v == e->w) return true;
  return false;
}
```



# One edge, ah, ah, ah…
Consider a variation on the adjacency matrix above, where we don’t store the number of edges, n_edges –
```C
struct graph {
	size_t n_vertices;
	bool **adj_matrix;
};
```
Write a C function to count the number of distinct edges in the graph.
```C
size_t graph_num_edges (Graph g);
```
## Sol
```C
size_t graph_num_edges (Graph g)
{
  
}
```
