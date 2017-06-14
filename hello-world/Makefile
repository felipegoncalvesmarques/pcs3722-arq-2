CC=gcc -Wall -Wextra -static -pg

.PHONY: all clean
all: program

clean:
	rm -rf program profile-data.txt gmon.out hello-world.o 

program: hello-world.o
	$(CC) -o $@ $^
