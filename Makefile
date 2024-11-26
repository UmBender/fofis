CC = gcc
CFLAGS_DEV = -lm -lGL -lpthread -ldl -lrt -lX11 -Wall -g -Og -Werror -pedantic
CFLAGS_RELEASE =  -Oz -lm -lGL -lpthread -ldl -lrt -lX11 -pedantic -pedantic-errors

# Target executable
TARGET_DEV = main-dev
TARGET_RELEASE = main 

# Source files
SRCS = main.c fofis.c

# Object files
OBJS_DEV = $(SRCS:.c=-dev.o)
OBJS_RELEASE = $(SRCS:.c=-release.o)

# Default target
all: dev release 

# Rule to compile .c files into .o files
%-dev.o: %.c
	$(CC) $(CFLAGS_DEV) -c $< -o $@

%-release.o: %.c
	$(CC) $(CFLAGS_RELEASE) -c $< -o $@


# Rule to link object files into executable
$(TARGET_DEV): $(OBJS_DEV)
	$(CC) $(OBJS_DEV) -o $(TARGET_DEV)

$(TARGET_RELEASE): $(OBJS_RELEASE)
	$(CC) $(OBJS_RELEASE) -o $(TARGET_RELEASE)

dev: $(TARGET_DEV)

release: $(TARGET_RELEASE)

# Rule to clean up intermediate object files and executable
clean:
	rm -f $(OBJS_DEV) $(TARGET_DEV) $(OBJS_RELEASE) $(TARGET_RELEASE)
