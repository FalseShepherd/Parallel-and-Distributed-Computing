/*
 * Giraph undirected edge reader.
 *  Reads a file of edges, specified
 *  as vertex ID pairs.  Vertex IDs are any sequence of 
 *  non-whitespace characters, two per input line
 *  (specifying an edge between the vertices), separated
 *  by white space.  Creates edges in both directions
 *  between the two edges.
 *
 *  Specify the edge format using the Giraph parameter
 *    -eif UndirectedTextEdgeInputFormat
 *  Specify the edge input file (or directory) as
 *    -eip input_file
 *
 *  Author: Mike Goss (mikegoss@cs.du.edu), May 2014
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
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.InputSplit;
import org.apache.hadoop.mapreduce.TaskAttemptContext;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.util.regex.Pattern;

/**
 * Simple text-based for
 * unweighted graphs with Text ids.
 *
 * Each line consists of: vertex1 vertex2
 */
public class UndirectedTextEdgeInputFormat extends
    TextEdgeInputFormat<Text, NullWritable> {
  private static final Logger LOG =
      Logger.getLogger(UndirectedTextEdgeInputFormat.class);


  /** Splitter for endpoints */
  private static final Pattern SEPARATOR = Pattern.compile("\\s+");

  @Override
  public EdgeReader<Text, NullWritable> createEdgeReader(
      InputSplit split, TaskAttemptContext context) throws IOException {
    LOG.info("createEdgeReader called");
    return new ReverseEdgeDuplicator<Text,NullWritable>(new UndirectedTextEdgeInputReader());
  }

  public class StringPair {
      public String first, second;

      StringPair(String f, String s) {
    first = f;
    second = s;
      }
  }

  /*
   *  UndirectedTextEdgeInputReader - read undirected edges
   *    specified by pairs of vertex names, separated by
   *    whitespace.
   */
  public class UndirectedTextEdgeInputReader extends
      TextEdgeReaderFromEachLineProcessed<StringPair> {
    @Override
    protected StringPair preprocessLine(Text line) throws IOException {
      String[] tokens = SEPARATOR.split(line.toString());
      return new StringPair(tokens[0], tokens[1]);
    }

    @Override
    protected Text getSourceVertexId(StringPair endpoints)
      throws IOException {
      return new Text(endpoints.first);
    }

    @Override
    protected Text getTargetVertexId(StringPair endpoints)
      throws IOException {
      return new Text(endpoints.second);
    }

    @Override
    protected NullWritable getValue(StringPair endpoints) throws IOException {
      return NullWritable.get();
    }
  }
}
