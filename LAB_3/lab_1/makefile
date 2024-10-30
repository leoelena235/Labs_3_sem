CC = gcc
STD_FLAGS = -Wall -Werror -Wextra -std=c11

all: func.o main.o
	$(CC) $(STD_FLAGS) $^ -lm -o task_1.exe

func.o: func.c
	$(CC) $(STD_FLAGS) -c $<

main.o: main.c
	$(CC) $(STD_FLAGS) -c $<

clean:
	rm -f *.out *.o

rebuild: clean all

run: task_1.out
	./task_1