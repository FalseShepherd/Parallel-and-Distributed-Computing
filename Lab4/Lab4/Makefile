# Create jar file to run WordCount in Hadoop

WordIndex.jar : WordIndex.java WordMapper.java IndexReducer.java
	javac -classpath "${HADOOP_CLASSPATH}" $^
	jar -cvf $@ *.class

clean:
	rm -f *.jar *.class
