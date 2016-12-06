CXXFLAGS =	-O3 -g -w -I../stk/include \
    -I${JAVA_HOME}/include \
	  -I${JAVA_HOME}/include/darwin \
    -D__OS_MACOSX__

LIBS = ../stk/lib/*

all: libDoctusStkJni.jnilib

run: all
	java DoctusStkJni

clean: 
	rm -f Tryout *.class *.o DoctusStkJni.h libDoctusStkJni.jnilib

Tryout:	Tryout.o Node.o
	$(CXX) -o Tryout Tryout.o Node.o $(LIBS)

Node: Node.o
	$(CXX) -o Node Node.o $(LIBS)

DoctusStkJni.class: DoctusStkJni.java
	javac DoctusStkJni.java
	
DoctusStkJni.h : DoctusStkJni.class
	javah -jni DoctusStkJni

libDoctusStkJni.jnilib: DoctusStkJni.h DoctusStkJni.cpp 
	$(CXX) 
		-o libDoctusStkJni.jnilib DoctusStkJni.cpp Node.o $(LIBS) -dynamiclib -framework JavaVM