import java.io.IOException;
 
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class PointMapper extends Mapper<Object, Text, Text, Text> {

  private Text newKey = new Text();

  final private float cellSize = 5.0f;
  
  @Override
    public void map(Object key, Text value,
                    Context context) throws IOException, InterruptedException {
    // Break line into tokens for processing
    String[] tokens = value.toString().split(",");

    // Parse coordinates and compute cell number
    float x = Float.parseFloat(tokens[1]);
    int xCell = (int) Math.floor(x / cellSize);
    float y = Float.parseFloat(tokens[2]);
    int yCell = (int) Math.floor(y / cellSize);

    // Map into cell, cell to immediate right,
    // and 3 adjacent cells in row below
    newKey.set(xCell + "," + yCell);
    context.write(newKey, value);
    newKey.set((xCell+1) + "," + yCell);
    context.write(newKey, value);
    newKey.set((xCell-1) + "," + (yCell+1));
    context.write(newKey, value);
    newKey.set(xCell + "," + (yCell+1));
    context.write(newKey, value);
    newKey.set((xCell+1) + "," + (yCell+1));
    context.write(newKey, value);
  }
}
