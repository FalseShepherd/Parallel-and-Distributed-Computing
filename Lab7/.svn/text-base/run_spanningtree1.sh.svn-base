#!/bin/bash

# Set names of jar file and class to run
JAR_FILE="SpanningTree.jar"
RUN_CLASS="SpanningTree"

# Set names of local files for input and output.
#  Input path is on HDFS
#  Output will be copied back from HDFS
INPUT_FILE=/Public/data/Lab7Graph1.txt
OUTPUT_DIR=spanningtree1

# Create HDFS directory path same as current directory
hadoop fs -mkdir -p "$PWD"

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
  -eip "$INPUT_FILE" \
  -eof org.apache.giraph.io.formats.SrcIdDstIdEdgeValueTextOutputFormat \
  -op "$PWD/$OUTPUT_DIR" \
  -ca SpanningTree.root="e" \
  -w 1 \
  2>&1 | tee $0.log

# Copy result from HDFS
if [ "${PIPESTATUS[0]}" -eq 0 ] ; then
  echo "Copying output directory $OUTPUT_DIR"
  hadoop fs -get "$PWD/$OUTPUT_DIR" .
fi
