from numpy import genfromtxt
from sklearn.neural_network import MLPClassifier

DATA = genfromtxt('TraData2.csv', delimiter=',')
test_data = DATA[2700:3000, 0:57]
test_ans = DATA[2700:3000, 57:58]

for i in range(1, 50):
    lower = 0
    size = int(2700 / i)
    upper = size

    ans = []

    for j in range(0, i):
        data = DATA[lower:upper, 0:57]
        data_ans = DATA[lower:upper, 57:58]

        lower += size
        upper += size

        clf = MLPClassifier(solver='lbfgs', alpha=1e-5,
                            hidden_layer_sizes=(1, 2), random_state=1, activation='logistic')

        clf.fit(data, data_ans.ravel())
        ans.append(clf.predict(test_data))

    cnt = 0

    for j in range(300):
        Y = 0
        N = 0
        result = 0
        for k in range(0, i):
            if ans[k][j] == 1:
                Y += 1
            else:
                N += 1
            pass
        if Y > N:
            result = 1

        if result == test_ans[j]:
            cnt+=1

    print("{}: {}: {}".format(i, int(cnt / 3), size))
