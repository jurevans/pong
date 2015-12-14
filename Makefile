# Makefile
CC		= gcc
CFLAGS		= -I.
DEPS		= pong.h
SOURCES		= ./src/
BIN		= ./bin/
OBJ		= pong
TARGETPATH	= $(BIN)
##############################
LDFLAGS		= -lncurses

all: pong

pong:
	$(CC) -o $(BIN)$(OBJ) $(SOURCES)pong.c $(LDFLAGS) $(CFLAGS)
#############################

