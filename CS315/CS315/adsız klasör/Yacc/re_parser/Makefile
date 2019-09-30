CC     = g++
CXX    = g++
LEX    = flex
YACC   = bison -y
YFLAGS = -d
PROGRAM = re_parser

OBJECTS = $(PROGRAM).o scan.o parse.o Expression.o

all: re_parser

re_parser: $(OBJECTS)
scan.o: scan.l parse.c
parse.o: parse.y Expression.h
$(PROGRAM).o: $(PROGRAM).cpp 
Expression.o: Expression.cpp Expression.h

clean:
	-rm -f $(OBJECTS)
	-rm -f y.tab.h
	-rm -f parse.c
	-rm -f $(PROGRAM)
