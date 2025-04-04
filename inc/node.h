#ifndef NODE_H
#define NODE_H

typedef struct s_node node;
struct s_node
{
	int		num;
	node	*next;
};

node *new_list(int num);
node *add(node **first_node, int num);
void clear(node *first_node);

#endif
