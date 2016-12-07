CXXFLAGS =	-O3 -w -D__OS_MACOSX__\
        -I../stk/include \
        -I${JAVA_HOME}/include \
        -I${JAVA_HOME}/include/darwin

LIBS = ../stk/lib/*

all: libJStk.jnilib

run: all
	java JStk

clean: 
	rm -f *.class *.o JStk.h *.jnilib 
	rm -rf *.dSYM 

Node: Node.o
	$(CXX) -o Node Node.o $(LIBS)

JStk.class : JStk.java
	javac JStk.java
	
JStk.h : JStk.class
	javah -jni JStk

libJStk.jnilib: JStk.h Node.o JStk.cpp 
	$(CXX) $(CXXFLAGS) \
	-dynamiclib -framework JavaVM \
	-o libJStk.jnilib JStk.cpp Node.o $(LIBS)
	
