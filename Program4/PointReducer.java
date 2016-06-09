import java.io.IOException;
import java.lang.Thread;
import java.util.Map;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
 
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;
 
public class PointReducer extends Reducer<Text, Text, Text, Float> {

  final private float cellSize = 5.0f;
  final private float cellSizeSq = cellSize * cellSize;

  Text outKey = new Text();
  float outValue;

  int cellX, cellY;

  @Override
    public void reduce(Text key, Iterable<Text> values, Context context)
    throws IOException, InterruptedException {

    // Get cell number of this key
    String[] keyStrings = key.toString().split(",");
    cellX = Integer.parseInt(keyStrings[0]);
    cellY = Integer.parseInt(keyStrings[1]);

    // Storage for point information
    ArrayList<String> pointId = new ArrayList<>();
    ArrayList<Float> pointX = new ArrayList<>();
    ArrayList<Float> pointY = new ArrayList<>();
    ArrayList<Boolean> inCell = new ArrayList<>();  // true if in this key's cell

    // Read in all the points with this key
    Iterator<Text> it=values.iterator();
    while (it.hasNext()) {
      // Parse input line for ID and coordinates
      String[] tokens = it.next().toString().split(",");
      pointId.add(tokens[0]);
      float x = Float.parseFloat(tokens[1]);
      pointX.add(x);
      float y = Float.parseFloat(tokens[2]);
      pointY.add(y);

      // Note if vertex is in this cell
      inCell.add(InCell(x, y));
    }

    // Find all points within distance cellSize of each point
    for (int i = 0; i < pointId.size()-1; ++i) {
      float x1 = pointX.get(i);
      float y1 = pointY.get(i);
      for (int j = i+1; j < pointId.size(); ++j) {
        // If one or both points in this key's cell
        if (inCell.get(i) || inCell.get(j)) {
          float x2 = pointX.get(j);
          float y2 = pointY.get(j);
          float dX = x1 - x2;
          float dY = y1 - y2;
          // If distance between points <= cellSize
          if (dX*dX + dY*dY <= cellSizeSq) {
            // Output point pair - lesser ID as key, greater ID as value
            if (pointId.get(i).compareTo(pointId.get(j)) < 0) {
              outKey.set(pointId.get(i)+ " " + pointId.get(j));
              outValue = (float) Math.sqrt(dX*dX + dY*dY);
            } else {
              outKey.set(pointId.get(j)+ " " + pointId.get(i));
	      outValue = (float) Math.sqrt(dX*dX + dY*dY);
              }
            context.write(outKey, outValue);
          }
        }
      }
    }
  }


  // Function to determine if x, y coordinates are with our cell
  private boolean InCell(float x, float y) {
    int inX = (int) Math.floor(x / cellSize);
    int inY = (int) Math.floor(y / cellSize);
    return inX == cellX && inY == cellY;
  }
}
