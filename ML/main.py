from numpy import genfromtxt
from sklearn import svm

ALL_DATA = genfromtxt('TraData.csv', delimiter=',')


train = ALL_DATA[0:1500, 0:57]
train_ans = ALL_DATA[0:1500, 57:58]

test = ALL_DATA[1500:3000, 0:57]
test_ans = ALL_DATA[1500:3000, 57:58]

clf = svm.SVC()
clf.fit(train, train_ans)

ans = clf.predict(test)

cnt = 0

for i in range(1500):
    if(ans[i] == test_ans[i]):
        cnt+=1;


print(cnt/1500)
