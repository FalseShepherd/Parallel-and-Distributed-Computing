# Create jar files for Giraph Lab 
#   (add LongestPathDAG.jar to end of line to build it by default)

all : SimpleShortestPathsComputation.jar LongestPathDAG.jar

SHELL=/bin/bash

# Rule to build and package classes in a jar file.  Includes
# the specified Java source files and all generated classes
# (including nested classes)
%.jar: %.java
	javac -classpath "${HADOOP_CLASSPATH}" $^
	shopt -s nullglob ; jar -cvf $@ $(^:.java=.class) $(^:.java=\$$*.class)

SimpleShortestPathsComputation.jar : SimpleShortestPathsComputation.java

# Uncomment the following line to build longest path jar file
LongestPathDAG.jar : LongestPathDAG.java

clean:
	rm -f *.jar *.class
