CC = gcc
CFLAGS = 
TARGET = fileManager

SRCS = src/structures \
	   src/model \
	   src/view \
	   src/

start:
	echo "Compiling..."
	gcc src/structures
