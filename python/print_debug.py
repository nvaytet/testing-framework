import sys
import shutil

in_fname = sys.argv[1]
out_fname = in_fname+'.tmp'

splitname = in_fname.split('.')

shutil.copyfile(in_fname, splitname[0] + '_backup.' + splitname[1])

fin = open(in_fname,'r')
fout = open(out_fname,'w')

fout.write('#include <iostream>\n')

counter = 0
print_open = '\n std::cout << "PRINT DEBUG: ' + in_fname
print_close = '" << std::endl;\n'

inside_one_liner_if_block = False

for theLine in fin.readlines():
    line = theLine.rstrip()
    ok = []
    if line.endswith(';'):
        ok.append(True)
    if line.endswith('  }'):
        ok.append(True)
    if line.endswith(') {'):
        ok.append(True)
    if line.lstrip().startswith('using'):
        ok.append(False)
    if line.lstrip().startswith('namespace'):
        ok.append(False)
    if line.lstrip().startswith('switch ('):
        ok.append(False)
    if line.lstrip().startswith('switch('):
        ok.append(False)
    if (line.lstrip().startswith('case')) and (line.endswith(':')) :
        ok.append(True)
    if line.endswith(' break;'):
        ok.append(False)
    if line.lstrip().startswith('return '):
        ok.append(False)

    # Handling if () one-liners
    if (line.lstrip().startswith('if (')) and (line.endswith(')')):
        counter += 1
        fout.write(line+' {'+print_open+' '+str(counter)+print_close)
        inside_one_liner_if_block = True
    elif (len(ok) == 0) or (False in ok):
        fout.write(line+'\n')
    else:
        counter += 1
        fout.write(line+print_open+' '+str(counter)+print_close)
        if inside_one_liner_if_block:
            counter += 1
            fout.write('}'+print_open+' '+str(counter)+print_close)
            inside_one_liner_if_block = False

fin.close()
fout.close()

shutil.move(out_fname, in_fname)
