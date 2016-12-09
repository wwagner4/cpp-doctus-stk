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

JStk.class : JStk.java IJStk.class JStkNodeSine.class JStkNodeGain.class \
             JStkNodeSequence.class JStkNodeSum.class ValueType.class \
             NodeClass.class
	javac JStk.java

IJStk.class : IJStk.java
	javac IJStk.java;

JStkNode.class: JStkNode.java
	javac JStkNode.java

ValueType.class: ValueType.java
	javac ValueType.java

NodeClass.class: NodeClass.java
	javac NodeClass.java

JStkContainer.class: JStkContainer.java
	javac JStkContainer.java

JStkNodeSequence.class: JStkNodeSequence.java JStkNode.class JStkContainer.class
	javac JStkNodeSequence.java

JStkNodeSum.class: JStkNodeSum.java JStkNode.class JStkContainer.class
	javac JStkNodeSum.java

JStkNodeSine.class: JStkNodeSine.java JStkNode.class
	javac JStkNodeSine.java

JStkNodeGain.class: JStkNodeGain.java JStkNode.class
	javac JStkNodeGain.java

JStk.h : JStk.class
	javah -v -force JStk

libJStk.jnilib: JStk.h Node.o JStk.cpp
	$(CXX) $(CXXFLAGS) \
	-dynamiclib -framework JavaVM \
	-o libJStk.jnilib JStk.cpp Node.o $(LIBS)

