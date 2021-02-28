import numpy as np
import math


def trapez(f, a, b, n):
    h = (b - a) / n
    x = a
    In = f(a)
    for k in range(1, n):
        x = x + h
        In += 2 * f(x)

    K = (In + f(b)) * h * 0.5
    print("Trapezoid: ", round(K, 7))
    return K


def romberg(f, a, b, p):
    I = np.zeros((p, p))
    for i in range(0, p):
        I[i, 0] = trapez(f, a, b, 2 ** i)
        for j in range(0, i):
            I[i, j + 1] = (4 ** (j + 1) * I[i, j] - I[i - 1, j]) / (4 ** (j + 1) - 1)
        x = (I[i, 0:i + 1])
        print_row(x)

    return I


def print_row(X):
    print(' | '.join('%1.8lf' % x for x in X))


def func(x):
    return math.sin(math.pi * (1 + math.sqrt(x)) / (1 + math.pow(x, 2))) * math.pow(math.e, -x)


if __name__ == '__main__':
    p_rows = 20
    I = romberg(func, 0, math.log(10) * 7, p_rows)
    solution = I[p_rows - 1, p_rows - 1]
    print("Final solution: ", round(solution, 7))
