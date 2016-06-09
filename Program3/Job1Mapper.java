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

public class Job1Mapper extends Mapper<LongWritable, Text, Text, Text> {
  private Text word1 = new Text();
  private Text word2 = new Text();

  @Override
    public void map(LongWritable key, Text value,
                    Context contex) throws IOException, InterruptedException {
    // Break line into words for processing
    StringTokenizer wordList = new StringTokenizer(value.toString(), " ~`!@#$%^&*()_-+={}[]|\\:;\"'<>,.?/");
    if(wordList.hasMoreTokens())
    {
    word2.set(wordList.nextToken());
    }
    while (wordList.hasMoreTokens()) {
      word1.set(word2);
      word2.set(wordList.nextToken());
      contex.write(word1,word2);
    }
  }
}
