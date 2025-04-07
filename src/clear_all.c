#include "even_odd.h"

void clear_all(struct s_data *data)
{
	clear_list(&data->even_list);
	clear_list(&data->initial_list);
	clear_list(&data->odd_list);
	if (pthread_mutex_destroy(&data->odd_mutex) || pthread_mutex_destroy(&data->even_mutex))
	{
		perror("pthread_mutex_destroy: ");
		exit(1);
	}
}
