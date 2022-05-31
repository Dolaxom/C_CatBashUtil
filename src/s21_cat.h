#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

struct activeFlags {
	int b;
	int e;
	int n;
	int s;
	int t;
};
// Зануляет структуру
void init(struct activeFlags *pCurrentFlags);
// Ищет аргументы
void searchArgs(int argc, char *argv[], struct activeFlags *pCurrentFlags);
// Ищет отступ для понимания, откуда начинаются идти аргументы файлов
int offsetOnRightSiteOfArguments(int argc, char *argv[]);
// Если файлы в аргументах есть, проверяет их
int isValidFiles(int offset, int argc, char *argv[]);
// Проверка на случай, если передано 0 флагов
int checkNullFlags(struct activeFlags *pCurrentFlags);
// Функция запускающая другие функции, зависимо от флагов
void flagHandling(int argc, char *argv[], struct activeFlags *pCurrentFlags);
// Создание и удаление копий файлов из аргументов
void createCopyFiles(int argc, char *argv[]);
void deleteCopyFiles();
// Обработка случая без флагов
void withoutFlags(int argc, char *argv[]);
// Обработка -n
void flagN_Activate(int argc, char *argv[]);
// Вывод файлов
void output(char *temp_filename, FILE* temp);
