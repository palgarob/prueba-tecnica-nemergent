#include "even_odd.h"
#include "node.h"

void even_odd(struct s_config *config)
{
	t_node *initial_list = NULL;
	/* t_node *even_list = NULL;
	t_node *odd_list = NULL; */

	printf("numbers_per_thread = %li\n", config->numbers_per_thread);
	srand(time(NULL));
	printf("thread_num = %li\n", config->thread_num);
	int initial_list_size = config->numbers_per_thread * config->thread_num;
	int *pool = generate_numbers_pool(POOL_SIZE);
	for (int i = 0; i < initial_list_size; i++) {
		add_node(&initial_list, new_node(pool[i]));
	}
	/* pthread_t t[initial_list_size];
	for (int i = 0; i < initial_list_size; i++)
	{
		pthread_create(&t[i], NULL, routine, NULL);
	} */
	print_list(initial_list);
//	clear(&list);
}
