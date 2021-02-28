#include <iostream>
#include <chrono>

using namespace std;

/**
 * n - liczba równań (wiersze macierzy)
 * b - przekątna nad główną (ponumerowana: [0; n-2])
 * c - główna przekątna macierzy (ponumerowana: [0; n-1])
 * a - przekątna poniżej głównej (ponumerowana: [1; n-1])
 * f - prawa strona (kolumna(wyniki))
 * x - rozwiązanie, tablica X będzie zawierać odpowiedź
 */

void solveMatrix (int n, const double *a, double *c, const double *b, double *f, double *x){
    /* Forward substitution */
    double m;
    /* Modify coefficients */
    for (int i = 1; i < n; i++){
        m = a[i]/c[i-1];
        c[i] = c[i] - m*b[i-1];
        f[i] = f[i] - m*f[i-1];
    }

    /* back substitute */
    x[n-1] = f[n-1]/c[n-1];
    for (int i = n - 2; i >= 0; i--)
        x[i]=(f[i]-b[i]*x[i+1])/c[i];
}

int main(){
    int n = 7;
    double lower[] = {1, 1, 1, 1, 1 ,1 ,1};
    double diagonal[] = {4, 4, 4, 4, 4, 4, 4};
    double upper[] = {1, 1, 1, 1, 1, 1, 1};
    double rhs[] = {1, 2, 3, 4, 5, 6, 7};
    double X[n];
    cout.precision(16);
    auto start = chrono::high_resolution_clock::now();
    solveMatrix(n,upper,diagonal,lower,rhs,X);
    auto finish = chrono::high_resolution_clock::now();
    int counter = 1;
    for (double i : X){
        cout << "x" << counter << " --> " << i << endl;
        counter++;
    }
    cout << "\n" << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << "ns\n";
}