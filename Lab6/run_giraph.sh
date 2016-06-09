#!/bin/bash

# Set names of jar file and class to run
JAR_FILE="SimpleShortestPathsComputation.jar"
RUN_CLASS="SimpleShortestPathsComputation"

# Set names of local files for input and output.
#  Input path is on HDFS
#  Output will be copied back from HDFS
INPUT_FILE=/Public/data/tiny_graph.txt
OUTPUT_DIR=shortestpaths

# Create HDFS directory path same as current directory
hadoop fs -mkdir -p "$PWD"

# Remove any old copies of output directory on HDFS and Linux FS
hadoop fs -rm -f -r "$PWD/$OUTPUT_DIR"
rm -rf "./$OUTPUT_DIR"

# Run Giraph program in Hadoop
#   -vip vertex input location (HDFS)
#   -vif vertex input format
#   -vof vertex output format
#   -op  output location (HDFS)
#   -w   number of workers
giraph "$JAR_FILE" \
  "$RUN_CLASS" \
  -vif org.apache.giraph.io.formats.JsonLongDoubleFloatDoubleVertexInputFormat \
  -vip "$INPUT_FILE" \
  -vof org.apache.giraph.io.formats.IdWithValueTextOutputFormat \
  -op "$PWD/$OUTPUT_DIR" \
  -w 1 \
  2>&1 | tee run_giraph.log

if [ "${PIPESTATUS[0]}" -eq 0 ] ; then
  echo "Copying output from $PWD/$OUTPUT_DIR to local $OUTPUT_DIR"
  hadoop fs -get "$PWD/$OUTPUT_DIR" .
fi
