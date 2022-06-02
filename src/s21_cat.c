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
                pCurrentFlags->b = 1;
                pCurrentFlags->n = 0;
                break;

            case 'e':
                pCurrentFlags->e = 1;
                break;

            case 'n':
                if (pCurrentFlags->b == 0) {
                    pCurrentFlags->n = 1;
                }
                break;

            case 's':
                pCurrentFlags->s = 1;
                break;

            case 't':
                pCurrentFlags->t = 1;
                break;

            default:
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
            flagS_Activate();
        }

        if (pCurrentFlags->b == 1) {
            flagB_Activate();
        }

        if (pCurrentFlags->n == 1) {
            flagN_Activate();
        }

        if (pCurrentFlags->t == 1) {
            flagT_Activate();
        }

        if (pCurrentFlags->e == 1) {
            flagE_Activate();
        }
        output();
        deleteCopyFiles();
    }

}

void createCopyFiles(int argc, char *argv[]) {
    const int MAX_LINE = 999999;
    char temp_filename[5000];
    FILE *file, *temp;
    char buffer[MAX_LINE];
    int stepsPrintA = 1;
    for (int count = 1; count < argc; count++) {
        if ((file = fopen(argv[count], "r")) == NULL) {
            continue;
        }
        int offset = 0;
        char nameOfFile[200];
        strcpy(nameOfFile, argv[count]);
        int lengthNameOfFile = strlen(nameOfFile);
        for (int i = lengthNameOfFile; i > 0; i--) {
            if (nameOfFile[i] == '/') {
                offset = ++i;
                break;
            }
        }
        char tmp[2000] = "";
        int j = 0;
        for (int z = 0; z < stepsPrintA; z++) {
            tmp[z] = 'A';
        }
        for (int i = 0; i < lengthNameOfFile; i++) {
            if (i < offset) {
                continue;
            }
            tmp[j + stepsPrintA] = nameOfFile[i];
            j++;
        }
        stepsPrintA++;
        strcpy(nameOfFile, tmp);
        strcpy(temp_filename, "./tmp/tmp_");
        strcat(temp_filename, nameOfFile);

        mkdir("tmp", S_IRWXU);

        temp = fopen(temp_filename, "w");

        if (temp == NULL) {
            printf("error %s\n", temp_filename);
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

void flagS_Activate() {
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

        int flagToNullStr = 0;

        while (fgets(buffer, MAX_LINE, file)) {
            if (strlen(buffer) > 1 || buffer[0] == '\t') {
                flagToNullStr = 0;
                fprintf(temp, "%s", buffer);
            } else {
                if (flagToNullStr != 1) {
                    fprintf(temp, "%s", buffer);
                }
                flagToNullStr = 1;
            }
        }

        fclose(temp);
        fclose(file);

        remove(filename);
        rename(temp_filename, filename);
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

void flagB_Activate() {
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
            if (strlen(buffer) > 1 || buffer[0] == '\t') {
                fprintf(temp, "%6d\t%s", current_line++, buffer);
            } else {
                fprintf(temp, "%s", buffer);
            }
        }

        fclose(temp);
        fclose(file);

        remove(filename);
        rename(temp_filename, filename);
    }
}

void flagT_Activate() {
    FILE *file, *temp;
    const int MAX_LINE = 2000;
    char filename[MAX_LINE];
    char temp_filename[MAX_LINE];
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
        strcpy(temp_filename, "./tmp/tmp____");
        strcat(temp_filename, entry->d_name);

        file = fopen(filename, "r");
        temp = fopen(temp_filename, "w");

        if (file == NULL || temp == NULL) {
            fclose(file);
            fclose(temp);
            continue;
        }

        int i = 0;
        while((chr = getc(file)) != EOF) {
            if ((int)chr == 9 && i > 6) {
                fprintf(temp, "%s", "^I");
            } else {
                fprintf(temp, "%c", chr);
            }
            i++;

            if ((int)chr == 10) {
                i = 0;
            }
        }

        fclose(temp);
        fclose(file);

        remove(filename);
        rename(temp_filename, filename);
    } 
}

void flagE_Activate() {
    FILE *file, *temp;
    const int MAX_LINE = 2000;
    char filename[MAX_LINE];
    char temp_filename[MAX_LINE];
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
        strcpy(temp_filename, "./tmp/tmp____");
        strcat(temp_filename, entry->d_name);

        file = fopen(filename, "r");
        temp = fopen(temp_filename, "w");

        if (file == NULL || temp == NULL) {
            fclose(file);
            fclose(temp);
            continue;
        }

        while((chr = getc(file)) != EOF) {
            if (chr == '\n') {
                fprintf(temp, "%c", 36);
                fprintf(temp, "%c", chr);
            } else {
                fprintf(temp, "%c", chr);
            }
        }

        fclose(temp);
        fclose(file);

        remove(filename);
        rename(temp_filename, filename);
    }
}

void output() {
    struct dirent **namelist;
    int n;
    FILE *file;
    char filename[2000];
    int chr;

    n = scandir("tmp", &namelist, 0, alphasort);
    if (n < 0) {
        perror("scandir");
    } else {
        while (n--) {
            if (namelist[n]->d_name[0] == '.') {
                continue;
            }
            strcpy(filename, "./tmp/");
            strcat(filename, namelist[n]->d_name);

            file = fopen(filename, "r");
            if (file == NULL) {
                fclose(file);
                continue;
            }

            while((chr = getc(file)) != EOF) {
                fprintf(stdout, "%c", chr);
            }

            fclose(file);

            free(namelist[n]);
        }

        free(namelist);
    }
}
