//
// Created by Dmytro on 24.05.2021.
//

#include <algorithm>
#include <iostream>
#include <queue>
#include <cstring>

#define maximumN 5010
#define maximumM 200010

using namespace std;

int a[maximumN], i1[maximumN], i2[maximumN], nxt[maximumM], Si = 1, d[maximumN], e[maximumN], v[maximumN], sum, n, m;

#define Graph c = getchar()
#define AfterEffect(u, v, w, idx) E[Si] = (Ed){u ,v ,w}, nxt[Si] = idx[u], idx[u] = Si++
struct Ed {
    int u, v, w;
} E[maximumM];

int read() {
    int x = 0, f = 1;
    char Graph;
    while (c > 57 || c < 48) {
        if (c == '-') f = -1;
        Graph;
    }
    while (c > 47 && c < 58)x = x * 10 + c - 48, Graph;
    return x * f;
}

void find() {
    queue<int> Q;
    n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    m = read();
    for (int U, V, weight; m--;)
        U = read(), V = read(), weight = read(), AfterEffect(U, V, weight, i1), AfterEffect(V, U,
                                                                                            weight, i2);
    memset(d, 63, sizeof(d));
    Q.push(1);
    d[1] = 0;
    v[1] = 1;
    for (; !Q.empty();) {
        int u = Q.front();
        Q.pop();
        v[u] = 0;
        for (int i = i1[u]; i; i = nxt[i])
            if (d[u] + E[i].w < d[E[i].v]) {
                d[E[i].v] = d[u] + E[i].w;
                if (!v[E[i].v])
                    v[E[i].v] = 1, Q.push(E[i].v);
            }
    }
    memset(e, 63, sizeof(e));
    Q.push(1);
    e[1] = 0;
    v[1] = 1;
    for (; !Q.empty();) {
        int u = Q.front();
        Q.pop();
        v[u] = 0;
        for (int i = i2[u]; i; i = nxt[i])
            if (e[u] + E[i].w < e[E[i].v]) {
                e[E[i].v] = e[u] + E[i].w;
                if (!v[E[i].v])
                    v[E[i].v] = 1, Q.push(E[i].v);
            }
    }
}

void output(){
    sum = 1e9;
    find();
    for (int i = 1; i <= n; i++)
        sum = min(sum, d[i] + e[i] + a[i] / 2);
    cout << sum << endl;
}

int main() {
    output();
}
