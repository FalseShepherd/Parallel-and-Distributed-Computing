/**
 *  SMapWritable - MapWritable extended with toString method
 *
 *  See https://hadoop.apache.org/docs/r2.6.2/api/org/apache/hadoop/io/MapWritable.html
 *  for documentation on MapWritable.
 */

import java.util.Arrays;
import java.util.Map;
import java.util.Set;

import org.apache.hadoop.io.MapWritable;
import org.apache.hadoop.io.Writable;

public class SMapWritable extends MapWritable {

  public SMapWritable() {}

  /**
   * toString - write out entries, sorted by key
   */
  @Override
    public String toString() {

    // Get array of entries
    Set<Map.Entry<Writable,Writable>> entries = entrySet();;

    String[] entryStrings = new String[entries.size()];
    int next = 0;
    for (Map.Entry<Writable,Writable> entry : entries) {
      entryStrings[next++] = entry.getKey().toString() + "=" + entry.getValue().toString();
    }
    Arrays.sort(entryStrings);

    return Arrays.toString(entryStrings);
  }
}
