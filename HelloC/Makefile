APP = HelloCExecutable
OBJ = main.o

CC ?= cc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Wfatal-errors

$(APP): $(OBJ)
	@echo "Linking $(OBJ) to $(APP)"
	$(CC) $^ -o $@ $(CFLAGS)

%.o: %.c
	@echo "Compiling $< to $@"
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(APP) $(OBJ)

test:
	./$(APP)

.PHONY: clean test
