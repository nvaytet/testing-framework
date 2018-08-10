#!/bin/bash

PWD=$(pwd);
# path1="../Framework/Kernel/inc/MantidKernel/Strings";
path1=~/.mantid;
path2=../Framework/Kernel/src;

BASE1="FastTests";

# for n in $(seq 2 2 24); do
# 
#   cp ${path1}/Mantid.user.properties.backup ${path1}/Mantid.user.properties;
#   sed -i "s/#MultiThreaded.MaxCores=4/MultiThreaded.MaxCores=${n}/g" ${path1}/Mantid.user.properties;
#   cp ${PWD}/${path2}/ConfigService_backup.cpp ${PWD}/${path2}/ConfigService.cpp;
#   sed -i "s/#MultiThreaded.MaxCores=4/MultiThreaded.MaxCores=${n}/g" ${PWD}/${path2}/ConfigService.cpp;
#   make -j 20;
  
  n=4;
  for i in $(seq 14 2 24); do
  
    ctest -E MantidPlot -j $i | tee ${BASE1}_${n}Threads_j${i}.txt;
  
  done

# done

exit;

# echo "Copying Strings.h file";
# # cp ${PWD}/${path1}_${BASE1}.h ${PWD}/${path1}.h;
# 
# # echo "Building";
# 
# # cp ~/.mantid/Mantid.user.properties_24 ~/.mantid/Mantid.user.properties;
# cp ${PWD}/${path2}_24.cpp ${PWD}/${path2}.cpp;
# make -j 20;
# ctest | tee ${BASE1}24Threads.txt;
# ctest -j 8 | tee ${BASE1}24Threadsj8.txt;
# 
# # cp ~/.mantid/Mantid.user.properties_4 ~/.mantid/Mantid.user.properties;
# cp ${PWD}/${path2}_4.cpp ${PWD}/${path2}.cpp;
# make -j 20;
# ctest -j 4 | tee ${BASE1}4Threadsj4.txt;


# 
# ctest -R python.api | tee ${BASE1}PythonApiXThreads.txt;
# ctest -j 8 -R python.api | tee ${BASE1}PythonApiXThreadsj8.txt;
# 
# 
# cp ~/.mantid/Mantid.user.properties_24 ~/.mantid/Mantid.user.properties;
# ctest -R AlgorithmsTest_ | tee ${BASE1}AlgorithmsTestXThreads.txt;
# ctest -j 8 -R AlgorithmsTest_ | tee ${BASE1}AlgorithmsTestXThreadsj8.txt;
# ctest -R python.api | tee ${BASE1}PythonApiXThreads.txt;
# ctest -j 8 -R python.api | tee ${BASE1}PythonApiXThreadsj8.txt;
# 
# cp ~/.mantid/Mantid.user.properties_4 ~/.mantid/Mantid.user.properties;
# ctest -j 4 -R AlgorithmsTest_ | tee ${BASE1}AlgorithmsTest4Threadsj4.txt;
# ctest -j 4 -R python.api | tee ${BASE1}PythonApi4Threadsj4.txt;
# 
# 
# 
# 
# BASE2="Master";
# 
# echo "Copying Strings.h file";
# cp ${PWD}/${path1}_${BASE2}.h ${PWD}/${path1}.h;
# 
# echo "Building";
# make -j 20;
# 
# cp ~/.mantid/Mantid.user.properties_24 ~/.mantid/Mantid.user.properties;
# ctest -R AlgorithmsTest_ | tee ${BASE2}AlgorithmsTestXThreads.txt;
# ctest -j 8 -R AlgorithmsTest_ | tee ${BASE2}AlgorithmsTestXThreadsj8.txt;
# ctest -R python.api | tee ${BASE2}PythonApiXThreads.txt;
# ctest -j 8 -R python.api | tee ${BASE2}PythonApiXThreadsj8.txt;
# 
# cp ~/.mantid/Mantid.user.properties_4 ~/.mantid/Mantid.user.properties;
# ctest -j 4 -R AlgorithmsTest_ | tee ${BASE2}AlgorithmsTest4Threadsj4.txt;
# ctest -j 4 -R python.api | tee ${BASE2}PythonApi4Threadsj4.txt;
# 
# python ~/work/mantid/testing-framework/python/Strings_Join_extract_timings.py ${BASE2}PythonApiXThreads.txt ${BASE2}PythonApiXThreadsj8.txt ${BASE1}PythonApiXThreads.txt ${BASE1}PythonApiXThreadsj8.txt ${BASE2}PythonApi4Threadsj4.txt ${BASE1}PythonApi4Threadsj4.txt;
# 
# cp AlgTests_timings.pdf pythonAPI_timings.pdf
# 
# python ~/work/mantid/testing-framework/python/Strings_Join_extract_timings.py ${BASE2}AlgorithmsTestXThreads.txt ${BASE2}AlgorithmsTestXThreadsj8.txt ${BASE1}AlgorithmsTestXThreads.txt ${BASE1}AlgorithmsTestXThreadsj8.txt ${BASE2}AlgorithmsTest4Threadsj4.txt ${BASE1}AlgorithmsTest4Threadsj4.txt;
