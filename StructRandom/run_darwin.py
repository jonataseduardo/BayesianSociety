import pandas as pd
import numpy as np
from multiprocessing import Pool
from subprocess import Popen, PIPE, STDOUT


def get_params():
    
    num        = "400"
    graph      = "1" # Watts Strogats 1, Barabasi 2
    tstep      = "1.0"
    coleta     = "1000"
    burn       = "500"
    tth        = "0.65"
    nmasters   = "2"
    nsamples   = "2"
    
    delta = np.linspace(0,1,3) 

    beta = np.linspace(0,8,3) 

    # viz = range(4,20,2)
    recon_prob = np.linspace(0,1,5)

    params = [ '%f'%d   + " " +
               '%f'%b   + " " +
               "%f"%p   + " " +
               num      + " " +
               graph    + " " +
               tstep    + " " +
               coleta   + " " +
               burn     + " " +
               tth      + " " +
               nmasters + " " +
               nsamples   
               for p in recon_prob
               for d in delta
               for b in reversed(beta) ]
        
    return params


def pp(cmd):
    return Popen(cmd,
                 shell=True,
                 stdout=PIPE,
                 stderr=STDOUT).communicate()


def main(params):
    return [params, pp('./roda ' + params )]


def organize(rdata, params):
    """
    Params
    ------
    rdata: [params, (string(hist + result), None)]
    """
     
    rdata = pd.Series([i[0] + i[1][0].split('\n')[-1] for i in out])
    rdata
    rdata[0]
    rdata[0][1][0].split('\n')[-1]


if __name__ == '__main__':

    params = get_params()
    params[0]
    pp('echo {} > input'.format(params[0]))
    
    pool = Pool(processes=20)
    resp = pool.map_async(main, params)
    out = [i for i in  resp.get()]

