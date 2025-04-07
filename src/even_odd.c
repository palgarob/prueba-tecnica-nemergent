#include "even_odd.h"
#include "node.h"

void *routine(void * param)
{
	t_thread *t;
	t = (t_thread *)param;
	t_node *list = t->list;
	while (list)
	{
		if (list->num % 2 == 0)
		{
			pthread_mutex_lock(&t->content->even_mutex);
			add_node(&t->content->even_list, list->num);
			pthread_mutex_unlock(&t->content->even_mutex);
		}
		else
		{
			pthread_mutex_lock(&t->content->odd_mutex);
			add_node(&t->content->odd_list, list->num);
			pthread_mutex_unlock(&t->content->odd_mutex);
		}
		list = list->next;
	}
	return (NULL);
}

void even_odd(struct s_config *config)
{
	t_node *initial_list = NULL;
	struct s_data content;
	content.odd_list = NULL;
	content.even_list = NULL;
	pthread_mutex_init(&content.odd_mutex, NULL);
	pthread_mutex_init(&content.even_mutex, NULL);

	printf("numbers_per_thread = %li\n", config->numbers_per_thread);
	srand(time(NULL));
	printf("thread_num = %li\n", config->thread_num);
	int initial_list_size = config->numbers_per_thread * config->thread_num;
	int *pool = generate_numbers_pool(POOL_SIZE);
	for (int i = 0; i < initial_list_size; i++) {
		add_node(&initial_list, pool[i]);
	}


	struct s_thread_struct threads[config->thread_num];
	t_node *loop = initial_list;
	for (int i = 0; i < config->thread_num; i ++)
	{
		threads[i].id = i;
		for (int j = config->numbers_per_thread; j; j--)
		{
			threads->list = NULL;
			add_node(&threads[i].list, loop->num);
			loop = loop->next;
		}
		pthread_create(&threads[i].thread, NULL, routine, &threads[i]);
	}
	for (int i = 0; i < config->thread_num; i++)
	{
		pthread_join(threads[i].thread, NULL);
	}
	print_list(initial_list);
	print_list(content.odd_list);
	printf("\n");
	print_list(content.even_list);
	clear(&initial_list);
	clear(&content.odd_list);
	clear(&content.even_list);
	pthread_mutex_destroy(&content.odd_mutex);
	pthread_mutex_destroy(&content.even_mutex);
}
