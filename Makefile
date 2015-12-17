##############################
# Makefile :: PONG -JRE V.10 #
##############################

CC		= gcc
CFLAGS		= -Wall -Wstrict-prototypes -g -I.
SOURCES		= ./src/
BIN		= ./bin/
OBJ		= pong
LDFLAGS		= -lncurses

all: pong

pong:
	mkdir -p bin && $(CC) -o $(BIN)borders.o $(SOURCES)borders.c $(LDFLAGS) $(CFLAGS) \
		&& $(CC) -o $(BIN)$(OBJ) $(SOURCES)pong.c $(LDFLAGS) $(CFLAGS) 

clean:
	rm -rfv $(BIN)

test:
	valgrind $(BIN)$(OBJ) --leak-check=full -v

install:
	cp -v bin/$(OBJ) /usr/local/bin/$(OBJ)

uninstall:
	rm -fv /usr/local/bin/$(OBJ)

#############################

