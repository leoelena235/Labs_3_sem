CC = gcc
STD_FLAGS = -Wall -Werror -Wextra -std=c11

all: func.o main.o
	$(CC) $(STD_FLAGS) $^ -o task_10.exe

functions.o: functions.c
	$(CC) $(STD_FLAGS) -c $<

main.o: main.c
	$(CC) $(STD_FLAGS) -c $<

clean:
	rm -f *.out *.o

rebuild: clean all
run: task_10.out
	./task_10
