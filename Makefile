CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

EXECUTABLE = main
TEST_EXECUTABLE = test_parse_string
INPUT = input.bej
FILENAME = output
OUTPUT = output.json
TEST_FILE = test_file.bin

.PHONY: all run clean result test

all: $(EXECUTABLE)

$(EXECUTABLE): main.c bej_parser.c
	$(CC) $(CFLAGS) $^ -o $@
	./$(EXECUTABLE) $(INPUT) $(FILENAME)

result:
	cat $(OUTPUT)
	@echo

clean:
	rm -f $(EXECUTABLE) $(OUTPUT) $(TEST_EXECUTABLE) $(TEST_FILE)

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): test_parse_string.c bej_parser.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean result test
