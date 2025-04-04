#include "even_odd.h"
#include "node.h"

void even_odd(struct s_config *config)
{
	t_node *list = NULL;

	printf("numbers_per_thread = %li\n", config->numbers_per_thread);
	printf("thread_num = %li\n", config->thread_num);
	srand(time(NULL));
	for (int i = 0; i < config->numbers_per_thread * config->thread_num; i++) {
		add_node(&list, new_node(rand()));
	}
	print_list(list);
	clear(&list);
}
