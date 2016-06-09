#!/bin/bash

# Set names of files for input and output.
#  Input files are already on HDFS
#  Output directory will be copied back from HDFS
INPUT_FILES='hdfs:///Public/data/CompleteShakespeare.txt,/Public/data/WarAndPeace.txt'
OUTPUT_DIR='Job1Output'

# Create HDFS directory path same as current directory
hadoop fs -mkdir -p "$PWD"

# Remove any old copies of output directory on HDFS and Linux FS
hadoop fs -rm -f -r "$PWD/$OUTPUT_DIR"
rm -rf "./$OUTPUT_DIR"

# Run WordCount MapReduce
hadoop jar Job1.jar Job1 -Dmapreduce.job.reduces=2 "$INPUT_FILES" "$PWD/$OUTPUT_DIR"

# Copy result from HDFS
echo "Copying output from $OUTPUT_DIR"
hadoop fs -get "$PWD/$OUTPUT_DIR" .
