# Create jar file to run WordCount in Hadoop

all : Job1.jar Job1_3705.jar Job2.jar

Job1.jar : Job1.java Job1Mapper.java Job1Reducer.java
	javac -classpath "${HADOOP_CLASSPATH}" $^
	jar -cvf $@ $(^:.java=.class)

Job1_3705.jar : Job1_3705.java WordMapper.java WordPairReducer3705.java
	javac -classpath "${HADOOP_CLASSPATH}" $^
	jar -cvf $@ $(^:.java=.class)

Job2.jar : Job2.java Job2Mapper.java Job2Reducer.java
	javac -classpath "${HADOOP_CLASSPATH}" $^
	jar -cvf $@ $(^:.java=.class)

clean:
	rm -f *.jar *.class
