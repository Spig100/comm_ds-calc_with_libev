CC	:= gcc
CFLAGS	:= -Wall -MMD -MP
LDFLAGS	:= LDFLAGS

TARGET	:= app

SRCS	:= $(wildcard *.c)

OBJS	:= $(SRCS:.c=.o)
DEPS	:= $(SRCS:.c=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)
