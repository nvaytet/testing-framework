from pylab import *
import numpy as np

min_threads = 2
max_threads = 24
inc_threads = 2

min_ctest_j = 2
max_ctest_j = 12
inc_ctest_j = 2



data = np.zeros([(max_threads-min_threads)/inc_threads+1,(max_ctest_j-min_ctest_j)/inc_ctest_j+1])
xload = []
yload = []
zload = []




f = open('total_timings.txt', 'r')

# Go through log file content
for line in f:
    fname = line.split(':')[0]
    string = fname.replace("FastTests_","").replace("Threads_j"," ").replace(".txt","")
    n = int(string.split(' ')[0])
    j = int(string.split(' ')[1])
    #print string
    #print n,j
    #print n/inc_threads - 1,j/inc_ctest_j - 1
    data[n/inc_threads - 1,j/inc_ctest_j - 1] = float(line.split(' ')[-2])
    xload.append(n)
    yload.append(float(line.split(' ')[-2]))
    zload.append(float(n*j)/24.0)
    #[n/inc_threads - 1,j/inc_ctest_j - 1] = float(n*j)/24.0
    #print data[n/inc_threads - 1,j/inc_ctest_j - 1]




fig = plt.figure()
#ratio = 6.0
#ratio = 0.7
#sizex = 8.0 # 20.0
#fig.set_size_inches(sizex,ratio*sizex)
ax1 = fig.add_subplot(111)


x = range(min_threads,max_threads+1,inc_threads)

#jet = cm = plt.get_cmap('jet')
#cNorm = matplotlib.colors.Normalize(vmin=0,vmax=np.shape(data)[1]-1)
#scalarMap = matplotlib.cm.ScalarMappable(norm=cNorm,cmap=jet)

for j in range(np.shape(data)[1]):

    #colorVal = scalarMap.to_rgba(j)
    #ax1.plot(x,data[:,j],color=colorVal)
    ax1.plot(x,data[:,j],label="ctest -j %i" %(min_ctest_j + j*inc_ctest_j))

s1 = ax1.scatter(xload,yload,c=zload,cmap="jet")
cb1 = plt.colorbar(s1,ax=ax1)
cb1.ax.set_ylabel("($N_{\mathrm{threads}} \\times j$) / (Number of available threads = 24)")

ax1.legend(ncol=3)
ax1.set_xlabel("Number of threads")
ax1.set_ylabel("AllTests (excluding MantidPlot) runtime (s)")
ax1.grid(True,color='gray',linestyle='dotted')

#fig.savefig("AlgTests_timings.pdf",bbox_inches='tight')
fig.savefig("ctest_threads_vs_j.pdf",bbox_inches='tight')


