CC     = g++
CXX    = g++
LEX    = flex
YACC   = yacc
PROG   = ellie
OUTP	= parser

all: $(PROG)

lex.yy.c: $(PROG).l
	$(LEX) $(PROG).l

y.tab.c: $(PROG).y
	$(YACC) -d $(PROG).y


$(PROG): y.tab.c lex.yy.c
	$(CXX) -o $(OUTP) y.tab.c lex.yy.c -ll

test: input
	cat input | ./$(OUTP)

clean:
	-rm -f lex.yy.c
	-rm -f y.tab.c
	-rm -f y.tab.h
	-rm -f $(OUTP)

