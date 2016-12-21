import numpy
import random
from sklearn import tree
from sklearn.preprocessing import StandardScaler

DATA = numpy.genfromtxt('TraData.csv', delimiter=',')
random.shuffle(DATA)
test = DATA[2700:3000 , 0:57]
test_ans = DATA[2700:3000 , 57:58]

train = DATA[0:2400 , 0:57]
train_ans = DATA[0:2400, 57:58]

scaler = StandardScaler()
scaler.fit(train)
train = scaler.transform(train)
test = scaler.transform(test)

rf = tree.DecisionTreeClassifier()
rf.fit(train, train_ans.ravel())
ans = rf.predict(test)

numpy.savetxt('ans.csv',ans,delimiter=',')
cnt = 0
for i in range(300):
    if(test_ans[i] == ans[i]):
        cnt+=1
cnt = cnt/3
print(cnt)
