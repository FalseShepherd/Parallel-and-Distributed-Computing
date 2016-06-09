#!/bin/bash

# Set names of files for input and output.
#  Input files are already on HDFS
#  Output directory will be copied back from HDFS
INPUT_DIR='Job1Output'
OUTPUT_DIR='Job2Output'

# Create HDFS directory path same as current directory
hadoop fs -mkdir -p "$PWD"

# Remove any old copies of output directory on HDFS and Linux FS
hadoop fs -rm -f -r "$PWD/$OUTPUT_DIR"
rm -rf "./$OUTPUT_DIR"

# Run WordCount MapReduce
hadoop jar Job2.jar Job2 -Dmapreduce.job.reduces=2 "$PWD/$INPUT_DIR" "$PWD/$OUTPUT_DIR"

# Copy result from HDFS
echo "Copying output from $OUTPUT_DIR"
hadoop fs -get "$PWD/$OUTPUT_DIR" .
