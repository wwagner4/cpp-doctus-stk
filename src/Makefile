CXXFLAGS =	-O2 -g -Wall -I../stk/include -D__OS_MACOSX__ -fmessage-length=0

LIBS =	../stk/lib/*

all: Tryout

clean: 
	rm -f \
	Tryout.o Tryout \
    Node.o 

Tryout:	Tryout.o Node.o
	$(CXX) -o Tryout Tryout.o Node.o $(LIBS)

Node:	Node.o
	$(CXX) -o Node Node.o $(LIBS)
