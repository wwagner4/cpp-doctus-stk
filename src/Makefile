CXXFLAGS =	-O3 -w -D__OS_MACOSX__\
        -I../stk/include \
        -I${JAVA_HOME}/include \
        -I${JAVA_HOME}/include/darwin

LIBS = ../stk/lib/*

all: libDoctusStkJni.jnilib

run: all
	java DoctusStkJni

clean: 
	rm -f Tryout *.class *.o DoctusStkJni.h *.jnilib 
	rm -rf *.dSYM 

Tryout:	Tryout.o Node.o
	$(CXX) -o Tryout Tryout.o Node.o $(LIBS)

Node: Node.o
	$(CXX) -o Node Node.o $(LIBS)

DoctusStkJni.class : DoctusStkJni.java
	javac DoctusStkJni.java
	
DoctusStkJni.h : DoctusStkJni.class
	javah -jni DoctusStkJni

libDoctusStkJni.jnilib: DoctusStkJni.h Node.o DoctusStkJni.cpp 
	$(CXX) $(CXXFLAGS) \
	-dynamiclib -framework JavaVM \
	-o libDoctusStkJni.jnilib DoctusStkJni.cpp Node.o $(LIBS)
	
