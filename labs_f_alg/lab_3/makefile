CC = gcc
STD_FLAGS = -Wall -Werror -Wextra -std=c11

all: func.o main.o
	$(CC) $(STD_FLAGS) $^ -lm -o task_3.exe

func.o: func.c
	$(CC) $(STD_FLAGS) -c $<

main.o: main.c
	$(CC) $(STD_FLAGS) -c $<

clean:
	rm -f *.out *.o

rebuild: clean all

run: task_3
	./task_3
