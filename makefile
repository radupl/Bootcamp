CC = gcc
#LDFLAGS = flags
TARGET = problem13
SRCS = problem13.c
DEPS = problem13.h
OBJS = $(SRCS:.c=.o)
.PHONY: all clean
all: $(TARGET)
 
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< -i $(CFLAGS)
 
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
clean:
	rm -f $(TARGET)