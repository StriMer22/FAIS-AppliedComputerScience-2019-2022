#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;
using vec = vector<double>;
const double NEARZERO = 1.0e-10;

vector<vec> genMatrix(int n) {
    vector <vec> matrix(n, vec(n));

    matrix[0][0] = 4;
    matrix[0][4] = 1;
    matrix[1][0] = 1;
    matrix[4][0] = 1;
    matrix[n-2][n-1] = 1;
    matrix[n-1][n-1] = 4;
    for(int i = 1; i < n-1; i++){
        matrix[i][i] = 4;
        matrix[i][i+4] = 1;
        matrix[i+1][i] = 1;
        matrix[i-1][i] = 1;
    }
    for (int i = 1; i < n-4; i++) {
        matrix[i+4][i] = 1;
    }
    matrix[n-1][0] = 0;
    matrix[0][n-1] = 0;
    return matrix;
}

vec genResults(int n){
    vec res(n);
    for(int i = 0; i < n; i++){
        res[i] = 1;
    }
    return res;
}

/** METODA GUASSA-SEIDELA **/

void gaussSeidelElimination(vector<vec> array, vec arr, int n) {
    int p = 0;
    cout.precision(10);
    vec result(n, 0.0);
    vec T(n, 0.0); vec F(n, 0.0);
    double k = 1e10;
    while (k >= 0.000001){
        p = p + 1;
        for (int i = 0; i < n; i++){
            double B = 0;
            T[i] = arr[i]/array[i][i];
            double C = array[i][i];
            for (int j = 0; j < n; j++){
                if (j!=i)
                    B += array[i][j] * result[j];
            }
            result[i] = T[i]-B/C;
        }
        for (int i = 0; i < n; i++){
            F[i] = 0.0;
            for (int j = 0; j < n; j++){
                F[i] = F[i] + array[i][j]*result[j];
            }
        }
        for (int i = 0; i < n; i++){
            F[i] = F[i]-arr[i];
        }
        k = 0.0;
        for (int i = 0;i < n;i++){
            k += F[i] * F[i];
        }
        k = sqrt(k);
    }
    cout << "Solution :\n";
    for (int i = 0; i < n; i++){
        cout << "x" << i+1 << "-->" << result[i] << "\n";
    }
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

void printMatrix(const vector<vector<double>>& tab, const vector<double>& res, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%.1f ", tab[i][j]);
        }
        printf("| %.1f", res[i]);
        printf("\n");
    }
}

int main() {
    int i = 128;
        vector<vector<double>> array = genMatrix(i);
        vector<double> res0 = genResults(i);
        printMatrix(array, res0, i);
        vec X = conjugateGradientSolver( array, res0 );
        cout << "ConjugateGradient: \n";
        print(X);
        cout << "GaussSeidel: \n";
        gaussSeidelElimination(array,res0, i);
}

