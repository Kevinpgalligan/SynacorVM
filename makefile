CC = clang
CFLAGS = -pedantic -Wall -Wcomment -I./include

NAME = synacor
TESTS_NAME = synacor-tests

DEPENDENCIES = \
	src/storage.c \
	src/execution.c \
	src/instructions.c \
	src/stack.c

TEST_DEPENDENCIES = \
	tests/testrunner.c \
	tests/test_storage.c \
	tests/test_stack.c

all: compile

compile:
	$(CC) $(DEPENDENCIES) src/main.c -o $(NAME) $(CFLAGS)

clean:
	rm $(NAME)

test:
	$(CC) $(DEPENDENCIES) $(TEST_DEPENDENCIES) -o $(TESTS_NAME) -lcheck $(CFLAGS) -g \
		&& valgrind -q --undef-value-errors=no ./$(TESTS_NAME)
