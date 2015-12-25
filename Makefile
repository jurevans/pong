##############################
# Makefile :: PONG -JRE V.10 #
##############################

CC	= gcc
CFLAGS	= -Wall -Wstrict-prototypes -g
SRC	= ./src/
OBJ	= $(SRC)obj/
INCLUDES= -I .$(SRC)include -I../include
MAIN	= pong
BIN	= ./bin/
OBJS	= ball.o field.o user.o paddle.o screen.o
LINK	= -lcurses

default: pong

pong:	$(OBJS)
	mkdir -p bin &&  $(CC) -o $(BIN)$(MAIN) $(SRC)pong.c $(OBJ)ball.o $(OBJ)field.o $(OBJ)user.o $(OBJ)paddle.o $(OBJ)screen.o $(CFLAGS) $(LINK)

ball.o:
	mkdir -p src/obj && $(CC) $(CFLAGS) -c $(SRC)ball.c -o $(OBJ)ball.o

field.o:
	mkdir -p src/obj && $(CC) $(CFLAGS) -c $(SRC)field.c -o $(OBJ)field.o

user.o:
	mkdir -p src/obj && $(CC) $(CFLAGS) -c $(SRC)user.c -o $(OBJ)user.o

paddle.o:
	mkdir -p src/obj && $(CC) $(CFLAGS) -c $(SRC)paddle.c -o $(OBJ)paddle.o

screen.o:
	mkdir -p src/obj && $(CC) $(CFLAGS) -c $(SRC)screen.c -o $(OBJ)screen.o

##################################################################################

clean:
	rm -rfv bin && rm -rfv src/obj

test:
	valgrind $(BIN)$(MAIN) --leak-check=full -v

install:
	cp -v bin/$(MAIN) /usr/local/bin/$(MAIN)

uninstall:
	rm -fv /usr/local/bin/$(MAIN)

#############################
