#include "s21_cat.h"

int main(int argc, char *argv[]) {
	struct activeFlags CurrentFlags;
    struct activeFlags *pCurrentFlags = &CurrentFlags;
	// Ищем какие флаги есть
	searchArgs(argc, argv, pCurrentFlags);

	printf("\n");

	//Ищем отступ аргументов для файлов
	int offset = offsetOnRightSiteOfArguments(argc, argv);

	printf("\n");

	int isValid = 1;

	if (isValidFiles(offset, argc, argv) != 1) {
		printf("У вас файл хуйня! >:(\n");
		isValid = 0;
	}

	if (isValid) {
		flagHandling(argc, argv, pCurrentFlags);
	}
}
