import os
from pylab import *
from scipy.stats import beta

dirList = os.listdir(os.getcwd())
M = {}
Theta = {}
for name in dirList:
    if ( name.endswith('.dat') and name.startswith('mZ')):
        pa = int(name[-5])
        data  = genfromtxt(name)
        print len(data)
        M[pa] = (data + 1.0)/2.0
        Theta[pa] = [mean(M[pa]),var(M[pa])]
        


def makefig( pa ):
    fig = figure()
    ax = axes()

    ax.hist(M[pa],bins=100,range=(0.5,1.0),normed=True)

    mu = Theta[pa][0]
    nu = mu*(1.0 -mu)/Theta[pa][1] - 1.0
    a = mu*nu
    b = (1.0 - mu)*nu
    rv = beta(a,b)
    x = arange(0.5,1.001,0.005)
    ax.plot(x,rv.pdf(x),lw = 3)

    fig.add_axes(ax)
    fig.show()
    return fig

for i in range(1,8):
    makefig(i)
