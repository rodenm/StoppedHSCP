
# common methods for getting run info from the Run Tree

def getTotalLivetime(runtree):
    time=0
    # loop over runs in run TTree
    nruns=runtree.GetEntriesFast()
    for i in range(0,nruns):
        entry = runtree.LoadTree(i)
        if entry < 0:
            break
        nb = runtree.GetEntry(i)
        if nb <= 0:
            continue
        time+=runtree.livetime
    return time

# return array of run number/livetime pairs
def getRuns(runtree):
    runs=[]
    # loop over runs in run TTree
    nruns=runtree.GetEntriesFast()
    for i in range(0,nruns):
        entry = runtree.LoadTree(i)
        if entry < 0:
            break
        nb = runtree.GetEntry(i)
        if nb <= 0:
            continue
        runs.append((runtree.run, runtree.livetime))
    return runs

