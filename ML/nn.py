import numpy
from sklearn.neural_network import MLPClassifier

DATA = numpy.genfromtxt('TraData2.csv', delimiter=',')
test = numpy.genfromtxt('input.csv', delimiter=',')

#2396 is best
train = DATA[0:2396 , 0:57]
train_ans = DATA[0:2396, 57:58]

clf = MLPClassifier(solver='lbfgs', alpha=1e-5,
                    hidden_layer_sizes=(4, 2), random_state=2, activation='tanh')
clf.fit(train, train_ans.ravel())
ans = clf.predict(test)

numpy.savetxt('output.csv', ans, delimiter=',', fmt='%d')
