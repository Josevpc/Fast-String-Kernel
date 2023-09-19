import numpy as np
import pandas as pd

from sklearn.model_selection import train_test_split
from sklearn import svm

from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score

import matplotlib.pyplot as plt

kernel_df = pd.read_csv('data.csv')

DATA_SIZE = len(kernel_df)

def select_kernel(X, Y):
    kernels = np.zeros((len(X), len(Y)))
    for i, idx_X in enumerate(X):
        for j, idx_Y in enumerate(Y):
            kernels[i, j] = K[idx_X, idx_Y]
    return kernels

y = kernel_df['target'].values
X_train, X_test, y_train, y_test = train_test_split(np.arange(DATA_SIZE),y[:DATA_SIZE], test_size=0.3)

#Const
K = pd.read_csv('const_weight_kernels.csv').to_numpy()
const_clf = svm.SVC(kernel=select_kernel, probability=False)

#Bound
K = pd.read_csv('bound_weight_kernels.csv').to_numpy()
bound_clf = svm.SVC(kernel=select_kernel, probability=False)

def experiment(clf, kernel_weight):
    print('Peso ' + kernel_weight)
    clf.fit(X_train.reshape(-1,1), y_train)
    pred = clf.predict(X_test.reshape(-1,1))
    #Métricas
    #Acurácia
    print('Acurácia:', accuracy_score(y_test, pred))
    #Precision Score
    print('Precisão:', precision_score(y_test, pred))
    #Recall Score
    print('Recall:', recall_score(y_test, pred))
    #F1 Score
    print('F1:', f1_score(y_test, pred))

#Const
experiment(const_clf, 'Constante')
#Bound
experiment(bound_clf, 'Bound')