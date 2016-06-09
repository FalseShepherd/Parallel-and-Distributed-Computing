import java.io.IOException;
import java.util.Iterator;
import java.lang.StringBuilder;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;
 
public class Job2Reducer extends Reducer<Text, Text , Text, Text> { 
  /*
   *  reduce - write out all the values in a single line, preceded by the key.
   */
  @Override
    public void reduce(Text key,Iterable<Text>  value, Context context)
    throws IOException, InterruptedException {
    Iterator<Text> it = value.iterator();
    StringBuilder words = new StringBuilder();
    while (it.hasNext()) {
      // Collect index values here
      words.append(it.next().toString()+" ");
    }
    // Output key and space-separated index value list here
   Text wordsWritable= new Text(words.toString()); 
   context.write(key, wordsWritable);
  }
}
