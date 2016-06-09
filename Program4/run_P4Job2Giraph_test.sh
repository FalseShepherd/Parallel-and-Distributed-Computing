#!/bin/bash

# Set names of jar file and class to run
JAR_FILE="AllShortestPaths.jar"
RUN_CLASS="AllShortestPaths"

# Set names of HDFS directories for input and output
# Input should already be on HDFS from Job1
# Output will be copied back from HDFS
INPUT_DIR=Job1TestOutput
OUTPUT_DIR=Job2TestOutput

# Remove any old copies of output directory on HDFS and Linux FS
hadoop fs -rm -f -r "$PWD/$OUTPUT_DIR"
rm -rf "./$OUTPUT_DIR"

# Run Giraph program in Hadoop
#   -eip edge input location (HDFS only)
#   -eif edge input format
#   -vof vertex output format
#   -op  output location (HDFS ONLY)
#   -w   number of workers
giraph "$JAR_FILE" \
  "$RUN_CLASS" \
  -eif UndirectedTextEdgeInputFormat \
  -eip "$PWD/$INPUT_DIR" \
  -vof org.apache.giraph.io.formats.IdWithValueTextOutputFormat \
  -op "$PWD/$OUTPUT_DIR" \
  -w 1 \
  2>&1 | tee $0.log

# Copy result from HDFS
if [ "${PIPESTATUS[0]}" -eq 0 ] ; then
  echo "Copying output directory $OUTPUT_DIR"
  hadoop fs -get "$PWD/$OUTPUT_DIR" .
fi
