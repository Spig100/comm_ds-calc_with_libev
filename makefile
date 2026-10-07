CC	:= gcc
LDFLAGS	:= -lev 

TARGET	:= app

SRC_DIR	:= src
SRCS	:= $(wildcard $(SRC_DIR)/*.c)

INC_DIR	:= inc

CFLAGS	:= -Wall -MMD -MP -I$(INC_DIR)

OBJS	:= $(SRCS:.c=.o)
DEPS	:= $(SRCS:.c=.d)

.PHONY: all clean

calculator: $(TARGET)
	rm -f $(OBJS) $(DEPS)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET) *.swp
