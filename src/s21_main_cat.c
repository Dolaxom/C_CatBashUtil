#include "s21_cat.h"

int main(int argc, char *argv[]) {
	struct activeFlags CurrentFlags;
	struct activeFlags *pCurrentFlags = &CurrentFlags;

	searchArgs(argc, argv, pCurrentFlags);

	flagHandling(argc, argv, pCurrentFlags);

	return 0;
}
