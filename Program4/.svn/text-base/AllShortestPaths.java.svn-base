/*
 * Find all shortest paths between vertices
 *
 */

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

import org.apache.giraph.graph.BasicComputation;
import org.apache.giraph.edge.Edge;
import org.apache.giraph.graph.Vertex;
import org.apache.hadoop.io.ArrayWritable;
import org.apache.hadoop.io.FloatWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.Writable;
import org.apache.log4j.Logger;

// TODO: your code here
public class AllShortestPaths extends BasicComputation<
Text, SMapWritable, FloatWritable, VertexDistanceArrayWritable> {
	final FloatWritable DTSelf = new FloatWritable(0); 



@Override
public void compute(Vertex<Text, SMapWritable, FloatWritable> vertex, Iterable<VertexDistanceArrayWritable> messages) 
throws IOException {
	if (getSuperstep() == 0) {
		vertex.setValue(new SMapWritable());
		vertex.getValue().put(vertex.getId(), new FloatWritable(0));

		VertexDistanceWritable[] mArr = new VertexDistanceWritable[1];
		for (Edge<Text, FloatWritable> e : vertex.getEdges()) {
			mArr[0] = new VertexDistanceWritable(vertex.getId().toString(), e.getValue().get());
			VertexDistanceArrayWritable mOut = new VertexDistanceArrayWritable(mArr);
			sendMessage(new Text(e.getTargetVertexId()), mOut);
		}
		vertex.voteToHalt();
		return;
	}

	ArrayList<VertexDistanceWritable> outList = new ArrayList<VertexDistanceWritable>();
	for (VertexDistanceArrayWritable message : messages) {
		VertexDistanceWritable[] mArray = (VertexDistanceWritable[]) message.toArray();
		for (VertexDistanceWritable v : mArray) {
			if (vertex.getValue().containsKey(v.getIdText())) {
				if (v.getDistance() < ((FloatWritable) vertex.getValue().get(v.getIdText())).get()) {
					vertex.getValue().put(v.getIdText(), new FloatWritable(v.getDistance()));
					outList.add(new VertexDistanceWritable(v.getId(), v.getDistance()));
				}
			}
			else {
				vertex.getValue().put(v.getIdText(), new FloatWritable(v.getDistance()));
				outList.add(new VertexDistanceWritable(v.getId(), v.getDistance()));
			}
		}
	}
	if (outList.size() > 0) {
		for (Edge<Text, FloatWritable> e : vertex.getEdges()) {
			VertexDistanceWritable[] tempArr = new VertexDistanceWritable[outList.size()];
			for (int i = 0; i < outList.size(); i++) {
				tempArr[i] = new VertexDistanceWritable(outList.get(i).getId(), outList.get(i).getDistance() + e.getValue().get());
			}
			VertexDistanceArrayWritable mOut = new VertexDistanceArrayWritable(tempArr);
			sendMessage(new Text(e.getTargetVertexId()), mOut);
		}
	}

	vertex.voteToHalt();
}
}

