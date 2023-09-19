import ctypes
import numpy as np
import pandas as pd

import data

#Use isso para selecionar o número de amostras e selecionalas randomicamente do dataset e criar a base de dados que vai ser utilizada
#data.make_csv('test', 1000)


#Lendo a base de dados com as sequências marcadas como alvo ou não
sequence_df = pd.read_csv('data.csv')
SIZE = int(len(sequence_df))

#Usando a biblioteca do C com ctypes
c_wrapper = ctypes.CDLL("src/fast_string_kernel.so")

c_wrapper.FAST_STRING_KERNEL.restype = ctypes.c_double

#Definição da função do Fast String Kernel
def fast_string_kernel(X, Y, weight, aux):
    for i in range(len(X)):
        if(weight == 'bound'):
            aux = len(X[i])
        for j in range(len(Y)):
            #Cálculo da distância entre os objetos
            K[i, j] = c_wrapper.FAST_STRING_KERNEL(X[i].encode('utf-8'), Y[j].encode('utf-8'), weight.encode('utf-8'), ctypes.c_float(aux))
    return K

K = np.zeros([SIZE, SIZE])

kernel_weight = 'const'

K = fast_string_kernel(sequence_df.iloc[:,0], sequence_df.iloc[:,0], kernel_weight, 0)

K_df = pd.DataFrame(data=K)
K_df.to_csv(kernel_weight+'_weight_kernels.csv', index=False)
