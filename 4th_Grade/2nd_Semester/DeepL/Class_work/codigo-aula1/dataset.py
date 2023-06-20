#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@author: miguelrocha (docente)
@author: Diogo Rebelo, PG50327
"""

import random
import numpy as np
import matplotlib.pyplot as plt

class Dataset:
    
    # constructor
    def __init__(self, filename = None, X = None, Y = None):
        if filename is not None:
            self.readDataset(filename)
        elif X is not None and Y is not None:
            self.X = X
            self.Y = Y
        else:
            self.X = None
            self.Y = None
        
        self.Xst = None
        
    def readDataset(self, filename, sep = ","):
        data = np.genfromtxt(filename, delimiter=sep)
        self.X = data[:,0:-1]
        self.Y = data[:,-1]
        
    def getXy (self):
        return self.X, self.Y
    
    def nrows(self):
        return self.X.shape[0]
    
    def ncols(self):
        return self.X.shape[1]
    
    def standardize(self):
        self.mu = np.mean(self.X, axis = 0)
        self.Xst = self.X - self.mu
        self.sigma = np.std(self.X, axis = 0)
        self.Xst = self.Xst / self.sigma
    
    def plotData2vars(self, xlab, ylab, standardized = False):
        if standardized:
            plt.plot(self.Xst, self.Y, 'rx', markersize=7)
        else:
            plt.plot(self.X, self.Y, 'rx', markersize=7)
        plt.ylabel(ylab)
        plt.xlabel(xlab)
        plt.show()
    
    def plotBinaryData(self):
        negatives = self.X[self.Y == 0]
        positives = self.X[self.Y == 1]
        plt.xlabel("x1")
        plt.ylabel("x2")
        plt.xlim([self.X[:,0].min(), self.X[:,0].max()])
        plt.ylim([self.X[:,0].min(), self.X[:,0].max()])
        plt.scatter( negatives[:,0], negatives[:,1], c='r', marker='o', linewidths=1, s=40, label='y=0' )
        plt.scatter( positives[:,0], positives[:,1], c='k', marker='+', linewidths=2, s=40, label='y=1' )
        plt.legend()
        plt.show()
    
    # nova função de divisão em treino/teste
    def train_test_split(self, test_size):
        test_size = int(test_size * self.nrows())
        train_size = self.nrows() - test_size
        idx = np.arange(self.nrows())
        np.random.shuffle(idx)
        train_idx = idx[:train_size]
        test_idx = idx[train_size:]

        # Atribuir os datasets às variáveis de instância
        X_train, y_train = self.X[train_idx], self.Y[train_idx]
        X_test, y_test = self.X[test_idx], self.Y[test_idx]
       
        return Dataset(X=X_train, Y=y_train), Dataset(X=X_test, Y=y_test)


if __name__ == "__main__":
    def test():
        d = Dataset("lr-example1.data")
        d.plotData2vars("Population", "Profit")
        print(d.getXy())
    
    def testStandardized():
        d = Dataset("lr-example1.data")
        d.standardize()
        d.plotData2vars("Population", "Profit", True)
        print(d.getXy())
    
    def testBinary():
        ds= Dataset("log-ex1.data")   
        ds.plotBinaryData()   
        
    def testBinary2():
        ds= Dataset("log-ex2.data")   
        ds.plotBinaryData()   
    
    test()
    #testStandardized()   
    #testBinary()
    #testBinary2()
