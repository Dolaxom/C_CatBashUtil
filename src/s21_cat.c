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
            break;
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
    int tmp = 1;
    if (checkNullFlags(pCurrentFlags)) {
        withoutFlags(argc, argv);
        tmp = 0;
    }

    if (tmp == 1) {
        createCopyFiles(argc, argv);

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
        output();
        deleteCopyFiles();
    }

}

void createCopyFiles(int argc, char *argv[]) {
    const int MAX_LINE = 1000000;
    char temp_filename[5000];
    FILE *file, *temp;
    char buffer[MAX_LINE];
    for (int count = 1; count < argc; count++) {
        if((file = fopen(argv[count], "r")) == NULL) {
            continue;
        }

        mkdir("tmp", S_IRWXU);

        strcpy(temp_filename, "./tmp/tmp_");
        strcat(temp_filename, argv[count]);
        
        DIR *folder;
        struct dirent *dir;
        folder = opendir("tmp");
        if (folder) {
            while ((dir = readdir(folder)) != NULL) {
                temp = fopen(temp_filename, "w");
            }
        }
        closedir(folder);

        if (temp == NULL) {
            printf("(not) error\n");
        }

        while (fgets(buffer, MAX_LINE, file) != NULL) {
            fprintf(temp, "%s", buffer);
        }
        fclose(file);
        fclose(temp);
    }
}

void deleteCopyFiles() {
    char temp_filename[5000];
    DIR *folder;
    struct dirent *entry;

    folder = opendir("tmp");
    if(folder == NULL) {
        perror("Нет такой папки\n");
    }

    while((entry=readdir(folder)) ) {
        strcpy(temp_filename, "./tmp/");
        strcat(temp_filename, entry->d_name);
        remove(temp_filename);
    }

    closedir(folder);

    rmdir("tmp");
}

void withoutFlags(int argc, char *argv[]) {
    FILE *file;
    int chr;

    for (int count = 1; count < argc; count++) {
        if((file = fopen(argv[count], "r")) == NULL) {
            continue;
        }

        while((chr = getc(file)) != EOF) {
            fprintf(stdout, "%c", chr);
        }

        fclose(file);
    }
}

void flagN_Activate() {
    FILE *file, *temp;
    const int MAX_LINE = 999999;
    char buffer[MAX_LINE];
    char filename[2000];
    char temp_filename[2000];

    DIR *folder;
    struct dirent *entry;
    folder = opendir("tmp");

    while ((entry=readdir(folder))) {
        if (entry->d_name[0] == '.') {
            continue;
        }

        strcpy(filename, "./tmp/");
        strcat(filename, entry->d_name);
        strcpy(temp_filename, "./tmp/tmp____");
        strcat(temp_filename, entry->d_name);

        file = fopen(filename, "r");
        temp = fopen(temp_filename, "w");

        if (file == NULL || temp == NULL) {
            fclose(file);
            fclose(temp);
            continue;
        }

        int current_line = 1;
        while (fgets(buffer, MAX_LINE, file)) {
            fprintf(temp, "%6d\t%s", current_line++, buffer);
        }

        fclose(temp);
        fclose(file);

        remove(filename);
        rename(temp_filename, filename);
    }
}

void output() {
    FILE *file;
    char filename[2000];
    int chr;

    DIR *folder;
    struct dirent *entry;
    folder = opendir("tmp");

    while ((entry=readdir(folder))) {
        if (entry->d_name[0] == '.') {
            continue;
        }

        strcpy(filename, "./tmp/");
        strcat(filename, entry->d_name);

        file = fopen(filename, "r");

        if (file == NULL) {
            fclose(file);
            continue;
        }

        while((chr = getc(file)) != EOF) {
            fprintf(stdout, "%c", chr);
        }

        fclose(file);
    }
}
