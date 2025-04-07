#ifndef EVEN_ODD_H
#define EVEN_ODD_H

#include <string.h> //strcmp()
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h> // strtol()
#include <time.h> // time()
#include <pthread.h>
#include "node.h"

#define INVALID_ARGS "Error: invalid arguments, run ./even_odd -h\n"
#define WRONG_EXTENSION "Error: wrong file extension, only .txt valid\n"
#define PARAM_ERR "Error: both parameters have to be in the range [1-200] with numeric characters\n"
#define KEY_FORMAT "Error: Use \"numbers_per_thread =\" and \"thread_num =\" as key names for each value in the config file\n"

#define HELP_GUIDE "\
./even_odd [-h || --help]		help\n\
./even_odd [-f || --file] <pathname>	for program exec\n"
#define POOL_SIZE 50000

struct s_config {
	long	numbers_per_thread;
	long	thread_num;
};

struct s_data;
typedef struct s_thread_struct
{
	int id;
	t_node *list;
	pthread_t thread;
	struct s_data *content;
}t_thread;

struct s_data 
{
	pthread_mutex_t odd_mutex;
	pthread_mutex_t even_mutex;
	t_node *even_list;
	t_node *odd_list;
};

void even_odd(struct s_config *config);
void parse_file(struct s_config *config, FILE *fp);
int *generate_numbers_pool(int size);
bool has_duplicates(int arr[], int size);

#endif
