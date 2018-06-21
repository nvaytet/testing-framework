from mantid.simpleapi import *
#import numpy
#import time
#from google_perftools_wrapped import StartProfiler, StopProfiler
#import yep

def time_CreateWorkspace(nbins, nspec):
    import numpy
    import time
    xdata = numpy.multiply(numpy.arange(float(nbins + 1)).tolist() * nspec,0.5)
    ydata = numpy.arange(float(nbins)).tolist() * nspec
    #start = time.time()
    #sx = ', '.join(xdata.astype('S'))
    #print len(sx)
    #print sx
    #print "%.3f sec" % (time.time() - start)
    start = time.time()
    print 'here NOW'
    ws = CreateWorkspace(DataX = xdata, DataY = ydata, NSpec = nspec)
    print "%.1f MiB in %.3f sec" % (ws.getMemorySize() / 1000000.0, time.time() - start)
    return ws

def time_WorkspaceFactory(nbins, nspec):
    #import numpy
    xdata = numpy.arange(float(nbins+1))
    ydata = numpy.arange(float(nbins))
    #import time
    start = time.time()
    ws = WorkspaceFactory.create("Workspace2D", NVectors=nspec, XLength=nbins+1, YLength=nbins)
    for i in xrange(nspec):
        ws.setX(i, xdata)
        ws.setY(i, ydata)
    print "%.1f MiB in %.3f sec" % (ws.getMemorySize() / 1000000.0, time.time() - start)
    return ws

#print "ws = time_WorkspaceFactory(1000, 1000)"
#ws = time_WorkspaceFactory(1000, 1000)
#print "ws = time_WorkspaceFactory(100, 10000)"
#ws = time_WorkspaceFactory(100, 10000)
#print "ws = time_WorkspaceFactory(10000, 100)"
#ws = time_WorkspaceFactory(10000, 100)
#print "ws = time_WorkspaceFactory(10000, 1000)"
#ws = time_WorkspaceFactory(10000, 1000)
#print "ws = time_WorkspaceFactory(100000, 1000)"
#ws = time_WorkspaceFactory(100000, 1000)

#yep.start('file_name.prof')
ws = time_CreateWorkspace(100, 100)
#yep.stop()


#print "ws = time_CreateWorkspace(1000, 1000)"
#ws = time_CreateWorkspace(1000, 1000)
#print "ws = time_CreateWorkspace(100, 10000)"
#ws = time_CreateWorkspace(100, 10000)
#print "ws = time_CreateWorkspace(10000, 100)"
#ws = time_CreateWorkspace(10000, 100)
#print "ws = time_CreateWorkspace(10000, 1000)"
#ws = time_CreateWorkspace(10000, 1000)
