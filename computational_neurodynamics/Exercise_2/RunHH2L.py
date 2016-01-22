"""
Computational Neurodynamics
Exercise 2

Simulates two layers of Izhikevich neurons. Layer 0 is stimulated
with a constant base current and layer 1 receives synaptic input
of layer 0.

(C) Murray Shanahan et al, 2015
"""

from ConnectHH2L import ConnectHH2L
import numpy as np
import matplotlib.pyplot as plt

N1 = 4
N2 = 4
T  = 500  # Simulation time
Ib = 7   # Base current

net = ConnectHH2L(N1, N2)

## Initialise layers
for lr in xrange(len(net.layer)):
  net.layer[lr].v = -65.0 * np.ones(net.layer[lr].N)
  net.layer[lr].firings = np.array([]) # empty array (no firings yet)

# time series to record voltage during simulation

v1 = np.zeros([T, N1]) # time series of voltage for N1 neurons over T periods
v2 = np.zeros([T, N2])

## SIMULATE
for t in xrange(T):

   # Deliver a constant base current to layer 1
   net.layer[0].I = Ib * np.ones(N1)
   net.layer[1].I = np.zeros(N2)

   net.Update(t) # net.Update(t) updates ALL the layers in net

   v1[t] = net.layer[0].v
   v2[t] = net.layer[1].v

   if t%5 == 0: print t/5, "/100"

## Retrieve firings and add Dirac pulses for presentation
firings1 = net.layer[0].firings # firings1[t, neuron_index]
firings2 = net.layer[1].firings

if firings1.size != 0:
  v1[firings1[:, 0], firings1[:, 1]] = 30 # v1[t, neuron_index]

if firings2.size != 0:
  v2[firings2[:, 0], firings2[:, 1]] = 30

print firings1.size
print firings2.size


## Plot membrane potentials
plt.figure(1)
plt.subplot(211)
plt.plot(range(T), v1)
plt.title('Population 1 membrane potentials')
plt.ylabel('Voltage (mV)')
# plt.ylim([-90, 40])

plt.subplot(212)
plt.plot(range(T), v2)
plt.title('Population 2 membrane potentials')
plt.ylabel('Voltage (mV)')
# plt.ylim([-90, 40])
plt.xlabel('Time (ms)')

## Raster plots of firings
if firings1.size != 0:
  plt.figure(3)
  plt.subplot(211)
  plt.scatter(firings1[:, 0], firings1[:, 1] + 1, marker='.')
  plt.xlim(0, T)
  plt.ylabel('Neuron number')
  plt.ylim(0, N1+1)
  plt.title('Population 1 firings')

if firings2.size != 0:
  plt.subplot(212)
  plt.scatter(firings2[:, 0], firings2[:, 1] + 1, marker='.')
  plt.xlim(0, T)
  plt.ylabel('Neuron number')
  plt.ylim(0, N2+1)
  plt.xlabel('Time (ms)')
  plt.title('Population 2 firings')

plt.show()
