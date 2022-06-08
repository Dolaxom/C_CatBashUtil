#include "s21_cat.h"

void init(struct activeFlags *pCurrentFlags) {
    pCurrentFlags->b = 0;
    pCurrentFlags->e = 0;
    pCurrentFlags->n = 0;
    pCurrentFlags->s = 0;
    pCurrentFlags->t = 0;
    pCurrentFlags->v = 0;
}

void searchArgs(int argc, char *argv[], struct activeFlags *pCurrentFlags) {
    init(pCurrentFlags);
    int res = 0;

    while ((res = getopt(argc, argv, "+benstv")) != -1) {
        switch (res) {
            case 'b': 
                pCurrentFlags->b = 1;
                pCurrentFlags->n = 0;
                break;

            case 'e':
                pCurrentFlags->e = 1;
                pCurrentFlags->v = 1;
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
                pCurrentFlags->v = 1;
                break;

            case 'v':
                pCurrentFlags->v = 1;

            default:
                break;
        }
    }
}

void flagHandling(int argc, char *argv[], struct activeFlags *pCurrentFlags) {
    FILE *file;
    const int MAX_LINE = 999999;
    char original[MAX_LINE];
    char buffer[MAX_LINE];
    for (int count = 1; count < argc; count++) {
        if((file = fopen(argv[count], "r")) == NULL) {
            continue;
        }
        int current_line = 1;
        int flagToNullStr = 0;
        while (fgets(original, MAX_LINE, file)) {
            // flag s
            if (pCurrentFlags->s == 1) {
                if (strlen(original) > 1 || original[0] == '\t') {
                    flagToNullStr = 0;
                } else {
                    if (flagToNullStr == 1) {
                        continue;
                    }
                    flagToNullStr = 1;
                }
            }
            // flag b
            if (pCurrentFlags->b == 1) {
                strcpy(buffer, original);
                if (strlen(buffer) > 1 || buffer[0] == '\t') {
                    sprintf(buffer, "%6d\t%s", current_line++, original);
                } else {
                    if (pCurrentFlags->e == 1) {
                        #ifdef __APPLE__
                            if (__builtin_available( macOS 12.0, * )) {
                                sprintf(buffer, "      \t%s", original);
                            } else {
                                sprintf(buffer, "%s", original);
                            }
                        #endif

                        #ifdef __linux__
                            sprintf(buffer, "%s", original);
                        #endif
                    } else {
                        sprintf(buffer, "%s", original);
                    }
                }
                strcpy(original, buffer);
            }
            // flag n
            if (pCurrentFlags->n == 1) {
                sprintf(buffer, "%6d\t%s", current_line++, original);
                strcpy(original, buffer);
            }
            // flag t
            if (pCurrentFlags->t == 1) {
                memset(buffer, 0 , 999999);
                size_t length = strlen(original);
                size_t j = 0;
                for (size_t i = 0; i < length; i++) {
                    if ((int)original[i] != 9) {
                        buffer[j] = original[i];
                    } else {
                        if (pCurrentFlags->b == 1 || pCurrentFlags->n == 1) {
                            if (i < 7) {
                                buffer[j] = original[i];
                            } else {
                                buffer[j] = '^';
                                j++;
                                buffer[j] = 'I';
                            }
                        } else {
                            buffer[j] = '^';
                            j++;
                            buffer[j] = 'I';
                        }

                    }
                    j++;
                }

                strcpy(original, buffer);
            }
            // flag e
            if (pCurrentFlags->e == 1) {
                strcpy(buffer, original);
                char *ptr = strchr(buffer, '\n');
                if (ptr != NULL) {
                    *ptr = '$';
                    strcat(buffer, "\n");
                }
                strcpy(original, buffer);
            }
            // flag v
            if (pCurrentFlags->v == 1) {
                memset(buffer, 0 , 999999);
                size_t length = strlen(original);
                size_t j = 0;
                for (size_t i = 0; i < length; i++) {
                    if ((int)original[i] == 9 || (int)original[i] == 10
                    || !iscntrl(original[i])) {
                        buffer[j] = original[i];
                    } else {
                        if (pCurrentFlags->b == 1 || pCurrentFlags->n == 1) {
                            if (i < 7) {
                                buffer[j] = original[i];
                            } else {
                                buffer[j] = '^';
                                j++;
                                int ch = original[i];
                                if (ch == '\177') {
                                    ch = '?';
                                } else {
                                    ch = ch | 0100;
                                }
                                buffer[j] = ch;
                            }
                        } else {
                                buffer[j] = '^';
                                j++;
                                int ch = original[i];
                                if (ch == '\177') {
                                    ch = '?';
                                } else {
                                    ch = ch | 0100;
                                }
                                buffer[j] = ch;
                        }

                    }
                    j++;
                }

                strcpy(original, buffer);
            }
            
            // Final output
            printf("%s", original);
        }

        fclose(file);
    }
}
