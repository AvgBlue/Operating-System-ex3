# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -pthread

# Source files
SRCS = main.c producer.c filereader.c co_editor.c dispatcher.c screen_manager.c unbounded_buffer.c
HEADERS = bounded_buffer.h co_editor.h dispatcher.h filereader.h producer.h runnable.h screen_manager.h unbounded_buffer.h

# Object files
OBJS = $(SRCS:.c=.o)

# Executable
EXEC = ex3.out

.PHONY: all clean run

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(EXEC)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)
