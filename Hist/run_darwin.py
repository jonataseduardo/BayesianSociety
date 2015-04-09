import pandas as pd
import numpy as np
from multiprocessing import Pool
from subprocess import Popen, PIPE, STDOUT

def get_params():
    
    num        = "400"
    graph      = "2"
    tstep      = "1.0"
    coleta     = "1000"
    burn       = "500"
    tth        = "0.65"
    nmasters   = "2"
    nsamples   = "2"
    
    Lamb = np.linspace(0,1,10) 

    beta = np.linspace(0,8,10) 

    viz = range(4,20,2)

    params = [ '%f'%l   + " " +
               '%f'%b   + " " +
               "%d"%v   + " " +
               num      + " " +
               graph    + " " +
               tstep    + " " +
               coleta   + " " +
               burn     + " " +
               tth      + " " +
               nmasters + " " +
               nsamples   
               for v in viz
               for l in Lamb
               for b in reversed(beta) ]
        
    return params

def pp(cmd):
    return Popen(cmd,
                 shell=True,
                 stdout=PIPE,
                 stderr=STDOUT).communicate()


def main(params):
    return pp('./roda ' + params )




if __name__ == '__main__':
    run run_darwin.py
    params = get_params()[:20]
    params[0]
    pp('echo {} > input'.format(params[0]))
    
    # pool = Pool(processes=20)
    # resp = pool.map_async(main, params)
    # out = [i for i in  resp.get()]
