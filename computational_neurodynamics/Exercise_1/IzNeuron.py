"""
Izhikevich Neuron Euler Method

Exercise 1, Question 2 b)

"""

import numpy as np
import matplotlib.pyplot as plt

# Create time series
Tstart = 0 # Start time
Tend = 200 # End time
dt = 0.01 # Time step
T = np.arange(Tstart, Tend+dt, dt)

# Set Parameters
I = 10

a = 0.02
b = 0.2 # Slope of u
c = -65 # The lower the c, the slower the neuron spikes (initial v value)
d = 8 # The higher the d, the slower the neuron spikes (refractory period reset)

# Create arrays for variables
v = np.zeros(len(T))
u = np.zeros(len(T))

# Initialize Values
v[0] = c
u[0] = -1

for t in xrange(len(T) - 1):
    # Calculate u and v
    v[t+1] = v[t] + dt*(0.04*(v[t]**2)+ 5 * v[t] + 140 - u[t] + I)
    u[t+1] = u[t] + dt*(a*(b*v[t] - u[t]))

    # in case of a spike
    if v[t+1] >= 30:
        v[t] = 30
        v[t+1] = c
        u[t+1] = u[t] + d

## Plot the membrane potential
plt.subplot(211)
plt.plot(T, v, 'r')
plt.xlabel('Time (ms)')
plt.ylabel('Membrane potential v (mV)')
plt.title('Izhikevich Neuron')

# Plot the reset variable
plt.subplot(212)
plt.plot(T, u, 'r')
plt.xlabel('Time (ms)')
plt.ylabel('Reset variable u')
plt.show()
