#!/bin/bash

# Set names of jar file and class to run
JAR_FILE="P4Job1MR.jar"
RUN_CLASS="P4Job1MR"

# Set names of local files for input and output.
INPUT_FILES='/Public/data/Prog4PointsTest.csv'
OUTPUT_DIR=Job1TestOutput

# Remove any old copies of output directory on HDFS and Linux FS
hadoop fs -rm -f -r "$PWD/$OUTPUT_DIR"
rm -rf "./$OUTPUT_DIR"

# Create HDFS directory path same as current directory
hadoop fs -mkdir -p "$PWD"

# Run MapReduce
hadoop jar \
    "$JAR_FILE" \
    "$RUN_CLASS" \
    -Dmapreduce.job.reduces=1 \
    "$INPUT_FILES" \
    "$PWD/$OUTPUT_DIR" \
    2>&1 \
| tee $0.log

# Copy result from HDFS
if [ "${PIPESTATUS[0]}" -eq 0 ] ; then
  echo "Copying output directory $OUTPUT_DIR"
  hadoop fs -get "$PWD/$OUTPUT_DIR" .
fi
