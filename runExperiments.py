import subprocess
import re

def experiment(executableName,xx,yy):

	outputTxt = open(executableName+'.txt','w+');
	# subP = subprocess.Popen(['processes.out',str(xx),str(yy)],stdout=outputTxt)
	subP = subprocess.Popen([executableName,str(xx),str(yy)],stdout=outputTxt)
	subP.wait()
	getNanoWords = re.compile('\d* nanoseconds')
	getNanoString = re.compile('\d*')

	getSecWords = re.compile('\d* seconds')
	getSecString = re.compile('\d*')

	procRead = open(executableName+'.txt','r');
	nanoseconds = -1
	seconds = -1

	for line in procRead:
		foundNano = getNanoWords.search(line)
		foundSec = getSecWords.search(line)
		# print(line)
		if (foundNano != None):
			stringNS = foundNano.group()
			nanoseconds = int(getNanoString.search(stringNS).group())
			# print("nanoseconds:" + str(nanoseconds))
		if (foundSec != None):
			stringS = foundSec.group()
			seconds = int(getSecString.search(stringS).group())
			# print("seconds:" + str(seconds))

	experimentResults = {'seconds':seconds,'nanoseconds':nanoseconds}
	return experimentResults

def avgOfThree(executableName,xx,yy):

	print("\n------\nCurrently running " + executableName + " with x=" + str(xx) + " and y=" + str(yy) + " it's running it 3 times and averaging it so could take a while so WAIT!\n")
	sumSec = 0
	sumNSec = 0
	for i in range(3):
		EX = experiment(executableName,xx,yy)
		# print('EXNS: ' + str(EX['nanoseconds']))
		sumSec+=EX['seconds']
		sumNSec+=EX['nanoseconds']

	# note doing int division!
	avgSec = sumSec//3
	avgNSec = sumNSec//3

	# print("avgSec: " + str(avgSec))
	# print("avgNSec: " + str(avgNSec))

	print("\nran " + executableName + " with x=" +str(xx) +" and y=" + str(yy) + " in " + str(avgSec) +" secs, " + str(avgNSec) + " nanosecs")

	experimentResults = {'seconds':str(avgSec),'nanoseconds':str(avgNSec)}
	return experimentResults

experiments = [(1,1),(100,4),(100,8),(100,11),(100,12),(100,13),(100,32),(100,64),(100,100),
		(1000,4),(1000,8),(1000,11),(1000,12),(1000,13),(1000,32),(1000,64), (1000,500), (1000,1000)]

for ex in experiments:
	# print (experiment[1])
	xx = int(ex[0])
	yy = int(ex[1])
	avgOfThree("processes.out",xx,yy)
	avgOfThree("threads.out",xx,yy)

