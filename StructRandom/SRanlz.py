import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
from matplotlib import cm


class FullData:

    def __init__(self, file_name):
        self.data = pd.read_csv(file_name, index_col=0)
        self.dx = sorted(list(set(self.data.delta)))
        self.bx = sorted(list(set(self.data.beta)))
        self.px = sorted(list(set(self.data.p)))

    def select_p_mtau(self, delta, beta, graph):
        return self.data[(self.data.delta == delta )
                         & (self.data.beta == beta)
                         & (self.data.graph == graph)
                         ].ix[:,['p','mtau']].values

    def select_p_mag(self, delta, beta, graph):
        return self.data[(self.data.delta == delta )
                         & (self.data.beta == beta)
                         & (self.data.graph == graph)
                         ].ix[:,['p','mag']].values



def plot_p_mtau_d(delta_ix):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    cmap = plt.get_cmap('jet')
    cNorm = colors.Normalize(vmin=B.bx[0], vmax = B.bx[-1])
    scalarMap = cm.ScalarMappable(norm=cNorm, cmap=cmap)
    for b in B.bx:
        WS = B.select_p_mtau(B.dx[delta_ix], b, 1).T
        BA = B.select_p_mtau(B.dx[delta_ix], b, 2).T
        colorval = scalarMap.to_rgba(b)
        plt.plot(WS[0], WS[1], color=colorval)
        plt.plot(BA[0], BA[1], '--', color=colorval)

def plot_p_mtau_b(beta_ix):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    cmap = plt.get_cmap('jet')
    cNorm = colors.Normalize(vmin=B.dx[0], vmax = B.dx[-1])
    scalarMap = cm.ScalarMappable(norm=cNorm, cmap=cmap)
    for d in B.dx:
        WS = B.select_p_mtau(d, B.bx[beta_ix], 1).T
        BA = B.select_p_mtau(d, B.bx[beta_ix], 2).T
        colorval = scalarMap.to_rgba(d)
        plt.plot(WS[0], WS[1], color=colorval)
        plt.plot(BA[0], BA[1], '--', color=colorval)

if __name__ == '__main__':

    B = FullData('teste_3.csv')
    plot_p_mtau_d(6)
    plot_p_mtau_b(6)

