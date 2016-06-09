/**
 * VertexDistanceWritable - define a class which stores a Text vertex ID along with
 *   a FloatWritable distance value.
 *
 */

import java.io.IOException;
import java.io.DataInput;
import java.io.DataOutput;
import org.apache.hadoop.io.FloatWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.Writable;


public class VertexDistanceWritable implements Writable {

  private Text id;                 // vertex id
  private FloatWritable distance;  // vertex distance

  // Default constructor
  public VertexDistanceWritable() {
    id = new Text();
    distance = new FloatWritable();
  }

  // Constructor with full specification
  public VertexDistanceWritable(String n, float d) {
    id = new Text(n);
    distance = new FloatWritable(d);
  }

  // Copy constructor (creates distinct objects from original)
  public VertexDistanceWritable(final VertexDistanceWritable other) {
    id = new Text(other.id);
    distance = new FloatWritable(other.distance.get());
  }

  // Write serialized version of this object
  public void write(DataOutput out) throws IOException {
    id.write(out);
    distance.write(out);
  }

  // Read serialized version of this object
  public void readFields(DataInput in) throws IOException {
    id.readFields(in);
    distance.readFields(in);
  }

  // Create new object from serial data input stream
  public static VertexDistanceWritable read(DataInput in) throws IOException {
    VertexDistanceWritable vdw = new VertexDistanceWritable();
    vdw.readFields(in);
    return vdw;
  }

  // Methods to set fields
  public void setId(String s) {
    id.set(s);
  }

  public void setDistance(float d) {
    distance.set(d);
  }

  // Methods to get fields
  public Text getIdText() {
    return id;
  }

  public String getId() {
    return id.toString();
  }

  public float getDistance() {
    return distance.get();
  }

  // Method to write as String
  @Override
    public String toString() {
    return "{" + id.toString() + "," + distance.get() +"}";
  }
}
