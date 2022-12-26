/*
Files to be created:
	graph.h, graph.c

A graph is a collections of nodes

An interface has a:
	Name
	Owning node
	A wire/link

A link is defined as a pair of interfaces

A node has a:
	name
	set of empty interface slots
*/

#ifndef __GRAPH__
#define __GRAPH__

#include <stddef.h>
#include <assert.h>
#include "gluethread/glthread.h"

#define NODE_NAME_SIZE   16
#define IF_NAME_SIZE     16
#define MAX_INTF_PER_NODE   10

/*Forward Declarations*/
typedef struct node_ node_t;
typedef struct link_ link_t;

typedef struct interface_ { //NIC
	char if_name[IF_NAME_SIZE];
	struct node_ *att_node;//pointer to the node to which the interface is a part of
	struct link_ *link;//pointer to the link to which the interface is part of
	//intf_nw_props_t intf_nw_props;
} interface_t;

struct link_ {
	interface_t intf1;
	interface_t intf2;
	unsigned int cost;
};

struct node_ {
	char node_name[NODE_NAME_SIZE];
	//every node need to have empty slots where interfaces can be plugged in
	//Arrays which holds the pointers to type interfcaes_
	interface_t *intf[MAX_INTF_PER_NODE];//empty slots present in the devices
	glthread_t graph_glue;//add this node to the graph
	unsigned int udp_port_number;
    	int udp_sock_fd;
    //node_nw_prop_t node_nw_prop;
};	

typedef struct graph_ {
	char topology_name[32];//name of the graph
	glthread_t node_list;//graph = collection of nodes; LL of nodes
} graph_t ;

node_t *
create_graph_node(graph_t *graph, char *node_name);

graph_t *
create_new_graph(char *topology_name);

void
insert_link_between_two_nodes(node_t *node1,
                             node_t *node2,
                             char *from_if_name,
                             char *to_if_name,
                             unsigned int cost);

/*Helper functions*/
static inline node_t *
get_nbr_node(interface_t *interface){

    assert(interface->att_node);
    assert(interface->link);

    link_t *link = interface->link;
    if(&link->intf1 == interface)
        return link->intf2.att_node;
    else
        return link->intf1.att_node;
}

static inline int
get_node_intf_available_slot(node_t *node){

    int i ;
    for( i = 0 ; i < MAX_INTF_PER_NODE; i++){
        if(node->intf[i])
            continue;
        return i;
    }
    return -1;
}

static inline interface_t *
get_node_if_by_name(node_t *node, char *if_name){

    int i ;
    interface_t *intf;

    for( i = 0 ; i < MAX_INTF_PER_NODE; i++){
        intf = node->intf[i];
        if(!intf) return NULL;
        if(strncmp(intf->if_name, if_name, IF_NAME_SIZE) == 0){
            return intf;
        }
    }
    return NULL;
}

static inline node_t *
get_node_by_node_name(graph_t *topo, char *node_name){

    node_t *node;
    glthread_t *curr;

    ITERATE_GLTHREAD_BEGIN(&topo->node_list, curr){

        node = graph_glue_to_node(curr);
        if(strncmp(node->node_name, node_name, strlen(node_name)) == 0)
            return node;
    } ITERATE_GLTHREAD_END(&topo->node_list, curr);
    return NULL;
}
#endif
