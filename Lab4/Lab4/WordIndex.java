// WordIndex - use Map Reduce to index a set of text files
//
// COMP3705/4705 Spring 2016 Lab 4

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

public class WordIndex extends Configured implements Tool {

  /*
   * main parses the arguments that are Hadoop specific (like -D)
   *   and then passes the rest of the arguments to the run() method.
   */
  public static void main(String[] args) throws Exception {
    int res = ToolRunner.run(new Configuration(),
                             new WordIndex(),
                             args);
    System.exit(res);
  }

  /*
   *  Run the Map Reduce
   *    args[0] is the input path (may be a wildcard)
   *    args[1] is the output directory
   */
  @Override
    public int run(String[] args) throws Exception {
    if (args.length != 2) {
      System.out.println("usage: [input] [output]");
      System.exit(-1);
    }

    Job job = Job.getInstance(getConf(), "WordIndexJob");
    job.setJarByClass(WordIndex.class);  // Main class for MapReduce
    job.setOutputKeyClass(Text.class);   // type of the mapper output key
    job.setOutputValueClass(LongWritable.class); // type of the mapper output value
 
    job.setMapperClass(WordMapper.class);  // class to use for Map
    job.setReducerClass(IndexReducer.class); // class to use for Reduce
 
    job.setInputFormatClass(TextInputFormat.class);    // format to read input
    job.setOutputFormatClass(TextOutputFormat.class);  // format to write output
 
    FileInputFormat.setInputPaths(job, new Path(args[0]));   // path(s) of input
    FileOutputFormat.setOutputPath(job, new Path(args[1]));  // directory of output
 
    return job.waitForCompletion(true) ? 0 : 1;  // run the Map Reduce and return the status
  }
}
