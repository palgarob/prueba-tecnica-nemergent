#include "even_odd.h"

static void extract_values(struct s_config *config, char *numbers_per_thread, char *thread_num)
{
	char *endptr;

	config->numbers_per_thread = strtol(numbers_per_thread + 21, &endptr, 10);
	if (endptr == numbers_per_thread + 21 || config->numbers_per_thread > 200 || config->numbers_per_thread < 1) {
		fprintf(stderr, PARAM_ERR);
		exit(1);
	}
	config->thread_num = strtol(thread_num + 13, &endptr, 10);
	if (endptr == thread_num + 13|| config->thread_num > 200 || config->thread_num < 1) {
		fprintf(stderr, PARAM_ERR);
		exit(1);
	}
}

void parse_file(struct s_config *config, FILE *fp)
{
	char *line1 = (char *)calloc(sizeof(char), 100);
	char *line2 = (char *)calloc(sizeof(char), 100);

	if (!fgets(line1, 100, fp)) {perror("fgets: "); exit(1);}
	if (!fgets(line2, 100, fp)) {perror("fgets: "); exit(1);}

	if (
		!strncmp(line1, "numbers_per_thread = ", 21)
		&& !strncmp(line2, "thread_num = ", 13)
	)
	{
		extract_values(config, line1, line2);
		free(line1); free(line2);
	}
	else if (
		!strncmp(line2, "numbers_per_thread = ", 21)
		&& !strncmp(line1, "thread_num = ", 13)
	)
	{
		extract_values(config, line2, line1);
		free(line1); free(line2);
	}
	else
	{
		fprintf(stderr, KEY_FORMAT);
		free(line1); free(line2);
		exit(1);
	}
}
