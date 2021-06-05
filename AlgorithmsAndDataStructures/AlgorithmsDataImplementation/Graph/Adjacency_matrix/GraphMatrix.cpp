#include "Graph.cpp"

void test1() {
    auto *G = new Graph();

    G->createVertices(10);
    cout << "number of edges: " << G->getNumberOfEdges() << endl;
    G->addEdge(1, 2);
    G->addEdge(2, 3);
    G->addEdge(1, 5);
    cout << "number of edges: " << G->getNumberOfEdges() << endl;
    cout << "vertex 1 degree: " << G->vertexDegree(1) << endl;
    cout << "vertex 2 degree: " << G->vertexDegree(2) << endl;
    cout << "vertex 8 degree: " << G->vertexDegree(8) << endl;
    G->printNeighbourIndices(1);
    list<int> lst = G->getNeighbourIndices(1);
    cout << "vertex 1 neighbour indices:" << endl;
    for (int &iter : lst) {
        cout << iter << endl;
    }
    G->printNeighbourIndices(2);
    cout << endl;
    cout << G->checkEdge(1, 2) << endl;
    G->removeEdge(1, 2);
    cout << G->checkEdge(1, 2) << endl;
    G->printNeighbourIndices(1);
    cout << "number of edges: " << G->getNumberOfEdges() << endl;
}

void test2() {
    auto *G = new Graph();
    G->readFromFile(R"(C:\Users\Dmytro\CLionProjects\Graphs\Adjacency_matrix\graph.txt)");
    cout << G->getNumberOfEdges() << endl;
    for (int i = 0; i < 20; ++i) {
        G->printNeighbourIndices(i);
    }
}

void test3() {
    auto *G = new Graph();

    G->readFromFile("nofile");
    G->createVertices(10);
    cout << "number of edges: " << G->getNumberOfEdges() << endl;
    G->addEdge(1, 2);
    G->addEdge(1, 2);
    G->addEdge(-1, 0);
    G->addEdge(1, 100);
    cout << "number of edges: " << G->getNumberOfEdges() << endl;
    cout << "vertex 1 degree: " << G->vertexDegree(1) << endl;
    G->removeEdge(5, 0);
    G->removeEdge(-1, 0);
    G->removeEdge(1, 100);
    cout << G->vertexDegree(100) << endl;
    list<int> lst = G->getNeighbourIndices(-1);
    cout << lst.empty() << endl;
    cout << G->checkEdge(-1, 0) << endl;
    cout << G->checkEdge(100, 0) << endl;
    G->printNeighbourIndices(-1);
    cout << "number of edges: " << G->getNumberOfEdges() << endl;
}

int main() {
    test1();
    std::cout << "\n\n";
    test2();
    std::cout << "\n\n";
    test3();
}
