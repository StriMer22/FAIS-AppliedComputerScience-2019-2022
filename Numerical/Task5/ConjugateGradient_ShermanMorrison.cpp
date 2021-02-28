#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <chrono>

using namespace std;
using vec = vector<double>;
const double NEARZERO = 1.0e-10;

vector<vec> genMatrix(int n) {
    vector <vec> matrix(n, vec(n));
    for (auto & i : matrix){
        for (double & j : i){
            j = 1;
        }
    }
    matrix[0][0] = 5;
    matrix[0][4] = 2;
    matrix[1][0] = 2;
    matrix[4][0] = 2;
    matrix[n-2][n-1] = 2;
    matrix[n-1][n-1] = 5;
    for(int i = 1; i < n-1; i++){
        matrix[i][i] = 5;
        matrix[i][i+4] = 2;
        matrix[i+1][i] = 2;
        matrix[i-1][i] = 2;
    }
    for (int i = 1; i < n-4; i++) {
        matrix[i+4][i] = 2;
    }
    matrix[n-1][0] = 1;
    matrix[0][n-1] = 1;
    return matrix;
}
vec genResults(int n){
    vec res(n,1.0);
    return res;
}
/** METODA GRADIENTÓW SPRZĘŻONYCH **/
// Iloczyn wewnętrzny U i V.
double innerProduct(const vec &U, const vec &V){
    return inner_product(U.begin(), U.end(), V.begin(), 0.0);
}
// Norma wektora
double vectorNorm(const vec &V){
    return sqrt(innerProduct(V, V));
}
vec matrixTimesVector(const vector<vec>& array, const vec &V){
    int n = array.size();
    vec C(n);
    for (int i = 0; i < n; i++)
        C[i] = innerProduct(array[i], V);
    return C;
}
// Liniowa kombinacja wektorów
vec vectorCombination(double a, const vec &U, double b, const vec &V){
    int n = U.size();
    vec W(n);
    for (int j = 0; j < n; j++)
        W[j] = a * U[j] + b * V[j];
    return W;
}

vec conjugateGradientSolver(const vector<vec>& array, const vec& arr ){
    double MARGIN = 1.0e-10;
    int n = array.size();
    vec X(n,0.0);
    vec R = arr;
    vec P = R;
    int k = 0;
    while (k < n){
        vec Rold = R;           // Przechowanie poprzednich pozostałości
        vec AP = matrixTimesVector(array,P);
        double alpha = innerProduct(R,R) / max(innerProduct(P,AP),NEARZERO);
        X = vectorCombination(1.0,X,alpha,P);            // Następne oszacowanie rozwiązania
        R = vectorCombination(1.0,R,-alpha,AP);          // Pozostała
        if (vectorNorm(R) < MARGIN)
            break;             // Test konwergencji
        double beta = innerProduct(R,R) / max(innerProduct(Rold,Rold),NEARZERO);
        P = vectorCombination(1.0,R,beta,P);             // Następny gradient
        k++;
    }
    return X;
}

vec ShermanMorrison(vector<vec>& one,vec& two){
    int n = one.size();
    vec u(n);
    vec v(n);
    double gammaU = 1;
    u[0] = gammaU;
    for (int i = 1; i < n; i++) {
        u[i] = 1.0;
    }
    for (int k = 0; k < n; k++) {
        v[k] = 1.0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
             one[i][j] -= 1.0;
        }
    }
    vec y = conjugateGradientSolver(one,two);
    vec z = conjugateGradientSolver(one,u);
    vec result(n);
    for (int i = 0; i < n; i++) {
        result[i] = y[i] - (innerProduct(v,y))/((1 + innerProduct(v,z))) * z[i] ;
    }
    return result;
}

void print(const vec &V){
    cout.precision(10);
    int n = V.size();
    cout << "Solution: \n";
    for (int i = 0; i < n; i++){
        double x = V[i];
        if (abs(x) < NEARZERO) x = 0.0;
        cout << "x" << i+1 << "-->" << x << "\n";
    }
    cout << '\n';
}

int main() {
    int i = 64;
        vector<vector<double>> array = genMatrix(i);
        vector<double> res0 = genResults(i);
    auto begin = std::chrono::steady_clock::now();
        print(ShermanMorrison(array,res0));
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
}

