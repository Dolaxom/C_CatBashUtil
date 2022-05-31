#include "s21_cat.h"

int main(int argc, char *argv[]) {
	struct activeFlags CurrentFlags;
	struct activeFlags *pCurrentFlags = &CurrentFlags;

	// Поиск аргументов и запись найденный в структуру
	searchArgs(argc, argv, pCurrentFlags);

	// Отступ раздедения аргументов файлов от флагов
	int offset = offsetOnRightSiteOfArguments(argc, argv);

	// Проверка файлов на валидность
	if (isValidFiles(offset, argc, argv) == 1) {
	// Запуск функций в зависимости от активированных флагов
		flagHandling(argc, argv, pCurrentFlags);
	}

	return 0;
}
