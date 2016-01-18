import numpy as np
import matplotlib.pyplot as plt

Tmin = 0
Tmax = 100
dt = 0.008
T = np.arange(Tmin, Tmax+dt, dt)


# define parameters
I = 10

gNa = 120
gK = 36
gL = 0.3

eNa = 115
eK = -12
eL = 10.6

# capacitance c is ignored as it is set to 1

m = np.zeros(len(T))
n = np.zeros(len(T))
h = np.zeros(len(T))

v = np.zeros(len(T))

v[0] = -10.0

for t in xrange(len(T) - 1):

    ma = (2.5-0.1*v[t])/((np.exp(2.5-0.1*v[t])) - 1)
    mb = 4.0*np.exp((-v[t])/18.0)

    na = (0.1-0.01*v[t])/(np.exp(1-0.1*v[t]) - 1)
    nb = 0.125*np.exp((-v[t])/80.0)

    ha = 0.07*np.exp((-v[t])/20.0)
    hb = 1.0/(np.exp(3-0.1*v[t])+1)

    m[t+1] = m[t] + dt*(ma*(1-m[t]) - mb*m[t])

    n[t+1] = n[t] + dt*(na*(1-n[t]) - nb*n[t])

    h[t+1] = h[t] + dt*(ha*(1-h[t]) - hb*h[t])

    i = gNa*(m[t]**3)*h[t]*(v[t]-eNa) + gK*(n[t]**4)*(v[t] - eK) + gL*(v[t] - eL)

    v[t+1] = v[t] + dt*(-i + I)

print v[0]

plt.subplot(211)
plt.plot(T, v, 'r')
plt.xlabel('Time (ms)')
plt.ylabel('Membrane potential v (mV)')
plt.title('HH Neuron')

plt.show()
