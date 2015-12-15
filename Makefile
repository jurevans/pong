##############################
# Makefile
##############################

CC		= gcc
CFLAGS		= -Wall -g -I.
DEPS		= pong.h
SOURCES		= ./src/
BIN		= ./bin/
OBJ		= pong
TARGETPATH	= $(BIN)
LDFLAGS		= -lncurses

all: pong

pong:
	$(CC) -o $(BIN)$(OBJ) $(SOURCES)pong.c $(LDFLAGS) $(CFLAGS)

clean:
	rm -rfv $(BIN)$(OBJ)*

test:
	valgrind $(BIN)$(OBJ) 

install:
	cp -v bin/$(OBJ) /usr/local/bin/$(OBJ)

uninstall:
	rm -fv /usr/local/bin/$(OBJ)

	

#############################

