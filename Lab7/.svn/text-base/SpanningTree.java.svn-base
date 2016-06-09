// SpanningTree - find spanning tree of connected, undirected graph

import java.io.IOException;
import java.util.Iterator;
import org.apache.giraph.graph.BasicComputation;
import org.apache.giraph.conf.StrConfOption;
import org.apache.giraph.edge.Edge;
import org.apache.giraph.graph.Vertex;
import org.apache.hadoop.io.BooleanWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.log4j.Logger;

public class SpanningTree
    extends BasicComputation<Text, BooleanWritable, NullWritable, Text> {

    /** The root node to use for the spanning tree */
    public static final StrConfOption SOURCE_ID =
        new StrConfOption("SpanningTree.root", "",
                          "Root node of spanning tree");
    /** Class logger */
    private static final Logger LOG =
        Logger.getLogger(SpanningTree.class);

    /**
     * Is this vertex the source id?
     *
     * @param vertex Vertex
     * @return True if the root id
     */
    private boolean isRoot(Vertex<Text, ?, ?> vertex) {
        String rootId = SOURCE_ID.get(getConf());
        if (rootId.length() == 0) {
            LOG.fatal("SpanningTree.root not specified");
        }
        return 0 == vertex.getId().toString().compareTo(rootId);
    }
    BooleanWritable value;
    @Override
    public void compute(Vertex<Text, BooleanWritable, NullWritable> vertex,
                        Iterable<Text> messages) throws IOException {
    // Add your Spanning Tree implementation here
    if (getSuperstep() == 0) {
      if(isRoot(vertex))
      {     
	value.set(true);
      	vertex.setValue(value);
        for (Edge<Text, NullWritable> edge : vertex.getEdges()) 
	{
		sendMessage(edge.getTargetVertexId(), vertex.getId());
	}
	vertex.voteToHalt();
      }
      else
      {
	value.set(false);
	vertex.setValue(value);
	vertex.voteToHalt();
      }
    }
    else{
 	if(vertex.getValue().get() == false)
	{
         boolean First = true;
	 Iterator<Text> check = messages.iterator(); 
	  if(check.hasNext())
	  {
	    value.set(true);
	    vertex.setValue(value);
	    for (Text message : messages) 
            {
	     removeEdgesRequest(vertex.getId(), message);
             if(!First) 
             {
	       sendMessage(message, vertex.getId());
             }
             else
             {
	      First = false;
             }   
            }
	    for(Edge<Text, NullWritable> edge : vertex.getEdges())
 	    {
		sendMessage(edge.getTargetVertexId(), vertex.getId());
	    } 
	  }
	  else
          {
           //do nothing
          }
        }
        else
	{
	 for(Text message : messages)
	 {
	  for(Edge<Text, NullWritable> edge : vertex.getEdges())
	  {
	   if(message == edge.getTargetVertexId())
	   {
	    sendMessage(message, vertex.getId());
	    removeEdgesRequest(vertex.getId(),message);
	   }
          } 
	 }
	

      vertex.voteToHalt();
    }
  }
}
