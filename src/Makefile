CXXFLAGS =	-O2 -g -Wall -I../stk/include -D__OS_MACOSX__ -fmessage-length=0

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
