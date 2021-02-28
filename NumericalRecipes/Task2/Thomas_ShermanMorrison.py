from timeit import default_timer as timer
import numpy as np

#Algorytm Thomasa
# a - przekątna poniżej głównej
# b - główna przekątna macierzy
# c - przekątna nad główną
# d - prawa strona (kolumna(wyniki))
def Thomas(a,b,c,d):
    try:
        n = len(d)
        A = np.array([[0]*n]*n, dtype='float64')

        for i in range(n):
            A[i,i] = b[i]
            if i > 0:
                A[i, i-1] = a[i]
            if i < n-1:
                A[i, i+1] = c[i]

        c_1 = [0]*n
        d_1 = [0]*n

        for i in range(n):
            if not i:
                c_1[i] = c[i]/b[i]
                d_1[i] = d[i] / b[i]
            else:
                c_1[i] = c[i]/(b[i]-c_1[i-1]*a[i])
                d_1[i] = (d[i]-d_1[i-1]*a[i])/(b[i]-c_1[i-1] * a[i])

        x = [0]*n

        for i in range(n-1, -1, -1):
            if i == n-1:
                x[i] = d_1[i]
            else:
                x[i] = d_1[i]-c_1[i]*x[i+1]

        x = [round(_, 16) for _ in x]

        return x

    except Exception as e:
        return e

#Wzór Shermana-Morissona dla rozwiązywania cyklicznego trójdiagonalnego równania liniowego A*x = b
# a - przekątna poniżej głównej
# b - główna przekątna macierzy
# c - przekątna nad główną
# d - prawa strona (kolumna(wyniki))
def ShermanMorrison(a,b,c,d):
    try:
        n = len(d)
        A = np.array([[0] * n] * n, dtype='float64')

        for i in range(n):
            A[i, i] = b[i]
            if i > 0:
                A[i, i - 1] = a[i]
            if i < n - 1:
                A[i, i + 1] = c[i]
        A[0, n - 1] = a[0]
        A[n - 1, 0] = c[n - 1]

        gamma = 1 # może być dowolna
        u = [gamma] + [0] * (n - 2) + [c[n - 1]]
        v = [1] + [0] * (n - 2) + [a[0] / gamma]

        # Modyfikacja współczynnika A'
        b[0] -= gamma
        b[n - 1] -= a[0] * c[n - 1] / gamma
        a[0] = 0
        c[n - 1] = 0

        # rozwiąż A'y = d, A'z = u, używając algorytmu Thomasa
        y = np.array(Thomas(a, b, c, d))
        z = np.array(Thomas(a, b, c, u))

        # używamy y i z, aby obliczyć x
        # x jest rozwiązaniem A*x = b
        x = y - (np.dot(np.array(v), y)) / (1 + np.dot(np.array(v), z)) * z
        x = [round(_, 16) for _ in x]
        return x

    except Exception as e:
        return e

def main():
    a = [1, 1, 1, 1, 1, 1, 1]
    b = [4, 4, 4, 4, 4, 4, 4]
    c = [1, 1, 1, 1, 1, 1, 1]
    d = [1, 2, 3, 4, 5, 6, 7]
    start_time = timer()*1000000000
    x = ShermanMorrison(a,b,c,d)
    end_time = timer()*1000000000
    for index, value in enumerate(x):
        print('X%s --> ' %index, value)
    print("\nTotal elapsed: {:g} nanosecs".format(end_time - start_time))
main()