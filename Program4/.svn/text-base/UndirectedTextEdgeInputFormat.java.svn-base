/*
 * Giraph undirected edge reader.
 *  Reads a file of edges, specified
 *  as vertex ID pairs and distance.  Vertex IDs are any sequence of 
 *  non-whitespace characters, two per input line
 *  (specifying an edge between the vertices), separated
 *  by white space, followed by a floating-point distance.
 *  Creates edges in both directions between the two edges.
 *
 *  Specify the edge format using the Giraph parameter
 *    -eif UndirectedTextEdgeInputFormat
 *  Specify the edge input file (or directory) as
 *    -eip input_file
 *
 *  Author: Mike Goss (mikegoss@cs.du.edu), May 2016
 *    (based on Giraph sample code)
 */

/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import org.apache.giraph.io.EdgeReader;
import org.apache.giraph.io.ReverseEdgeDuplicator;
import org.apache.giraph.io.formats.TextEdgeInputFormat;
import org.apache.hadoop.io.FloatWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.InputSplit;
import org.apache.hadoop.mapreduce.TaskAttemptContext;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.util.regex.Pattern;

/**
 * Simple text-based for
 * unweighted graphs with Text ids and distances
 *
 * Each line consists of: vertex1 vertex2 distance
 */
public class UndirectedTextEdgeInputFormat
  extends TextEdgeInputFormat<Text, FloatWritable> {

  private static final Logger LOG =
    Logger.getLogger(UndirectedTextEdgeInputFormat.class);

  /** Splitter for input line */
  private static final Pattern SEPARATOR = Pattern.compile("\\s+");

  @Override
    public EdgeReader<Text, FloatWritable> createEdgeReader(
      InputSplit split, TaskAttemptContext context) throws IOException {
    LOG.info("createEdgeReader called");
    return new ReverseEdgeDuplicator<Text,FloatWritable>(new UndirectedTextEdgeInputReader());
  }

  public class EdgeData {
    public String first, second;
    public float distance;

    EdgeData(String f, String s, String d) {
      first = f;
      second = s;
      distance = Float.parseFloat(d);
    }
  }

  /*
   *  UndirectedTextEdgeInputReader - read undirected edges
   *    specified by pairs of vertex names, separated by
   *    whitespace.
   */
  public class UndirectedTextEdgeInputReader extends
    TextEdgeReaderFromEachLineProcessed<EdgeData> {
    @Override
      protected EdgeData preprocessLine(Text line) throws IOException {
      String[] tokens = SEPARATOR.split(line.toString());
      return new EdgeData(tokens[0], tokens[1], tokens[2]);
    }

    @Override
      protected Text getSourceVertexId(EdgeData edge)
      throws IOException {
      return new Text(edge.first);
    }

    @Override
      protected Text getTargetVertexId(EdgeData edge)
      throws IOException {
      return new Text(edge.second);
    }

    @Override
      protected FloatWritable getValue(EdgeData edge) throws IOException {
      return new FloatWritable(edge.distance);
    }
  }
}
