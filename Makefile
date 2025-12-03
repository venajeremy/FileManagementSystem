CC = gcc
CFLAGS = 
TARGET = fileManager

SRCS = $(wildcard src/structures/*.c \
	   src/model/*.c \
	   src/view/*.c \
	   src/controller/*.c)

OBJ = $(SRCS:.c=.o)

OUT = bin/

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OUT)$(TARGET)

$(OUT)$(TARGET): $(OBJ)
	$(CC) $^ -o $@

