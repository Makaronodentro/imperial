import numpy as np


class HHNetwork:
  """
  Network of Hodgkin-Huxley neurons.
  """

  def __init__(self, _neuronsPerLayer, _Dmax):
    """
    Initialise network with given number of neurons

    Inputs:
    _neuronsPerLayer -- List with the number of neurons in each layer. A list
                        [N1, N2, ... Nk] will return a network with k layers
                        with the corresponding number of neurons in each.

    _Dmax            -- Maximum delay in all the synapses in the network. Any
                        longer delay will result in failing to deliver spikes.
    """

    self.Dmax = _Dmax # Max delay
    self.Nlayers = len(_neuronsPerLayer)

    self.layer = {} # empty array that will hold the layers

    for i, n in enumerate(_neuronsPerLayer):
      self.layer[i] = HHLayer(n) # populating the array

  def Update(self, t):
    """
    Run simulation of the whole network for 1 millisecond and update the
    network's internal variables.

    Inputs:
    t -- Current timestep. Necessary to sort out the synaptic delays.
    """
    for lr in xrange(self.Nlayers):  # traverse all the layers of the network
      self.NeuronUpdate(lr, t) # update the individual neurons

  def NeuronUpdate(self, i, t):
    """
    HH neuron update function. Update one layer for 1 millisecond
    using the Euler method.

    Inputs:
    i -- Number of layer to update
    t -- Current timestep. Necessary to sort out the synaptic delays.
    """

    # Euler method step size in ms
    dt = 0.02

    # Calculate current from incoming spikes, for all the layers
    for j in xrange(self.Nlayers): # Nlayers is the number of Neurons per layer

      # If layer[i].S[j] exists then layer[i].factor[j] and
      # layer[i].delay[j] have to exist
      if j in self.layer[i].S:
        S = self.layer[i].S[j]  # target neuron->rows, source neuron->columns
        # targets the specific neuron

        # Firings contains time and neuron idx of each spike.
        # [t, index of the neuron in the layer j]
        firings = self.layer[j].firings

        # Find incoming spikes taking delays into account
        delay = self.layer[i].delay[j]
        F = self.layer[i].factor[j]

        # Sum current from incoming spikes
        k = len(firings)
        while k > 0 and (firings[k-1, 0] > (t - self.Dmax)):
          idx = delay[:, firings[k-1, 1]] == (t-firings[k-1, 0])
          self.layer[i].I[idx] += F * S[idx, firings[k-1, 1]]
          k = k-1

    # Update v and u using the Izhikevich model and Euler method
    for k in xrange(int(1/dt)):
      v = self.layer[i].v

      m = self.layer[i].m
      n = self.layer[i].n
      h = self.layer[i].h

      iS = self.layer[i].iS

      ma = (2.5-0.1*v)/((np.exp(2.5-0.1*v)) - 1)
      mb = 4.0*np.exp((-v)/18.0)

      na = (0.1-0.01*v)/(np.exp(1-0.1*v) - 1)
      nb = 0.125*np.exp((-v)/80.0)

      ha = 0.07*np.exp((-v)/20.0)
      hb = 1.0/(np.exp(3-0.1*v)+1)

      self.layer[i].m = m + dt*(ma*(1-m) - mb*m)
      self.layer[i].n = n + dt*(na*(1-n) - nb*n)
      self.layer[i].h = h + dt*(ha*(1-h) - hb*h)

      self.layer[i].iS = (
        self.layer[i].gNa*(m**3)*h*(v - self.layer[i].eNa) +
        self.layer[i].gK*(n**4)*(v - self.layer[i].eK) +
        self.layer[i].gL*(v - self.layer[i].eL) )

      self.layer[i].v += dt*(-self.layer[i].iS + self.layer[i].I)

      # Find index of neurons that have fired this millisecond
      fired = np.where(self.layer[i].v >= 90)[0]

      if len(fired) > 0:
        for f in fired:
          # Add spikes into spike train
          if len(self.layer[i].firings) != 0:
            self.layer[i].firings = np.vstack([self.layer[i].firings, [t, f]])
          else:
            self.layer[i].firings = np.array([[t, f]])

    return


class HHLayer:
  """
  Layer of Hodgkin-Huxley neurons to be used inside an HHNetwork.
  """

  def __init__(self, n):
    """
    Initialise layer with empty vectors.

    Inputs:
    n -- Number of neurons in the layer
    """

    self.N = n

    self.gNa = np.zeros(n)
    self.gK = np.zeros(n)
    self.gL = np.zeros(n)

    self.eNa = np.zeros(n)
    self.eK = np.zeros(n)
    self.eL = np.zeros(n)

    self.m = np.zeros(n)
    self.n = np.zeros(n)
    self.h = np.zeros(n)

    self.iS = np.zeros(n)

    self.S      = {}
    self.delay  = {}
    self.factor = {}
