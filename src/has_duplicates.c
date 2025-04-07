#include "even_odd.h"

bool has_duplicates(int arr[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (arr[i] == arr[j]) {
				return true; // Duplicate found
			}
		}
	}
	return false; // No duplicates
}
