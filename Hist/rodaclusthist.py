import os
from multiprocessing import Queue, Value, Process
from Queue import Empty
from subprocess import Popen, PIPE, STDOUT
from numpy import * 

Nab , Nbc, Ncd = 4, 4, 4

nohses = {}
nohses['ab']  = [['ab%02d'%(i+1,),Nab] for i in xrange(13)]
nohses['bc']  = [['bc%02d'%(i+1,),Nbc] for i in xrange(12)]
nohses['cd']  = [['cd%02d'%(i+1,),Ncd] for i in xrange(8)]

nohses['all'] = nohses['cd'] + nohses['bc'] + nohses['ab'] 
nohses['some']= [['ab01',Nab], ['bc01',Nbc], ['cd01',Ncd]]


NodeQueue = Queue()
NodeNames = Queue()
WorkQueue  = Queue()
fname = "bar.txt"

def ssh( x ):
        ( node, cmd, params ) = x 
        proc = Popen("ssh %s %s %s"%(node, cmd, params), shell = True, stdout = PIPE, stderr = STDOUT)
        output,stderr = proc.communicate()
        status = proc.poll()
        return output

def makeNames( use="all" ):
    for n in nohses[use]:
        NodeNames.put(n)

def makeworkqueue(param):
    for p in param:
        WorkQueue.put(p)


def checknodes( ):
    while True:
        try:
            node = NodeNames.get(block=False)
            x = ssh( (node[0], "uname", "-n" ) )
            if x[:-1] == node[0]:
                print node[0]
                for n in range(node[1]):
                    NodeQueue.put(node[0])
            else:
                print node[0], " Erro: ", x[:-1] 
        except Empty:
            break


def runjobs( ):
    while True:
        try:
            no = NodeQueue.get()
            x = ssh( (no, "uname", "-n" ) )
            if x[:-1] == no:
                p = WorkQueue.get(block=False)
                print no, " -> ", p
                y = ssh( ( no, cmd, p ) )
                NodeQueue.put(no)
                if (fname != None):
                    fout = open(fname, 'a')
                    print >>fout, p, y
                    fout.close()
            else:
                print no, " Erro: ", x[:-1] 
        except Empty:
            break
   

def runcluster( fun, nthreads):
    #multiprocessamento
    processes = [Process(target = fun, args = ()) for i in range(nthreads)]

    for p in processes:
        p.start()
    for p in processes:
        p.join()


def checkcluster( use = "all"):
    runcluster(checknodes, len(nohses[use]))

def run ( nthreads): 
    runcluster(runjobs,nthreads)
    
if __name__=="__main__":

    path = os.getcwd()
    cmd =  path[8:] + "/roda"
    print cmd

    fname = "testehistloglog3.txt"
    #fname = "histlog.txt"
    dirList = os.listdir(os.getcwd())
    for name in dirList:
        if name == fname:
            print "fazendo o backup do arquivo " + fname
            Popen("mv  %s  %s~"%(fname,fname),shell = True)


    viz        = "20"
    num        = "400"
    graph      = "2"
    tstep      = "1.0"
    coleta     = "10000"
    burn       = "6000"
    tth        = "0.65"
    nmasters   = "4"
    nsamples   = "400"
    
    #rho = arange(0.01,0.99,0.1)
    #rho = append(rho,0.99) 
    #rho = arange(0.0,1.0,0.02)
    rho = arange(0.01,1.0,0.01)
    rho = append(rho,arange(0.805,.99,0.01)) 
    
    #Lamb = append( arange(0.2,1.0,0.02), arange(1.0,3.0,0.1) )
    Lamb = sqrt(1 - rho**2)/rho
    #lbeta = append(arange(-9.0,-4.3,0.2),arange(-4.3,2.0,0.1))
    #lbeta = append(lbeta,arange(2.0,4.0,0.3))
    lbeta = arange(-8.0,4.0,0.1)
    viz = [20]
         
    print "************ PARTE 1 ***************"

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
               for b in reversed(lbeta) ]
    for p in params:
        print p


    makeworkqueue(params)

    makeNames()
    checkcluster()

    nt = min(WorkQueue.qsize(),NodeQueue.qsize())
    run(nt)
