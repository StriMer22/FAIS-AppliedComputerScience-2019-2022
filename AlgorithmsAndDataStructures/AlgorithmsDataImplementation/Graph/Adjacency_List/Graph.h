#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <list>

using namespace std;

class Graph {
    list<list<int>> vertexList;
    int numberOfEdges;

    bool checkVertex(int idx);

public:
    Graph();

    void createVertices(int ile);

    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);

    void removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);

    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);

    int vertexDegree(int idx);

    list<int> getNeighbourIndices(int idx);

    void printNeighbourIndices(int idx);

    int getNumberOfEdges();

    void readFromFile(std::string path);
};

