#include "even_odd.h"

int *generate_numbers_pool(int n)
{
	int *pool = malloc(sizeof(int) * n);
	if (!pool) return (perror("malloc: "), NULL);
	
	for (int i = 0; i < n; i++) {
		pool[i] = i;
	}

	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = pool[i];
		pool[i] = pool[j];
		pool[j] = temp;
	}
	return pool;
}
