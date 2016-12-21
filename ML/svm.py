import numpy
from sklearn import svm

DATA = numpy.genfromtxt('TraData2.csv', delimiter=',')

idx = 0
Max_value = 0

test = DATA[2700:3000 , 0:57]
test_ans = DATA[2700:3000 , 57:58]

for j in range(200,3000):
    train = DATA[0:j , 0:57]
    train_ans = DATA[0:j, 57:58]

    clf = svm.SVC(kernel='rbf', C = 100, random_state=0, gamma = 10)

    clf.fit(train, train_ans.ravel())

    ans = clf.predict(test)

    cnt = 0
    for i in range(300):
        if(test_ans[i] == ans[i]):
            cnt+=1

    print("{}: {}%".format(j,int(cnt/300*100)))
