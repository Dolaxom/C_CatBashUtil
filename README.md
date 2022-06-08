# Cat bash util in C

**Compilation:** gcc s21_cat.c s21_main_cat.c -o s21_cat

or just **make**


      \    /\
       )  ( ')
      (  /  )
       \(__)|
       
**Using:** ./s21_cat ../data/test.txt ../data/test2.txt

**Flags:** ``-s``, ``-b``, ``-n``, ``-t``, ``-e``

Example: ./s21_cat -n -e ../data/test.txt ../data/test2.txt
***
**Source files:** The main file is **s21_main_cat.c** with the main() function that accepts arguments from the terminal.

In the **s21_cat.c** file, the implementation of the argument parser, copying files, and processing them with flags. In **s21_cat.h** the declaration of all functions and struct with flags.

| macOS | ✅ |
| :---: | :---: |
| Lunux | ✅ |
| Windows | 🕗 |
