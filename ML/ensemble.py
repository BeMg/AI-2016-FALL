import numpy
import random
from sklearn import tree
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestRegressor
from sklearn.neural_network import MLPClassifier


DATA2 = numpy.genfromtxt('TraData2.csv', delimiter=',')
DATA = numpy.genfromtxt('Random.csv', delimiter=',')
TEST = numpy.genfromtxt('input2.csv', delimiter=',')

test = TEST[0:300 , 0:57]
# test_ans = DATA[2700:3000 , 57:58]

train = DATA[0:2700 , 0:57]
train_ans = DATA[0:2700, 57:58]

train2 = DATA2[0:2396 , 0:57]
train2_ans = DATA2[0:2396, 57:58]

rf =  RandomForestRegressor(random_state=0, n_estimators=1)
rf.fit(train, train_ans.ravel())
ans_rf = rf.predict(test)

dt = tree.DecisionTreeClassifier()
dt.fit(train2, train2_ans.ravel())
ans_dt = dt.predict(test)

clf = MLPClassifier(solver='lbfgs', alpha=1e-5,
                    hidden_layer_sizes=(4, 2), random_state=2, activation='tanh')
clf.fit(train, train_ans.ravel())
ans_clf = clf.predict(test)

ans = ans_clf

for i in range(300):
    zero = 0
    one = 0
    if(ans_rf[i] == 1):
        one+=1
    else:
        zero+=1
    if(ans_dt[i] == 1):
        one+=1
    else:
        zero+=1
    if(ans_clf[i] == 1):
        one+=1
    else:
        zero+=1

    if (one > zero):
        ans[i] = 1
    else:
        ans[i] = 0

numpy.savetxt('output.csv', ans, delimiter=',', fmt='%d')

# cnt = 0
# for i in range(300):
#     if(test_ans[i] == ans[i]):
#         cnt+=1
#
# print("{}%".format(cnt/300*100))
