CC	= g++
CXX     = g++
PROGRAM = calculator

OBJECTS = $(PROGRAM).o Lexer.o Parser.o Expression.o Statement.o Indenter.o Numeric.o

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
Lexer.o: Lexer.cpp Lexer.h
Indenter.o: Indenter.cpp Indenter.h
Expression.o : Expression.cpp Expression.h Indenter.h
Statement.o : Statement.cpp Statement.h Expression.h Indenter.h
Parser.o: Parser.cpp Parser.h Lexer.h Expression.h
Numeric.o: Numeric.cpp Numeric.h
$(PROGRAM).o: $(PROGRAM).cpp Lexer.h Parser.h Expression.h Statement.h Numeric.h

clean:
	-rm -f $(OBJECTS)
	-rm -f $(PROGRAM)
