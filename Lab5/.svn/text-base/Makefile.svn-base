# Create jar file to run WordCount in Hadoop

Lab5.jar : Lab5.java PointMapper.java PointReducer.java
	javac -classpath "${HADOOP_CLASSPATH}" $^
	jar -cvf $@ $(^:.java=.class)

clean:
	rm -f *.jar *.class
