import numpy
import random
from sklearn import tree
from sklearn.preprocessing import StandardScaler

DATA = numpy.genfromtxt('TraData.csv', delimiter=',')
random.shuffle(DATA)

test = numpy.genfromtxt('input.csv', delimiter=',')
test_ans = numpy.genfromtxt('output.csv', delimiter=',')

train = DATA[0:2400 , 0:57]
train_ans = DATA[0:2400, 57:58]

# scaler = StandardScaler()
# scaler.fit(train)
# train = scaler.transform(train)
# test = scaler.transform(test)

rf = tree.DecisionTreeClassifier()
rf.fit(train, train_ans.ravel())
ans = rf.predict(test)

cnt = 0
for i in range(300):
    if(test_ans[i] == ans[i]):
        cnt+=1
cnt = cnt/3
print(cnt)
