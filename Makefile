CC = gcc
CFLAGS =
TARGET = fileManager

INCL = src/include/

SRCS = $(wildcard src/structures/*.c \
	   src/model/*.c \
	   src/view/*.c \
	   src/controller/*.c)

OBJ = $(SRCS:.c=.o)

OUT = bin/

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCL) -c $< -o $@

build: $(OUT)$(TARGET)

$(OUT)$(TARGET): $(OBJ)
	$(CC) $^ -o $@

run:
	bin/$(TARGET)
