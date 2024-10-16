CC = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all: main.o func.o
	$(CC) $(CFLAGS) main.o func.o -o task_4.exe

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

func.o: func.c
	$(CC) $(CFLAGS) -c func.c

clean:
	rm -f *.o task_4.exe