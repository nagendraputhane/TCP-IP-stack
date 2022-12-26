#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void
insert_link_between_two_nodes(node_t *node1, node_t *node2, char *from_if_name, char *to_if_name, unsigned int cost) {
	link_t *link = calloc(1, sizeof(link_t));

	//set interface name
	strncpy(link->intf1.if_name, from_if_name, IF_NAME_SIZE);
	link->intf1.if_name[IF_NAME_SIZE] = '\0';
	strncpy(link->intf2.if_name, to_if_name, IF_NAME_SIZE);
	link->intf2.if_name[IF_NAME_SIZE] = '\0';

	link->intf1.link = link;//associate the NIC with the link
	link->intf2.link = link;

	link->intf1.att_node = node1;//NIC for interface 1 of the link
	link->intf2.att_node = node2;
	link->cost = cost;
	
	int empty_intf_slot;
	//insert the link to the empty slots of the node
	empty_intf_slot = get_node_intf_available_slot(node1);
    	node1->intf[empty_intf_slot] = &link->intf1;

    	empty_intf_slot = get_node_intf_available_slot(node2);
    	node2->intf[empty_intf_slot] = &link->intf2;
}

graph_t *
create_new_graph(char *topology_name) {
	graph_t *graph = calloc(1, sizeof(graph_t));//calloc a graph data structure
	strncpy(graph->topology_name, topology_name, 32);//copy the name of the graph, as you can't assign strings
	graph->topology_name[31] = '\0';

	init_glthread(&graph->node_list);//initialize the linked list
	return graph;
}

//create a new node in the graph
node_t *
create_graph_node(graph_t *graph, char *node_name) {
	node_t *node = calloc(1, sizeof(node_t));
	strncpy(node->node_name, node_name, NODE_NAME_SIZE);
	node->node_name[NODE_NAME_SIZE] = '\0';

	init_glthread(&node->graph_glue);
	glthread_add_next(&graph->node_list, &node->graph_glue);
	return node;
}
