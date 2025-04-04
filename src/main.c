#include "even_odd.h"

static void check_extension(char *file)
{
	char *dot = strrchr(file, '.');
	if (!dot || strcmp(dot, ".txt")) {
		fprintf(stderr, WRONG_EXTENSION);
		exit(1);
	}
}

int main(int argc, char **argv)
{
	FILE* fp;
	struct s_config config;
	if (argc == 2 && (!strcmp("-h", argv[1]) || !strcmp("--help", argv[1])))
		printf(HELP_GUIDE);
	else if (argc == 3 && (!strcmp("-f", argv[1]) || !strcmp("--file", argv[1])))
	{
		check_extension(argv[2]);
		fp = fopen(argv[2], "r");
		if (fp == NULL)
			return (perror("fopen: "), 1);
		parse_file(&config, fp);
		even_odd(&config); // execution starts here
	}
	else
		return (fprintf(stderr, INVALID_ARGS), 1);
	return (0);
}
