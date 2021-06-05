//
// Created by Dmytro on 16.05.2021
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int summarily[1000000];

int find(int x) {
    return summarily[x] == x ? x : summarily[x] = find(summarily[x]);
}

vector<int> readData() {
    ifstream file(R"(C:\Users\homen\CLionProjects\C++\input.txt)");
    string str;
    vector<int> input;
    while (std::getline(file, str)) {
        input.push_back(stoi(str));
    }
    return input;
}

int combinedSearch(vector<int> in) {
    int n, sum = 0;
    int dataX, dataY;
    n = in.front();
    for (int i = 1; i <= n; i++)
        summarily[i] = i;
    for (int i = 1; i <= n; i++) {
        dataX = find(in[i]);
        dataY = find(i);
        summarily[dataY] = dataX;
    }
    for (int i = 1; i <= n; i++)
        if (summarily[i] == i)
            sum++;
    return sum;
}

void output() {
    cout << "Minimalnie trzeba stłuc " << combinedSearch(readData()) << endl;
}

int main() {
    output();
}
