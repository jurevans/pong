##############################
# Makefile :: PONG -JRE V.10 #
##############################

CC		= gcc
CFLAGS		= -Wall -g -I.
SOURCES		= ./src/
BIN		= ./bin/
OBJ		= pong
LDFLAGS		= -lncurses

all: pong

pong:
	mkdir -p bin && $(CC) -o $(BIN)$(OBJ) $(SOURCES)pong.c $(LDFLAGS) $(CFLAGS)

clean:
	rm -rfv $(BIN)

test:
	valgrind $(BIN)$(OBJ) 

install:
	cp -v bin/$(OBJ) /usr/local/bin/$(OBJ)

uninstall:
	rm -fv /usr/local/bin/$(OBJ)

#############################

