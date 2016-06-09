/*
 *  WordMapper maps each word with a value string composed of
 *    the file number from input, a dash, and the position
 *    of the word in the input file as specified by the key.
 */

import java.io.IOException;
import java.util.StringTokenizer;
 
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class WordMapper extends Mapper<LongWritable, Text, Text, LongWritable> {
  private Text word = new Text();
  
  @Override
    public void map(LongWritable key, Text value,
                    Context contex) throws IOException, InterruptedException {
    // Break line into words for processing
    StringTokenizer wordList = new StringTokenizer(value.toString(), " ~`!@#$%^&*()_-+={}[]|\\:;\"'<>,.?/");
    while (wordList.hasMoreTokens()) {
      word.set(wordList.nextToken());
      contex.write(word, key);
    }
  }
}
