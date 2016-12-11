import numpy
from sklearn.neural_network import MLPClassifier

DATA = numpy.genfromtxt('TraData2.csv', delimiter=',')


test = DATA[2700:3000 , 0:57]
test_ans = DATA[2700:3000 , 57:58]

train = DATA[0:2700 , 0:57]
train_ans = DATA[0:2700, 57:58]

clf = MLPClassifier(solver='lbfgs', alpha=1e-5,
                    hidden_layer_sizes=(4, 2), random_state=2, activation='tanh')

clf.fit(train, train_ans.ravel())

ans = clf.predict(test)


cnt = 0
for i in range(300):
    if(test_ans[i] == ans[i]):
        cnt+=1

print(int(cnt/300*100))
