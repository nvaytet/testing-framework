import matplotlib.pyplot as plt
import numpy as np

import sys
files = sys.argv[1:]
print files


#files = ["MasterAlgTestsXThreads.txt"  , \
         #"MasterAlgTestsXThreadsj8.txt", \
         #"NeilAlgTestsXThreads.txt"  , \
         #"NeilAlgTestsXThreadsj8.txt",\
         #"build-23026.txt",\
         #"MasterAlgTests4Threadsj4.txt"]#,\
         ##"build-22481.txt"]

#colors = ["r","r","k","k","cyan","g"]#,"y"]
#markers = ["o","s","o","s","s","^"]#,"s"]
#labels = ["Master","Master-j8","branch20443","branch20443-j8","build-23026","Master-j4+4Threads"]#,"build-22481 (OSX)"]


#files = ["MasterAlgTestsXThreads.txt"  , \
         #"MasterPythonAPITestsXThreadsj8.txt", \
         #"NeilAlgTestsXThreads.txt"  , \
         #"NeilAlgTestsXThreadsj8.txt",\
         #"MasterPythonAPITests4Threadsj4.txt"]

colors = ["r","r","k","k","r","k","cyan","lime","purple"]
markers = ["o","s","o","s","^","^","*","P","X"]
labels = ["Master","Master-j8","branch20443","branch20443-j8","Master-j4+4Threads","branch20443-j4+4Threads","branch20443-OSX","Master-OSX","NewStrings"]

nfiles = len(files)
timings = dict()

for f in files:

    fstream = open(f, 'r')

    maxlen = 0

    # Go through log file content
    for line in fstream:

        if line.count(" Test ") > 0:
            name = (line.split(':')[-1]).split(' ')[1]
            maxlen = max(maxlen,len(name))
            try:
                t = float(line.split(' ')[-2])
            except ValueError:
                #print line
                #print line.split(' ')[-2]
                #exit()
                pass
            if name in timings.keys():
                timings[name].append(t)
            else:
                timings[name] = [t]

    fstream.close()


# Now print and plot timings

fig = plt.figure()
#ratio = 6.0
ratio = 3.0
sizex = 8.0 # 20.0
fig.set_size_inches(sizex,ratio*sizex)
ax1 = fig.add_subplot(111)

xlims = [0.9,140.0]

count = 0.0
step = 1.0
x = []
y = []
z = []
leg = [0] * nfiles
#print("Test name".ljust(maxlen)+": Master 20443 difference")
for key in sorted(timings.keys(),reverse=True):
    if len(timings[key]) == nfiles:
        #diff = timings[key][0]-timings[key][1]
        #print(key.ljust(maxlen)+": %.2f  %.2f  %.2f"%(timings[key][0],timings[key][1],diff))
        count += step
        ax1.text(xlims[0],count,key+" ",ha='right',va='center')
        ax1.plot(xlims,[count,count],color='lightgray',ls='dotted',zorder=-10)
        minval = np.amin(timings[key])
        for i in range(nfiles):
            leg[i], = ax1.plot(timings[key][i]/minval,count,markers[i],color=colors[i])
            #y.append(count)
            #x.append(timings[key][i]/minval)
            #z.append(float(i))

#sc = ax1.scatter(x,y,c=z)
#sc.set_facecolor("none")
ax1.grid(True,color='gray',linestyle='dotted')
ax1.get_yaxis().set_visible(False)

#ax1.legend(leg,labels,ncol=len(files),loc=1)
#ax1.legend(leg,labels,ncol=1,loc=1,fontsize=30)
ax1.legend(leg,labels,ncol=1,loc=1)
ax1.set_xlim(xlims)
ax1.set_ylim([0,count+1])
ax1.set_xscale("log", nonposx='clip')

#fig.savefig("AlgTests_timings.pdf",bbox_inches='tight')
fig.savefig("timings.pdf",bbox_inches='tight')


