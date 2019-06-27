import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


x = np.linspace(0,30,1000)
fig, ax = plt.subplots()
line, = ax.plot(np.random.rand(1000))
ax.set_ylim(-1.1, 1.1)


def update(data):
    line.set_ydata(data)
    return line,


def data_gen():
    t = 0
    q1 = 1
    q2 = 2
    while True:
        t += 0.1
        yield np.sin(x - q1 * t) + np.sin(x - q2 * t)

ani = animation.FuncAnimation(fig, update, data_gen, interval=1.0/60.0*1000)
plt.show()

