from multiprocessing import Process, Array, Manager, Value
import random
import time
import sys





def loop(v,pid):
	# print(v)
	# print(dir(v))
	# print(v.value
	while (v.value > 0):
		count_and_wait(v,pid)
	return



def count_and_wait(v,pid):
	wait = random.random() * 10.0
	print("I am process %i and the count is" % pid,v.value,"waiting for %f seconds" % wait)
	sys.stdout.flush()
	with v.get_lock():
		v.value += -1
	# v -= 1
	time.sleep(wait)
	return






n = 100

ncores = 4

num = Value('i', n)
pid = Value('i', 0)
# nworking = Value('i', ncores)



# Multi-core processes
processes = [] # an array to hold the processes
# results_array = Array('i', 4*optionncores) # shared array to hold skipped, failed and total number of tests + status
# test_counter = Array('i', [0, 0, 0]) # shared array for number of executed tests, total number and max name length
# manager = Manager() # a manager to create a shared dict to store names of skipped and failed tests
# status_dict = manager.dict() # a shared dict to store names of skipped and failed tests

# print(mtdconf.testDir)
# print(mtdconf.dataDir)
# print(mtdconf.saveDir)
# exit()

# while n > 0:
# 	with pid.get_lock():
# 		pid.value = (pid.value + 1) % ncores
# 		p = Process(target=count_and_wait,args=(num,pid.value))
# 		p.start()



# Prepare ncores processes
for ip in range(ncores):
    processes.append(Process(target=loop,args=(num,ip)))


# Start and join processes
for p in processes:
    p.start()
# for p in processes:
#     p.join()

print("I am here now")