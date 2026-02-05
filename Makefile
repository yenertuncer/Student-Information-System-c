CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./src


SRCS = src/main.c src/menu.c src/student.c src/course.c src/professor.c src/enrollment.c src/grade.c src/utils.c src/curriculum.c
OBJS = $(SRCS:.c=.o)

TARGET = StudentSystem


.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET) $(TARGET).exe valgrind_log.txt test_suite test_results.txt


test:
	$(CC) $(CFLAGS) src/student.c src/course.c src/utils.c src/professor.c src/enrollment.c src/grade.c tests/test_main.c -o test_suite
	./test_suite > test_results.txt
	cat test_results.txt