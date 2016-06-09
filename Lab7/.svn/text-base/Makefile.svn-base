# Create jar files for Giraph Lab 7

all : SpanningTree.jar

SHELL=/bin/bash

# Rule to build and package classes in a jar file.  Includes
# the specified Java source files and all generated classes
# (including nested classes)
%.jar: %.java
	javac -classpath "${HADOOP_CLASSPATH}" -Xlint:unchecked $^
	shopt -s nullglob ; jar -cvf $@ $(^:.java=.class) $(^:.java=\$$*.class)

SpanningTree.jar : SpanningTree.java UndirectedTextEdgeInputFormat.java

clean:
	rm -f *.jar *.class
