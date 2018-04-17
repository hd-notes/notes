import numpy as np
import matplotlib.pyplot as plt
import scipy.optimize as optimize

def f(x,a):
    return x - np.sin(x) - a

def fprime(x,a):
    return 1 - np.cos(x)

n = 1000
xs = np.linspace(0,2*np.pi,n)

pret = xs - np.sin(xs)

t = []

for x in xs:
    startx = xs[np.argmin(np.abs(pret - x))]
    t.append(optimize.newton(f, startx, fprime=fprime, args=(x,)))

t = np.array(t)

plt.plot(t - np.sin(t), 1 - np.cos(t), linestyle="None", marker="+")
plt.show()
