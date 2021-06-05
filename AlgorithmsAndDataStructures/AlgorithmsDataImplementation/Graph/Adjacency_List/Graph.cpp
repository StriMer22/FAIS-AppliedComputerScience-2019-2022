#include "Graph.h"

Graph::Graph() {
    numberOfEdges = 0;
}

void Graph::createVertices(int ile) {
    for (int i = 0; i < ile; ++i) {
        list<int> vertex;
        vertexList.push_back(vertex);
    }
}

void Graph::addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (!checkVertex(i_Vertex_Index_1) || !checkVertex(i_Vertex_Index_2)) {
        cout << "wrong vertex index" << endl;
    } else if (checkEdge(i_Vertex_Index_1, i_Vertex_Index_2)) {
        cout << "edge (" << i_Vertex_Index_1 << ", " << i_Vertex_Index_2 << ") is already exists!" << endl;
    } else {
        auto iter = vertexList.begin();
        advance(iter, i_Vertex_Index_1);
        (*iter).push_back(i_Vertex_Index_2);
        numberOfEdges++;
    }
}

void Graph::removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (!checkVertex(i_Vertex_Index_1) || !checkVertex(i_Vertex_Index_2)) {
        cout << "wrong vertex index" << endl;
    } else if (!checkEdge(i_Vertex_Index_1, i_Vertex_Index_2)) {
        cout << "edge (" << i_Vertex_Index_1 << ", " << i_Vertex_Index_2 << ") is not exist!" << endl;
    } else {
        auto iter = vertexList.begin();
        advance(iter, i_Vertex_Index_1);
        (*iter).remove(i_Vertex_Index_2);
        numberOfEdges--;
    }
}

bool Graph::checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2) {
    if (!checkVertex(i_Vertex_Index_1) || !checkVertex(i_Vertex_Index_2)) {
        cout << "wrong vertex index" << endl;
        return false;
    } else {
        auto iter = vertexList.begin();
        advance(iter, i_Vertex_Index_1);
        auto iter2 = iter->begin();
        for (; iter2 != iter->end() && (*iter2) != i_Vertex_Index_2; ++iter2);
        return iter2 != iter->end();
    }
}

int Graph::vertexDegree(int idx) {
    if (!checkVertex(idx)) {
        cout << "wrong vertex index" << endl;
        return -1;
    } else {
        int counter = 0;
        auto iter = vertexList.begin();
        advance(iter, idx);
        auto iter2 = iter->begin();
        for (; iter2 != iter->end(); ++iter2) {
            counter++;
        }
        return counter;
    }
}

list<int> Graph::getNeighbourIndices(int idx) {
    if (!checkVertex(idx)) {
        cout << "wrong vertex index" << endl;
        return list<int>();
    } else {
        auto iter = vertexList.begin();
        advance(iter, idx);

        return *iter;
    }
}

void Graph::printNeighbourIndices(int idx) {
    if (!checkVertex(idx)) {
        cout << "wrong vertex index" << endl;
    } else {
        auto iter = vertexList.begin();
        advance(iter, idx);

        cout << "vertex " << idx << " neighbour indexes: " << endl;
        auto iter2 = iter->begin();
        for (; iter2 != iter->end(); ++iter2) {
            cout << *iter2 << endl;
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
    return (idx < vertexList.size() && idx >= 0);
}
