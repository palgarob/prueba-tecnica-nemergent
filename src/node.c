#include "node.h"

t_node *new_node(int num)
{
	t_node *node_new = (t_node *)malloc(sizeof(t_node));
	if (!node_new)
	{
		return (perror("malloc : "), NULL);
	}
		node_new->num = num;
	return node_new;
}

void add_node(t_node **list, t_node *node_new)
{
	node_new->next = *list;
	*list = node_new;
}

void clear(t_node **first_node)
{
	t_node	*aux;
	t_node	*prev;

	if (!*first_node) return ;
	aux = (*first_node)->next;
	free(*first_node);
	if (aux)
	{
		while (aux->next)
		{
			prev = aux->next;
			free(aux);
			aux = prev;
		}
		free(aux);
	}
}

void print_list(t_node *node)
{
	if (node == NULL) return ;
	while (node) {
		printf("%d ", node->num);
		node = node->next;
	}
	printf("\n");
}
