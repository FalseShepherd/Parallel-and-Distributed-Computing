/**
 * VertexDistanceArrayWritable - define an array of VertexDistanceWritable objects
 *   which can be send in a Giraph message
 *
 * See https://hadoop.apache.org/docs/r2.6.2/api/org/apache/hadoop/io/ArrayWritable.html
 * for documentation on ArrayWritable.
 */

import org.apache.hadoop.io.ArrayWritable;

// ArrayWritable containing VertexDistanceWritable objects
public class VertexDistanceArrayWritable extends ArrayWritable {

  public VertexDistanceArrayWritable() {
    super(VertexDistanceWritable.class);
  }

  public VertexDistanceArrayWritable(VertexDistanceWritable[] v) {
    super(VertexDistanceWritable.class, v);
  }
}
