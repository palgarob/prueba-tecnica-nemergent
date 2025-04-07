#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h> // perror()
#include <stdbool.h> // has_duplicates()

typedef struct s_node t_node;
struct s_node
{
	int		num;
	t_node	*next;
};

t_node *new_node(int num);
void add_node(t_node **first_node, t_node *node_new);
void clear(t_node **first_node);
void print_list(t_node *node);

#endif
