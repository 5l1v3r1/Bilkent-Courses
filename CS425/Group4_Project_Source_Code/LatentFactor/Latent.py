import numpy as np
import pandas as pd

def latent_factor(initial_matrix, rand_P_matrix, rand_Q_matrix, numFeature):
    numStep = 1000
    SGD_A = 0.02
    SGD_B = 0.02

    rand_Q_matrix = rand_Q_matrix.transpose()
    for m in range(0, numStep):
        for l in range(0, len(initial_matrix)):
            for n in range(0, len(initial_matrix[l])):
                multMat = np.dot(rand_P_matrix[l, :], rand_Q_matrix[:, n])
                matValue= initial_matrix[l][n]

                if matValue > 0:
                    temp = matValue - multMat
                    for feature in range(0, numFeature):
                        rand_P_matrix[l][feature] = rand_P_matrix[l][feature] + SGD_A * (2 * temp * rand_Q_matrix[feature][n] - SGD_B * rand_P_matrix[l][feature])
                        rand_Q_matrix[feature][n] = rand_Q_matrix[feature][n] + SGD_A * (2 * temp * rand_P_matrix[l][feature] - SGD_B * rand_Q_matrix[feature][n])
        temp2 = 0
        for i in range(0, len(initial_matrix)):
            for j in range(0, len(initial_matrix[i])):
                multMat = np.dot(rand_P_matrix[i, :], rand_Q_matrix[:, j])
                matValue = initial_matrix[i][j]

                if matValue > 0:
                    temp2 = temp2 + pow(matValue - multMat, 2)
                    for feature in range(0, numFeature):
                        PVal = rand_P_matrix[i][feature]
                        QVal = rand_Q_matrix[feature][j]
                        temp2 = temp2 + (SGD_B/2) * (pow(PVal,2) + pow(QVal,2))
        if temp2 < 0.001:
            break
    return rand_P_matrix, rand_Q_matrix.transpose()

data = pd.read_csv('ratings.csv')
main_data = data.iloc[:, :].values

mov_data = pd.read_csv('movies.csv')
movie_data = mov_data.iloc[:, :].values

numFeature = 19
index = main_data[:,1]
index2 = movie_data[:,0]
names = movie_data[:,1]

userNum = input("Enter a user number to proceed: ")

fac = np.zeros(shape=(1,27278))
rowNum = len(fac)
colNum = len(fac[0])
rand_P_matrix = np.random.rand(rowNum,numFeature)
rand_Q_matrix = np.random.rand(colNum,numFeature)

prevOne = userNum
a = 0
initIndex = 0
for i in range(0, len(main_data)):
    if (main_data[i][0] == prevOne):
        a = a + 1
        if (initIndex == 0 and prevOne != 1):
            initIndex = i

indexler = np.empty(shape=a)

x = 0
for i in range(initIndex, initIndex + a):
    inde = np.nonzero(index[i]== index2)[0][0]
    indexler[x] = inde
    x = x + 1
    k = main_data[i][2]

    fac[0][inde] = k

reg_P_matrix, reg_Q_matrix = latent_factor(fac, rand_P_matrix, rand_Q_matrix, numFeature)
result = np.dot(reg_P_matrix, reg_Q_matrix.transpose())

recommended = (-result).argsort()[:1000]

print("")
count = 0
for i in range(0, len(recommended[0])):
    k = recommended[0][i]
    if k not in indexler and count != 250:
        print("Movie {} with movie id {} is recommended to user {} with rating {}. ".format(names[k],index2[k],prevOne,result[0][k]))
        count = count + 1
