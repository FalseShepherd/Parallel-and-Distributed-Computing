# Create jar files for COMP3705/4705 Program 4

all : P4Job1MR.jar AllShortestPaths.jar

SHELL=/bin/bash

# Rule to build and package classes in a jar file.  Includes
# the specified Java source files and all generated classes
# (including nested classes)
%.jar: %.java
	javac -Xlint:unchecked -classpath ".:${HADOOP_CLASSPATH}" $^
	shopt -s nullglob ; jar -cvf $@ $(^:.java=.class) $(^:.java=\$$*.class)

P4Job1MR.jar : P4Job1MR.java PointMapper.java PointReducer.java

AllShortestPaths.jar : AllShortestPaths.java UndirectedTextEdgeInputFormat.java \
		VertexDistanceWritable.java VertexDistanceArrayWritable.java SMapWritable.java

clean:
	rm -f *.jar *.class

rebuild: clean all
