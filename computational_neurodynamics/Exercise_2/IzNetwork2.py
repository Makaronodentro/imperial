import nympy as np

class IzNetwork
    """
        Network of Izhikevich neurons
    """

    def __init__(self, _neuronsPerLayer, _Dmax):

        self.Dmax = _Dmax
        self.Nlayers = len(_neuronsPerLayer)

        self.layer = {} # empty array that will hold the layers

        for i, n in enumerate(_neuronsPerLayer):
            self.layer[i] = IzLayer(n) # n is the number in _neuronsPerLayer

    def Update(self, t):
        """
        Run simulation of the whole network for 1 millisecond and update the
        network's internal variables.

        Inputs:
        t -- Current timestep. Necessary to sort out the synaptic delays.
        """

        for lr in xrange(self.Nlayers):
            self.NeuronUpdate(lr, t)

    def NeuronUpdate(self, i, t):
        """
        Update one neuron for 1 millisecond using the Euler method.

        Inputs:
        i -- Number of layer to update
        t -- Current timestep. Necessary to sort out the synaptic delays.
        """

        dt = 0.2 # Euler method size in ms

        # Calculate current from incoming spikes
        for j in xrange(self.Nlayers):

            # If layer[i].S[j] exists then layer[i].factor[j] and
            # layer[i].delay[j] exist too
            if j in self.layer[i].S:
                S = self.layer[i].S[j] #target neuron->rows, source neuron->cols

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
