#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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

int checkNullFlags(struct activeFlags *pCurrentFlags);

void flagHandling(int argc, char *argv[], struct activeFlags *pCurrentFlags);

void withoutFlags(int argc, char *argv[]);

void flagN_Activate(int argc, char *argv[]);

void output(char *temp_filename, FILE* temp);
