CC	:= gcc
LDFLAGS	:= -lev 

TARGET	:= calculator

SRC_DIR	:= src
SRCS	:= $(wildcard $(SRC_DIR)/*.c)

INC_DIR	:= inc

CFLAGS	:= -Wall -MMD -MP -I$(INC_DIR) -g

OBJS	:= $(SRCS:.c=.o)
DEPS	:= $(SRCS:.c=.d)

.PHONY: all clean

all: $(TARGET)
	rm -f $(OBJS) $(DEPS)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET) *.swp
