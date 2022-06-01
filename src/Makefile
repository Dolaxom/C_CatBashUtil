TARGET = s21_cat
PATH = ../data/test.txt ../data/test2.txt

build:
	gcc -Wall -Werror -Wextra s21_cat.c s21_main_cat.c -o $(TARGET)

all:
	./$(TARGET) -b -n -e $(PATH)

base:
	./$(TARGET) $(PATH)

N:
	./$(TARGET) -n $(PATH)

B:
	./$(TARGET) -n -b -n $(PATH)

E:
	./$(TARGET) -e $(PATH)

NE:
	./$(TARGET) -n -e $(PATH)

BE:
	./$(TARGET) -b -e $(PATH)
	
T:
	./$(TARGET) -t $(PATH)
