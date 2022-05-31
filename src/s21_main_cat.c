#include "s21_cat.h"

int main(int argc, char *argv[]) {
	struct activeFlags CurrentFlags;
    struct activeFlags *pCurrentFlags = &CurrentFlags;

	searchArgs(argc, argv, pCurrentFlags);

	printf("\n");

	int offset = offsetOnRightSiteOfArguments(argc, argv);

	printf("\n");

	if (isValidFiles(offset, argc, argv) == 1) {
		flagHandling(argc, argv, pCurrentFlags);
	}

	return 0;
}
