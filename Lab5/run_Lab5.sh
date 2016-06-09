#!/bin/bash

# Run hadoop Lab5

# Set names of files for input and output.
#  Input file is already on HDFS
#  Output directory will be copied back from HDFS
INPUT_FILE='hdfs:///Public/data/Lab5Points.csv'
OUTPUT_DIR=points

# Create HDFS directory path same as current directory
hadoop fs -mkdir -p "hdfs://$PWD"

# Remove any old copies of output directory on HDFS and Linux FS
hadoop fs -rm -f -r "hdfs://$PWD/$OUTPUT_DIR"
rm -rf "./$OUTPUT_DIR"

# Run MapReduce
hadoop jar Lab5.jar Lab5 -Dmapreduce.job.reduces=2 "$INPUT_FILE" $PWD/$OUTPUT_DIR

# Copy result from HDFS
echo "Copying output from $OUTPUT_DIR"
hadoop fs -get $PWD/$OUTPUT_DIR .
