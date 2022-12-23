## Doubly Linked List the Glue way - glthreads
`typedef struct dll_node_ {
	void *data;
	struct dll_node_ *left;
	struct dll_node_ *right;
}dll_node_t;
//dll_node_ is in only in the defined structs namespace.
//dll_node_t is global`
