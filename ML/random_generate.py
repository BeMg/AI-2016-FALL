import numpy

DATA = numpy.genfromtxt('TraData.csv', delimiter=',')

numpy.random.shuffle(DATA)

numpy.savetxt("test.csv", DATA[0:300 , 0:57], delimiter=',', fmt='%f')
numpy.savetxt("test_ans.csv", DATA[0:300 , 57:58], delimiter=',', fmt='%d')
