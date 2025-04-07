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
			pthread_mutex_lock(&t->data->even_mutex);
			aux = new_node(list->num);
			if (!aux)
				return (NULL);
			add_node(&t->data->even_list, aux);
			pthread_mutex_unlock(&t->data->even_mutex);
		}
		else
		{
			pthread_mutex_lock(&t->data->odd_mutex);
			aux = new_node(list->num);
			if (!aux)
				return (NULL);
			add_node(&t->data->odd_list, aux);
			pthread_mutex_unlock(&t->data->odd_mutex);
		}
		list = list->next;
	}
	return (NULL);
}

static void generate_initial_list(t_node **initial_list, struct s_config *config)
{
	int *pool = generate_numbers_pool(POOL_SIZE);
	t_node *aux;
	int initial_list_size = config->numbers_per_thread * config->thread_num;
	for (int i = 0; i < initial_list_size; i++) {
		aux = new_node(pool[i]);
		if (aux)
		{
			add_node(initial_list, aux);
		}
		else
		{
			clear_list(initial_list);
			free(pool);
			exit(1);
		}
	}
	free(pool);
}

void even_odd(struct s_config *config)
{
	// initialization
	struct s_data data;
	data.odd_list = NULL;
	data.even_list = NULL;
	data.initial_list = NULL;
	srand(time(NULL));
	generate_initial_list(&data.initial_list, config);

	if (pthread_mutex_init(&data.odd_mutex, NULL))
	{
		perror("pthread_mutex_init: ");
		exit(1);
	};
	if (pthread_mutex_init(&data.even_mutex, NULL))
	{
		perror("pthread_mutex_init: ");
		exit(1);
	};

	printf("numbers_per_thread = %li\n", config->numbers_per_thread);
	printf("thread_num = %li\n", config->thread_num);

	//thread creation
	struct s_thread_struct threads[config->thread_num];
	t_node *loop = data.initial_list;
	for (int i = 0; i < config->thread_num; i++)
	{
		threads[i].list = NULL;
		threads[i].data = &data;
		for (int j = config->numbers_per_thread; j; --j)
		{
			t_node *aux = new_node(loop->num);
			if (!aux)
			{
				clear_all(&data);
				exit(1);
			}
			add_node(&threads[i].list, aux);
			loop = loop->next;
		}
		if (pthread_create(&threads[i].thread, NULL, routine, &threads[i]))
		{
			perror("pthread_create: ");
			clear_all(&data);
			exit(1);
		};
	}

	for (int i = 0; i < config->thread_num; i++)
	{
		if (pthread_join(threads[i].thread, NULL))
		{
			perror("pthread_join: ");
			clear_all(&data);
			exit(1);
		}
		clear_list(&threads[i].list);
	}

	printf("Initial list:\n");
	print_list(data.initial_list);
	printf("Odd list:\n");
	print_list(data.odd_list);
	printf("Even list:\n");
	print_list(data.even_list);
	clear_all(&data);
}
