import sys
import shutil

fname = sys.argv[1]

splitname = fname.split('.')

shutil.copyfile(fname, splitname[0] + "_backup." + splitname[1])

fin = open(fname,'r')
fout = open(fname+".tmp",'w')

counter = 0
printout = "PRINT DEBUG: "

for theLine in fin.readlines():
	line = theLine.rstrip()

	if line.endswith(';') or line.endswith("  }") or line.endswith('{'):
		fout.write(line+'\n std::cout << "'+printout+str(counter)+'" << std::endl;\n')
		counter += 1
	else:
		fout.write(line+'\n')

fin.close()
fout.close()
