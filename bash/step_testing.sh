#!/bin/bash

list=$(grep " test_" $1);
arr=(${list});

executable=$(echo $1 | sed 's/\// /g');
executable=(${executable});
for ((i=0;i<${#executable[@]};i++)); do
	if [ ${executable[i]} == "test" ] ; then
		j=$(($i - 1));
		k=$(($i + 1));
		exec_name=${executable[j]};
		test_name=$(echo ${executable[k]} | sed 's/.h//g');
		break;
	fi
done
echo $exec_name $test_name

for ((i=0;i<${#arr[@]};i++)); do
    query=$(echo ${arr[i]} | grep test_);
    if [ ${#query} -gt 0 ] ; then
    	func_name=$(echo ${arr[i]} | sed 's/()//g');
    	echo "Running ${func_name}:";
    	./${exec_name}Test $test_name $func_name;
    	# exit;
    fi


done
