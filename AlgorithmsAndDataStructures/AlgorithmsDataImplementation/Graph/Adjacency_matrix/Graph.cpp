#include "Graph.h"

Graph::Graph() {
    numberOfEdges = 0;
}

void Graph::createVertices(int ile) {
    numberOfVertex = ile;
    matrix = new bool *[ile];
    for (int i = 0; i < ile; ++i) {
        matrix[i] = new bool[ile]();
    }
}

void Graph::addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (!checkVertex(i_Vertex_Index_1) || !checkVertex(i_Vertex_Index_2)) {
        cout << "wrong vertex index" << endl;
    } else if (checkEdge(i_Vertex_Index_1, i_Vertex_Index_2)) {
        cout << "edge (" << i_Vertex_Index_1 << ", " << i_Vertex_Index_2 << ") is already exists!" << endl;
    } else {
        matrix[i_Vertex_Index_1][i_Vertex_Index_2] = true;
        numberOfEdges++;
    }
}

void Graph::removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (!checkVertex(i_Vertex_Index_1) || !checkVertex(i_Vertex_Index_2)) {
        cout << "wrong vertex index" << endl;
    } else if (!checkEdge(i_Vertex_Index_1, i_Vertex_Index_2)) {
        cout << "edge (" << i_Vertex_Index_1 << ", " << i_Vertex_Index_2 << ") is not exist!" << endl;
    } else {
        matrix[i_Vertex_Index_1][i_Vertex_Index_2] = false;
        numberOfEdges--;
    }
}

bool Graph::checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (!checkVertex(i_Vertex_Index_1) || !checkVertex(i_Vertex_Index_2)) {
        cout << "wrong vertex index" << endl;
        return false;
    } else {
        return matrix[i_Vertex_Index_1][i_Vertex_Index_2];
    }
}

int Graph::vertexDegree(int idx) {
    if (!checkVertex(idx)) {
        cout << "wrong vertex index" << endl;
        return -1;
    } else {
        int counter = 0;
        for (int i = 0; i < numberOfVertex; ++i) {
            if (matrix[idx][i]) {
                counter++;
            }
        }
        return counter;
    }
}

list<int> Graph::getNeighbourIndices(int idx) {
    if (!checkVertex(idx)) {
        cout << "wrong vertex index" << endl;
        return list<int>();
    } else {
        list<int> lst;
        for (int i = 0; i < numberOfVertex; ++i) {
            if (matrix[idx][i]) {
                lst.push_back(i);
            }
        }
        return lst;
    }
}

void Graph::printNeighbourIndices(int idx) {
    if (!checkVertex(idx)) {
        cout << "wrong vertex index" << endl;
    } else {
        cout << "vertex " << idx << " neighbour indices: " << endl;
        for (int i = 0; i < numberOfVertex; ++i) {
            if (matrix[idx][i]) {
                cout << i << endl;
            }
        }
    }
}

int Graph::getNumberOfEdges() {
    return numberOfEdges;
}

void Graph::readFromFile(string path) {
    ifstream input;
    input.open(path);
    if (!input.good()) {
        cout << "can't open file " + path << endl;
    } else {
        int vertexAmount, a, b;
        input >> vertexAmount;
        createVertices(vertexAmount);
        input >> a;
        while (!input.eof()) {
            input >> b;
            addEdge(a, b);
            input >> a;
        }
    }
}

bool Graph::checkVertex(int idx) {
    return (idx < numberOfVertex && idx >= 0);
}
