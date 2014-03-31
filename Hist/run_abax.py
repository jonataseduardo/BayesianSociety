import os
from multiprocessing import Queue, Process
from Queue import Empty
from subprocess import Popen, PIPE, STDOUT
from numpy import * 

Nab , Nbc, Ncd, Nde = 3, 3, 3, 6

nohses = {}
nohses['ab']  = [['ab%02d'%(i+1,),Nab] for i in xrange(13)]
nohses['bc']  = [['bc%02d'%(i+1,),Nbc] for i in xrange(12)]
nohses['cd']  = [['cd%02d'%(i+1,),Ncd] for i in xrange(8)]
nohses['de']  = [['de%02d'%(i+1,),Nde] for i in xrange(5)]

nohses['all'] = nohses['de'] + nohses['cd'] + nohses['bc'] + nohses['ab'] 
nohses['some']= [['ab01',Nab], ['bc01',Nbc], ['cd01',Ncd]]


NodeQueue = Queue()
NodeNames = Queue()
WorkQueue  = Queue()

def ssh( x ):
        ( node, cmd, params ) = x 
        proc = Popen("ssh %s %s %s"%(node, cmd, params), shell = True, stdout = PIPE, stderr = STDOUT)
        output,stderr = proc.communicate()
        status = proc.poll()
        return output, stderr

def makeNames( use="all" ):
    if NodeNames.empty() == True:
        for n in nohses[use]:
            NodeNames.put(n)

def makeworkqueue(param):
    if WorkQueue.empty()==True:
        for p in param:
            WorkQueue.put(p)

def checknodes( ):
    if NodeQueue.empty() == True:    
        while True:
            try:
                node = NodeNames.get(block=False)
                x, err = ssh( (node[0], "uname", "-n" ) )
                if x[:-1] == node[0]:
                    #print node[0]
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
            x, err = ssh( (no, "uname", "-n" ) )
            if x[:-1] == no:
                p = WorkQueue.get(block=False)
                #print no, " -> ", p
                y, err = ssh( ( no, cmd, p ) )
                NodeQueue.put(no)
                if (fname != None):
                    if len(y) > 0:
                        print p, y, err
                        fout = open(fname, 'a')
                        print >>fout, p, y
                        fout.close()
                    else:
                        print "recolocando job: " + p
                        WorkQueue.put(p)

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
    return True

def get_params(fname):
    
    num        = "400"
    graph      = "2"
    tstep      = "1.0"
    coleta     = "5000"
    burn       = "1500"
    tth        = "0.65"
    nmasters   = "4"
    nsamples   = "10"
    
    delta = arange(0.,0.3,0.01)
    delta = append(delta,arange(0.3,1,0.05)) 
    
    beta = arange(0, 5, 0.1)
    beta = append(beta,arange(5,20,0.5))
    viz = range(4,60,2) 
         

    params = [ '%f'%d   + " " +
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
               for d in delta
               for b in beta 
               ]
        
    f = open(fname,'w').close()
    f = open(fname,'a')
    for p in params:
        print >>f, p
    f.close() 
    return params


if __name__=="__main__":

    path = os.getcwd()
    cmd =  path + "/roda"
    fin = path + "/input.txt"
    fname = path + "/Barabasi-K400-n20-teste2.txt" 

    jobs = get_params(fin)

    makeworkqueue(jobs)
    makeNames()
    checkcluster()
    nt = min(WorkQueue.qsize(),NodeQueue.qsize())
    print run(nt)

    dirList = os.listdir(path)
    for name in dirList:
        if fname in name:
            print "fazendo o backup do arquivo " + f_file
            Popen("mv  %s  %s~"%( name, name), shell = True)
