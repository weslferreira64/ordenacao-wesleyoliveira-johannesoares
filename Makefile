CC = gcc
WARN = -Wall -Wextra -std=c11
CFLAGS = $(WARN) -O2
DEPFLAGS = -MMD -MP

ALG_SRCS = src/basicos/bubble.c src/basicos/selection.c src/basicos/insertion.c src/avancados/merge.c src/avancados/quick.c src/avancados/heap.c
SRCS = src/main.c $(ALG_SRCS)

OBJS = $(SRCS:.c=.o)
ALL_OBJS = $(sort $(OBJS))

TARGET = sort_main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(ALL_OBJS) $(ALL_OBJS:.o=.d)

.PHONY: all clean

-include $(ALL_OBJS:.o=.d)