/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  vector<Vertex> vertices = g_.getVertices();

  for(auto itr = vertices.begin(); itr != vertices.end(); itr++) {
    flow_.insertVertex(*itr);
    residual_.insertVertex(*itr);
  }

  vector<Edge> edges = g_.getEdges();
  for (auto itr =  edges.begin(); itr != edges.end(); itr++) {
    flow_.insertEdge(itr->source, itr->dest);
    flow_.setEdgeWeight(itr->source, itr->dest, 0);

    residual_.insertEdge(itr->source, itr->dest);
    residual_.setEdgeWeight(itr->source, itr->dest, itr->getWeight());
    residual_.insertEdge(itr->dest, itr->source);
    residual_.setEdgeWeight(itr->dest, itr->source, 0);
  }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int res = residual_.getEdgeWeight(path.at(0), path.at(1));
  for(size_t i = 1; i < path.size() - 1; i++) {
    res = std::min(residual_.getEdgeWeight(path.at(i), path.at(i+1)), res);
  }
  return res;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  vector<Vertex> vertices;
  while(findAugmentingPath(source_, sink_, vertices)) {
    int cap = pathCapacity(vertices);
    for (size_t i = 0; i < vertices.size() - 1; i++) {
      Vertex s = vertices.at(i);
      Vertex d = vertices.at(i+1);

      if (! flow_.edgeExists(s, d)) {
        flow_.setEdgeWeight(d, s, flow_.getEdgeWeight(d, s) - cap);
      } else {
        flow_.setEdgeWeight(s, d, flow_.getEdgeWeight(s, d) + cap);
      }

      residual_.setEdgeWeight(d, s, residual_.getEdgeWeight(d, s) + cap);
      residual_.setEdgeWeight(s, d, residual_.getEdgeWeight(s, d) - cap);

    }
  }

  int maxVal = 0;
  vector<Vertex> adjacents = flow_.getAdjacent(source_);
  for (auto itr = adjacents.begin(); itr != adjacents.end(); itr++) {
    maxVal += flow_.getEdgeWeight(source_, *itr);
  }
  maxFlow_ = maxVal;
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
