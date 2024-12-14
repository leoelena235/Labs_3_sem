CC = gcc
STD_FLAGS = -Wall -Werror -Wextra -std=c11

OUTPUT = task_3

all: func.o main.o
	$(CC) $(STD_FLAGS) $^ -lm -o $(OUTPUT)

func.o: func.c
	$(CC) $(STD_FLAGS) -c $<

main.o: main.c
	$(CC) $(STD_FLAGS) -c $<

clean:
	rm -f *.o $(OUTPUT)

rebuild: clean all

run: $(OUTPUT)
	./$(OUTPUT)
