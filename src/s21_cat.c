#include "s21_cat.h"

void init(struct activeFlags *pCurrentFlags) {
    pCurrentFlags->b = 0;
    pCurrentFlags->e = 0;
    pCurrentFlags->n = 0;
    pCurrentFlags->s = 0;
    pCurrentFlags->t = 0;
}

void searchArgs(int argc, char *argv[], struct activeFlags *pCurrentFlags) {
    init(pCurrentFlags);
    int res = 0;

    while ((res = getopt(argc, argv, "benst")) != -1) {
        switch (res) {
            case 'b': 
                printf("Найден аргумент b\n");
                pCurrentFlags->b = 1;
                break;

            case 'e':
                printf("Найден аргумент e\n");
                pCurrentFlags->e = 1;
                break;

            case 'n':
                printf("Найден аргумент n\n");
                pCurrentFlags->n = 1;
                break;

            case 's':
                printf("Найден аргумент s\n");
                pCurrentFlags->s = 1;
                break;

            case 't':
                printf("Найден аргумент t\n");
                pCurrentFlags->t = 1;
                break;

            default:
                printf("Найден хуй знает кто\n");
                break;
        }
    }
}

int offsetOnRightSiteOfArguments(int argc, char *argv[]) {
    int tmp = 0;
    for (int i = argc - 1; i > 0; i--) {
        char *name = argv[i];
        if (name[0] == '-') {
            break;
        }

        tmp = i;
    }

    return tmp;
}

int isValidFiles(int offset, int argc, char *argv[]) {
    int tmp = 1;
    for (int i = offset; i < argc; i++) {
        FILE* file;
        char *name = argv[i];
        if ((file = fopen(name, "r")) == NULL) {
            tmp = 0;
            printf("Файл %s не был найден\n", name);
            break;
        } else {
            printf("Файл %s успешно нашёлся\n", name);
        }

        fclose(file);
    }

    return tmp;
}

int checkNullFlags(struct activeFlags *pCurrentFlags) {
    int tmp = 0;
    if (pCurrentFlags->b == 0 && pCurrentFlags->e == 0
    && pCurrentFlags->n == 0 && pCurrentFlags->s == 0
    && pCurrentFlags->t == 0) {
        tmp = 1;
    }

    return tmp;
}

void flagHandling(int argc, char *argv[], struct activeFlags *pCurrentFlags) {
    if (checkNullFlags(pCurrentFlags)) {
        withoutFlags(argc, argv);
    }

    if (pCurrentFlags->s == 1) {
        printf("Срабатывание флага -s\n");
    }

    if (pCurrentFlags->b == 1) {
        printf("Срабатывание флага -b\n");
    }

    if (pCurrentFlags->n == 1) {
        printf("Срабатывание флага -n\n");
        flagN_Activate(argc, argv);
    }

    if (pCurrentFlags->t == 1) {
        printf("Срабатывание флага -t\n");
    }

    if (pCurrentFlags->e == 1) {
        printf("Срабатывание флага -e\n");
    }
}

void withoutFlags(int argc, char *argv[]) {
    FILE *file;
    int chr;
    int count;

    for (count = 1; count < argc; count++) {
        if((file = fopen(argv[count], "r")) == NULL) {
            continue;
        }

        while((chr = getc(file)) != EOF) {
            fprintf(stdout, "%c", chr);
        }

        fclose(file);
    }
}

void flagN_Activate(int argc, char *argv[]) {
    const int MAX_LINE = 1000000;
    char temp_filename[5000];
    FILE *file, *temp;
    int count;
    char buffer[MAX_LINE];
    for (count = 1; count < argc; count++) {
        if((file = fopen(argv[count], "r")) == NULL) {
            continue;
        }

        strcpy(temp_filename, "temp_");
        strcat(temp_filename, argv[count]);

        temp = fopen(temp_filename, "w");

        if (temp == NULL) {
            printf("ОШИБКА ФАЙЛА\n");
        }

        int current_line = 1;

        while (fgets(buffer, MAX_LINE, file) != NULL) {
            fprintf(temp, "%d %s", current_line++, buffer);
        }
        fclose(file);
        fclose(temp);
        output(temp_filename, temp);
    }
}

void output(char *temp_filename, FILE* temp) {
        int chr;
        temp = fopen(temp_filename, "r");
        while((chr = getc(temp)) != EOF) {
            fprintf(stdout, "%c", chr);
        }

        fclose(temp);
        remove(temp_filename);
}
