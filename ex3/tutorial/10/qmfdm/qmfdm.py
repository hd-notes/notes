import matplotlib
matplotlib.use('Qt5Agg')
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import scipy.sparse 
import scipy.sparse.linalg
import scipy.optimize as optimize
import numpy.linalg

hbar = 1
m = 1

def laplace1d(n,dx):
    diag = ([[1,-2,1]] / (dx**2)[:,None])
#    diag[0,:] = [0,0,0]
#    diag[-1,:] = [0,0,0]
    ret = scipy.sparse.diags(diag.T,[-1,0,1], shape=(n,n))
    return ret

def hamilton1d(n,dx,v):
    return - hbar * hbar / (2.0 * m) * laplace1d(n,dx) + v

n = 1000
x = np.linspace(0,5,n + 1)
dx = x[:-1] - x[1:]
#v = np.zeros(n)
#v[np.abs(x[:-1]) > 2] = 50 # box potential
# v = x[:-1]**2 # harmonic oszillator
# v = -1.0 / np.abs(x[:-1]) #  1 / r
# v[v < -10000000] = -10000000
# v = np.exp(x[:-1]) 
# print(v)

# cycloid

def cy(x, a):
    return x - np.sin(x) - a

def cyprime(x, a):
    return 1 - np.cos(x)
xss = np.linspace(0, 1 * np.pi, n)
pret = cy(xss, 0)
t = []

for xs in xss:
    startx = xss[np.argmin(np.abs(pret - xs))]
    t.append(optimize.newton(cy, startx, fprime=cyprime, args=(xs, )))
t = np.array(t)

v = 1.0* (-1.0 + np.cos(t)) + 2.0
#ahalf = v[:n/2]
#bhalf = v[n/2:]
#v = np.append(bhalf, ahalf)

V = scipy.sparse.diags([v], [0])
H = hamilton1d(n, dx, V)
#print(H.todense())
k = 3

w, vs = scipy.sparse.linalg.eigsh(H, k = k, which='SM', maxiter=1000000)
#w, vs = numpy.linalg.eig(H.todense())
w = w[np.argsort(w)]
vs = vs[:,np.argsort(w)]
#print(np.abs(vs))
#print(w)

#print(w)
plt.plot(x[:-1], v / np.max(np.abs(v)) * np.max(np.abs(vs[:,:k])**2))
plt.plot(x[:-1], np.abs(vs[:,:k])**2)
gaussian = np.exp(-(x[:-1] - 1)**2)
plt.show()
#plt.plot(w)
coeffs = []
for eig in vs.T:
    coeffs.append(np.abs(np.dot(gaussian,eig)))

coeffs = np.array(coeffs)

#print np.dot(vs,)

gmod = np.array(x.shape)
gmod[:] = 0

for (i, eig) in enumerate(vs.T):
    gmod = gmod + coeffs[i] * eig


#print(gmod)
#plt.plot(x[:-1],gaussian[:,None] * vs)
#plt.plot(x[:-1],gaussian)
#plt.plot(coeffs)
#print(coeffs)
#print(coeffs)
#plt.plot(x[:-1], np.real(vs[:,:k]))
#plt.plot(x[:-1], np.abs(vs[:,:k])**2)
#plt.plot(x[:-1], -v * np.max(vs) / np.max(v))
#for e in v:
#plt.show()

f, (ax1, ax2) = plt.subplots(2,1,sharex='col')

ax2.plot(x[:-1], v / 4)
re, = ax1.plot(x[:-1], np.real(gmod))
im, = ax1.plot(x[:-1], np.imag(gmod))
a, = ax2.plot(x[:-1], np.abs(gmod)**2)

ax1.set_ylim([-1.3,1.3])
ax2.set_ylim([-.1,1.3])

def init():
    gmod = np.array(x.shape)
    gmod[:] = 0

    for (i, v) in enumerate(vs.T):
        gmod = gmod + coeffs[i] * v
    
    re.set_data(x[:-1], np.real(gmod))
    im.set_data(x[:-1], np.imag(gmod))
    a.set_data(x[:-1], np.abs(gmod)**2)
#    (WaveFunc, PotKurve, xVals) = calc(0)
#    re.set_data(xVals,np.real(WaveFunc))
#    im.set_data(xVals,np.imag(WaveFunc))
#    a.set_data(xVals,np.abs(WaveFunc)**2)
def animate(t):
    gmod = np.array(x.shape)
    gmod[:] = 0
    for (i, v) in enumerate(vs.T):
        gmod = gmod + coeffs[i] * v * np.exp(-1.j * (w[i] / hbar) * t)
    
    re.set_data(x[:-1], np.real(gmod))
    im.set_data(x[:-1], np.imag(gmod))
    a.set_data(x[:-1], np.abs(gmod)**2)
#    (WaveFunc, PotKurve, xVals) = calc(i)
#    re.set_data(xVals,np.real(WaveFunc))
#    im.set_data(xVals,np.imag(WaveFunc))
#    a.set_data(xVals,np.abs(WaveFunc)**2)

#for t in range(0,1000,100):
#    animate(t)
#plt.show()
#ani = animation.FuncAnimation(f, animate, np.linspace(0,12*np.pi,500), init_func=init)
#ani.show()
#ani.save('test.mp4', fps=25, dpi=100)
