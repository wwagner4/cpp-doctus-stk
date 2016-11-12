CXXFLAGS =	-O3 -g -w -I../stk/include -D__OS_MACOSX__

LIBS =	../stk/lib/*

all: Tryout Parser

clean: 
	rm -f \
	Tryout.o Tryout \
	Parser.o Parser \
    Node.o 

Tryout:	Tryout.o Node.o
	$(CXX) -o Tryout Tryout.o Node.o $(LIBS)

Parser:	Parser.o 
	$(CXX) -o Parser Parser.o $(LIBS)

Node: Node.o
	$(CXX) -o Node Node.o $(LIBS)
