#ifndef EVEN_ODD
#define EVEN_ODD

#include <string.h> //strcmp()
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h> // strtol()
#include "node.h"

#define INVALID_ARGS "Error: invalid arguments\n"
#define WRONG_EXTENSION "Error: wrong file extension\n"
#define PARAM_ERR "Error: both parameters have to be in the range [1-200] with numeric characters\n"
#define KEY_FORMAT "Error: Use \"numbers_per_thread = \" and \"thread_num = \" as key names for each value\n"

#define HELP_GUIDE "[\"-h\" || \"--help\"] for help, [\"-f\" || \"--file\"] && pathname for program exec\n"

struct s_config {
	long	numbers_per_thread;
	long	thread_num;
};

void even_odd(struct s_config *config);
void parse_file(struct s_config *config, FILE *fp);

#endif
