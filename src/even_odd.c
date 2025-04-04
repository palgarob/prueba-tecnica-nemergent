#include "even_odd.h"

void even_odd(struct s_config *config)
{
	(void)config;
	printf("numbers_per_thread = %li\n", config->numbers_per_thread);
	printf("thread_num = %li\n", config->thread_num);
}
