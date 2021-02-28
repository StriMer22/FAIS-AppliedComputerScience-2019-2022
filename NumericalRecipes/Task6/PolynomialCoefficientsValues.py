import numpy as np
import matplotlib.pyplot as plt


def toFixed(numObj, digits=0):
    return f"{numObj:.{digits}f}"


def inv_interpolate(X, Y):
    M = [[_x ** i * (-1) ** (i * len(X)) for _x in X] for i in range(len(X))]
    Coefficient = [np.linalg.det((M + [Y] + M)[d:d + len(X)]) for d in range(len(X) + 1)]
    Coefficient = (Coefficient / Coefficient[0] * (-1) ** (len(X) + 1))[1:]
    return Coefficient


def function():
    x1 = np.linspace(-1, 1, 100)
    y1 = poly(x1)
    plt.plot(x1, y1, label="Interpolate function")
    plt.plot(x, y, "r+", label="Input points")
    plt.xlim(-1, 1)
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend()
    plt.savefig("wykres.jpg")


if '__main__' in __name__:
    x = [0.062500, 0.187500, 0.312500, 0.437500, 0.562500, 0.687500, 0.812500, 0.937500]
    y = [0.687959, 0.073443, -0.517558, -1.077264, -1.600455, -2.080815, -2.507266, -2.860307]
    C = inv_interpolate(x, y)
    poly = lambda _x: sum([C[i] * _x ** i for i in range(len(x))])
    function()
    for i in range(len(C)):
        print("Coefficient", i + 1, "-->", toFixed(C[i], 4))

