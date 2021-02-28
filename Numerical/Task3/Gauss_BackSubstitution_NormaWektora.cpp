#include <iostream>
#include <cmath>

using namespace std;

double** Matrix() {
    double matrix[5][5]{
            { -116.66654, 583.33346 , -333.33308 , 100.00012 , 100.00012},
            { 583.33346 , -116.66654 , -333.33308, 100.00012 , 100.00012},
            { -333.33308, -333.33308 , 133.33383 , 200.00025 , 200.00025},
            { 100.00012 , 100.00012  , 200.00025 , 50.000125 , -649.99988},
            { 100.00012 , 100.00012 , 200.00025 , -649.99988 , 50.000125}};
    auto** retMatrix = new double*[5];
    for (int i = 0; i < 5; ++i) {
        retMatrix[i] = new double[5];
    }
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            retMatrix[i][j] = matrix[i][j];
        }
    }
    return retMatrix;
}

double* gaussElimination(double **tab, double *res, int n) {
    for(int i = 0; i < n; i++) {
        double div = tab[i][i];

        for(int j = i; j < n; j++) {
            tab[i][j] /= div;
        }
        res[i] /= div;
        if(i+1 < n) {
            for(int k = i+1; k < n; k++) {
                double mul = tab[i][i]*tab[k][i];
                for(int j = i; j < n; j++) {
                    tab[k][j] -= mul*tab[i][j];
                }
                res[k] -= mul*res[i];
            }
        }
    }
    return res;
}

void back_substitution(double **tab, double* res, int n) {
    for(int i = n-1; i > 0; i--) {
        for(int j = i-1; j>= 0; j--) {
            res[j] -= tab[j][i]*res[i];
        }
    }
}

void printResults(double* res, int n) {
    for(int i = 0; i < n; i++) {
        printf("z%d = %.12f  ", i+1, res[i]);
    }
    printf("\n");
}

double* sub(const double* a,const double* b){
    auto* c = new double[5];
    for (int i = 0; i < 5; i++) {
        c[i] = a[i] - b[i];
    }
    return c;
}

double getNorma(const double* normaM){
    double norma = 0;
    for (int i = 0; i < 5; ++i) {
        norma+= pow(normaM[i],2);
    }
    return sqrt(norma);
}

int main() {
    double *b1{new double[5]{-0.33388066, 1.08033290, -0.98559856, 1.31947922, -0.09473435}};
    double *b2{new double[5]{-0.33388066, 1.08033290, -0.98559855, 1.32655028, -0.10180541}};
    double *b3{new double[5]{0.72677951, 0.72677951, -0.27849178, 0.96592583, 0.96592583}};
    double *b4{new double[5]{0.73031505, 0.73031505, -0.27142071, 0.96946136, 0.96946136}};
    int i = 5;
    cout.precision(15);
    double Norma1 = getNorma(sub(b1,b2));
    double Norma2 = getNorma(sub(b3,b4));
    double **arr0 = Matrix();
    double *z1 = gaussElimination(arr0, b1, i);
    back_substitution(arr0, b1, i);
    double *z2 = gaussElimination(Matrix(), b2, i);
    back_substitution(arr0, b2, i);
    double Norma3 = (getNorma(sub(z1,z2))/Norma1);
    double *z3 = gaussElimination(Matrix(), b3, i);
    back_substitution(arr0, b3, i);
    double *z4 = gaussElimination(Matrix(), b4, i);
    back_substitution(arr0, b4, i);
    double Norma4 = (getNorma(sub(z3,z4))/Norma2);

    cout << "A*z = b1: " << endl;
    printResults(z1,i);
    cout << "A*z = b2: " << endl;
    printResults(z2,i);
    cout << "A*z = b3: " << endl;
    printResults(z3,i);
    cout << "A*z = b4: " << endl;
    printResults(z4,i);

    cout << "||b1-b2|| = " << Norma1 << endl;
    cout << "||b3-b4|| = "<< Norma2 << endl;
    cout << "||z1-z2|| / ||b1-b2|| = "<< Norma3 << endl;
    cout << "||z3-z4|| / ||b3-b4|| = "<< Norma4 << endl;
}