CC = clang
CFLAGS = -pedantic -Wall -Wcomment -I./include

NAME = synacor
TESTS = synacor-tests
DEPENDENCIES = \
	src/storage.c
TEST_DEPENDENCIES = \
	src/tests/test_storage.c

all: compile

compile:
	$(CC) $(DEPENDENCIES) src/main.c -o $(NAME) $(CFLAGS)

clean:
	rm $(NAME)

test:
	$(CC) $(DEPENDENCIES) $(TEST_DEPENDENCIES) -o $(TESTS) -lcheck $(CFLAGS)
	valgrind --track-origins=yes ./$(TESTS)

