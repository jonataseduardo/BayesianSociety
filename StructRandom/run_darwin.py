import pandas as pd
import numpy as np
from multiprocessing import Pool
from subprocess import Popen, PIPE, STDOUT


def get_params():
    
    num        = "400"
    graph      = ["1", "2", "3"] # 1 - Watts Strogats, 2 - Barabasi, 3 - Erdos Renyi
    tstep      = "1.0"
    coleta     = "10000"
    burn       = "800"
    tth        = "0.65"
    nmasters   = "20"
    nsamples   = "50"
    
    delta = np.linspace(0,1,11) 

    beta = np.linspace(0,10,11) 

    def recon_prob(g):
        if g == "3": #from 4 to 20 neighbours on Erdos Renyi
            return  np.linspace(0.01,0.05,21) # if p > 1 the num of neigbs is 4
        else:
            return np.linspace(0,1,21) 

    params = [ '%f'%d   + " " +
               '%f'%b   + " " +
               "%f"%p   + " " +
               num      + " " +
               g        + " " +
               tstep    + " " +
               coleta   + " " +
               burn     + " " +
               tth      + " " +
               nmasters + " " +
               nsamples   
               for g in graph
               for d in delta
               for b in reversed(beta)
               for p in recon_prob(g)]
        
    return params


def pp(cmd):
    return Popen(cmd,
                 shell=True,
                 stdout=PIPE,
                 stderr=STDOUT).communicate()


def main(params):
    print params
    return [params, pp('./roda ' + params )]


def organize(rdata):
    """
    Params
    ------
    rdata: [params, (string(hist + result), None)]
    """

    names = ["delta", "beta", "p", "num", "graph", "tstep", "coleta", "burn", "tth",
             "nmasters", "nsamples", "etau", "eetau", "mtau", "emtau", "mag", "vmag", 
             "sigma", "erg", "verg", "acpt", "vacpt", "n", "TotalTime", "hist"]

    out = [(i[0] + i[1][0].split('\n')[-1]).split() + [':'.join(i[1][0].split('\n')[:-1])] for i in rdata]
    return pd.DataFrame(out, columns=names)



if __name__ == '__main__':

    params = get_params()
    pool = Pool(processes=120)
    resp = pool.map_async(main, params)
    out = [i for i in  resp.get()]
    data = organize(out)
    data.to_csv('teste_5.csv')
