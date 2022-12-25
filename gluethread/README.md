## Doubly Linked List the Glue way - glthreads
<p>Traditional Linked List</p>
<pre><code>typedef struct dll_node_ {
	void *data;
	struct dll_node_ *left;
	struct dll_node_ *right;
}dll_node_t;
//dll_node_ is in only in the defined structs namespace.
//dll_node_t is global</code></pre>
<p>Glue based DLL</p>
<pre><code>typedef stuct glthread_node_ {
	struct glthread_node_ *left;
	struct glthread_node_ *right;
}glthread_node_t;
//no data member</code></pre>
<p>Representation of glue based doublt linked list</p>
<pre><code>typedef struct_gldll_ {
glthread_node_t *head;
int (*key_match)(void *, void *);//function pointers
unsigned int offset;//
}gldll_t;</code></pre>
<p>glnodes = data is glued to the node. The data struct has a glnode, and with that pointer, it sticks itself to the corresponding glnode.</p>
<p>Offset of a given field in a struct is the number of bytes the field is away from the start of the struct</p>
