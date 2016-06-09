#!/bin/bash

# Run hadoop WordIndex example

# Set names of files for input and output.
#  Input file is already on HDFS
#  Output directory will be copied back from HDFS
INPUT_FILE='hdfs:///Public/data/GibbonVol?.txt'
OUTPUT_DIR=word_index

# Create HDFS directory path same as current directory
hadoop fs -mkdir -p "hdfs://$PWD"

# Remove any old copies of output directory on HDFS and Linux FS
hadoop fs -rm -f -r "hdfs://$PWD/$OUTPUT_DIR"
rm -rf "./$OUTPUT_DIR"

# Run WordIndex MapReduce
hadoop jar WordIndex.jar WordIndex -Dmapreduce.job.reduces=6 "$INPUT_FILE" $PWD/$OUTPUT_DIR

# Copy result from HDFS
echo '*********************************************'
echo "  Copying output from $OUTPUT_DIR"
echo '*********************************************'
hadoop fs -get $PWD/$OUTPUT_DIR .
