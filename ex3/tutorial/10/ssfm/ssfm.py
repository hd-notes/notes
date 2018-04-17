import numpy as np
import scipy.fftpack as fft
import matplotlib.pyplot as plt

hbar = 1
m = 1

def normalize(x):
    return x / np.sqrt(np.sum(np.abs(x)**2))

def split_step_single(ψ, dt, n):
    xn = x0
#    k = 2*np.pi*

N = 2000

x = np.linspace(-30,30,N)
dx = np.diff(x).mean()

k = 2 * np.pi * fft.fftshift(fft.fftfreq(N, d = dx))
dk = np.diff(k).mean()

# V = (np.pi)**2 * (m / 2) * x**2
V = np.full(N, 0)
#V[np.abs(x) > 20] = 1e10

T = hbar**2 * k**2 / (2 * m)

σ = 15
x0 = 0
k0 = 1
ψ = normalize(np.exp(-(x - x0)**2 / (2 * σ**2)))
ψ = fft.ifft(fft.fftshift(np.roll(fft.fftshift(fft.fft(ψ)), np.int(np.round(k0 / dk)))))
dt = .5e-3
tfin = 1000

M = round(tfin / dt)
ts = np.full(M, np.nan)
calcval = ts.copy()
calcval2 = ts.copy()

fig = plt.figure(1)
ax1 = fig.add_subplot(2,2,1)
ax2 = fig.add_subplot(2,2,2)
ax3 = fig.add_subplot(2,2,3)
ax4 = fig.add_subplot(2,2,4)

t = 0
count = 0
valcount = 0

for m in range(0,M):
    t = t + dt
    count = count + 1
    ψ = fft.ifft(fft.fftshift(fft.fftshift(fft.fft(
        np.exp(-1j * V / hbar * dt) * ψ)) * np.exp(-1j * T / hbar * dt)))

    if count > 100:
        ts[valcount] = t
        ψk = fft.fftshift(fft.fft(ψ))
        meank = np.sum(np.conj(ψk) * k * ψk)
        meank = np.real(meank)
        meank2 = np.sum(np.conj(ψk) * k**2 * ψk)
        meank2 = np.real(meank2)
        meanx = np.sum(np.conj(ψ) * x * ψ)
        meanx = np.real(meanx)
        meanx2 = np.sum(np.conj(ψ) * x**2 * ψ)
        meanx2 = np.real(meanx2)

        calcval[valcount] = np.sqrt(meanx2 - meanx**2)
        calcval2[valcount] = np.sqrt(meank2 - meank**2)
        valcount += 1

        count = 0
        ax1.cla()
        ax2.cla()
        ax3.cla()
        ax4.cla()
        ax1.plot(x, np.abs(ψ)**2)
        ax2.plot(k, np.abs(ψk)**2)
        ax3.plot(x, np.angle(ψ))
        ax3.set_xlim([-10,10])
#        ax3.set_ylim([-.01,.0])
        ax4.plot(k, np.angle(ψk))
        ax4.set_xlim([-2.5,2.5])
        fig.canvas.draw()
        plt.pause(0.00001)
        

