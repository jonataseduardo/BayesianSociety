import os
from pylab import *

dirList = os.listdir(os.getcwd())
M = dict()
for name in dirList:
    if ( name.endswith('.dat') and name.startswith('mZ')):

        pa = int(name[-5])
        data  = genfromtxt(name)
        s = double(size(data))
        x = arange(s)/s
        d = sort(data)
        M[pa] = [x, d]

Liber = []
for i in range(2,4):
    Liber += M[i][1].tolist()

Concer = []
for i in range(4,6):
    Concer += M[i][1].tolist()

fig1 = figure()
Ch = hist(Concer, bins=100, range=(0.5,1.0), normed=True)
Lh = hist(Liber, bins=100, range=(0.5,1.0), normed=True)

fig2 = figure()
Lch = hist(Liber, bins=100, range=(0.5,1.0), normed=True,cumulative=True)
Cch = hist(Concer, bins=100, range=(0.5,1.0), normed=True,cumulative=True)

