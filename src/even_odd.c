#include "even_odd.h"
#include "node.h"

void *routine(void * param)
{
	t_thread *t;
	t = (t_thread *)param;
	t_node *list = t->list;
	t_node *aux;

	while (list)
	{
		if (list->num % 2 == 0)
		{
			pthread_mutex_lock(&t->content->even_mutex);
			aux = new_node(list->num);
			if (!aux)
				return (NULL);
			add_node(&t->content->even_list, aux);
			pthread_mutex_unlock(&t->content->even_mutex);
		}
		else
		{
			pthread_mutex_lock(&t->content->odd_mutex);
			aux = new_node(list->num);
			if (!aux)
				return (NULL);
			add_node(&t->content->odd_list, aux);
			pthread_mutex_unlock(&t->content->odd_mutex);
		}
		list = list->next;
	}
	return (NULL);
}

void even_odd(struct s_config *config)
{
	int initial_list_size = config->numbers_per_thread * config->thread_num;

	struct s_data content;
	content.odd_list = NULL;
	content.even_list = NULL;
	content.initial_list = NULL;

	pthread_mutex_init(&content.odd_mutex, NULL);
	pthread_mutex_init(&content.even_mutex, NULL);

	t_node *aux;
	
	printf("numbers_per_thread = %li\n", config->numbers_per_thread);
	srand(time(NULL));
	printf("thread_num = %li\n", config->thread_num);

	int *pool = generate_numbers_pool(POOL_SIZE);
	for (int i = 0; i < initial_list_size; i++) {
		aux = new_node(pool[i]);
		if (aux)
		{
			add_node(&content.initial_list, aux);
		}
		else
		{
			clear(&content.initial_list);
			free(pool);
			exit(1);
		}
	}
	
	struct s_thread_struct threads[config->thread_num];
	t_node *loop = content.initial_list;
	for (int i = 0; i < config->thread_num; i++)
	{
		threads[i].id = i;
		threads[i].list = NULL;
		threads[i].content = &content;
		for (int j = config->numbers_per_thread; j; --j)
		{
			t_node *aux = new_node(loop->num);
			if (!aux)
				exit(1);
			add_node(&threads[i].list, aux);
			loop = loop->next;
		}
		pthread_create(&threads[i].thread, NULL, routine, &threads[i]);
	}

	for (int i = 0; i < config->thread_num; i++)
	{
		pthread_join(threads[i].thread, NULL);
	}

	printf("Initial list:\n");
	print_list(content.initial_list);
	printf("Odd list:\n");
	print_list(content.odd_list);
	printf("Even list:\n");
	print_list(content.even_list);
	clear(&content.initial_list);
	clear(&content.odd_list);
	clear(&content.even_list);
	pthread_mutex_destroy(&content.odd_mutex);
	pthread_mutex_destroy(&content.even_mutex);
}
