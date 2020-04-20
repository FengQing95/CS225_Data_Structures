#include <iostream>
#include <string>
#include "adjacency_list.h"

using namespace std;

bool containsEdge(Graph const * const g, int src, int dest) {
        // Your code here
        if (src >= g->n || dest >= g->n) {
            return false;
        }

        AdjacencyList & curNode = g->adjLists[src];
        LinkedListNode * nextNode = curNode.edges;
        while(nextNode) {
            if (nextNode->v == dest) {
                return true;
            } else {
                nextNode = nextNode->next;
            }
        }
        return false;

}

void addEdge(Graph* g, int src, int dest) {
        // Your code here
        if (containsEdge(g, src, dest)) {
            return;
        } else {
            AdjacencyList & curNode = g->adjLists[src];
            LinkedListNode * tem = curNode.edges;
            curNode.edges = new LinkedListNode();
            curNode.edges->v = dest;
            curNode.edges->next = tem;
        }
}

int numOutgoingEdges(Graph const * const g, int v) {
        // Your code here
        AdjacencyList & curNode = g->adjLists[v];
        LinkedListNode * nextNode = curNode.edges;
        int res = 0;
        while(nextNode) {
            res++;
            nextNode = nextNode->next;
        }
        return res;
}


int numIncomingEdges(Graph const * const g, int v) {
        // Your code here
        int res = 0;
        for (int i = 0; i < g->n; i++) {
            if (containsEdge(g, i, v)) {
                res++;
            }
        }
        return res;
}

// No need to modify the functions below

Graph* createVertices(int numV) {
        Graph* g = new Graph();
        g->adjLists = new AdjacencyList[numV];
        g->n = numV;

        // Initialize the vertices
        for (int i = 0; i < numV; i += 1) {
                g->adjLists[i].vertex = i;
                g->adjLists[i].edges = NULL;
        }

        return g;
}

void printGraph(Graph const * const g) {
    for (int i = 0; i < g->n; i += 1) {
        AdjacencyList adjList = g->adjLists[i];

        int v = adjList.vertex;
        // Vertex
        cout << "Vertex: " << v << endl;

        // Print number of incoming and outgoing edges
        int inc = numIncomingEdges(g, v);
        int out = numOutgoingEdges(g, v);
        cout << "Number of incoming edges: " << inc << endl;
        cout << "Number of outgoing edges: " << out << endl;

        cout << "\n" << endl;
    }
}
