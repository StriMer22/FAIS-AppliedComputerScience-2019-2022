import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate


def f(X):
    return 1 / (1 + 5 * (X ** 2))


def values():
    Yvalues = np.zeros(len(x))
    for k in range(len(x)):
        Yvalues[k] = f(x[k])
    return Yvalues


if '__main__' in __name__:
    x = np.arange(-1, 1.0001, 1 / 32)
    y = values()
    tck = interpolate.splrep(x, y, s=0)
    xnew = np.linspace(-1, 1, 100)
    ynew = interpolate.splev(xnew, tck, der=0)
    yplt = np.array([])
    for xp in xnew:
        yp = 0
        for xi, yi in zip(x, y):
            p = np.prod((xp - x[x != xi]) / (xi - x[x != xi]))
            yp += yi * p
        yplt = np.append(yplt, yp)
    plt.figure()
    plt.plot(x, y, 'r+',xnew, ynew,'b-', xnew, yplt, 'y--')
    plt.legend(['Spline points', 'Interpolate cubic Spline', 'Lagrange'])
    plt.show()
    print(y)
    print(yplt)
