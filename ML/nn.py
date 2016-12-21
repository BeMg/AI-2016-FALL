import numpy
from sklearn.neural_network import MLPClassifier

DATA = numpy.genfromtxt('TraData2.csv', delimiter=',')

idx = 0
Max_value = 0

test = numpy.genfromtxt('input.csv', delimiter=',')
test_ans = numpy.genfromtxt('test_ans.csv', delimiter=',')

#2396 is best
train = DATA[0:2396 , 0:57]
train_ans = DATA[0:2396, 57:58]

clf = MLPClassifier(solver='lbfgs', alpha=1e-5,
                    hidden_layer_sizes=(4, 2), random_state=2, activation='tanh')

clf.fit(train, train_ans.ravel())

ans = clf.predict(test)

numpy.savetxt('output.csv', ans, delimiter=',', fmt='%d')

# cnt = 0
# for i in range(300):
#     if(test_ans[i] == ans[i]):
#         cnt+=1
#
# print("{}%".format(int(cnt/300*100)))
