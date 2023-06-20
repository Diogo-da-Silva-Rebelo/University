#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
@author: miguelrocha
"""

import numpy as np
import matplotlib.pyplot as plt

from dataset import Dataset   

class LinearRegression:
    
    def __init__(self, dataset, standardize = False, regularization = False, lamda = 1):
        if standardize:
            dataset.standardize()
            self.X = np.hstack ((np.ones([dataset.nrows(),1]), dataset.Xst ))
            self.standardized = True
        else:
            self.X = np.hstack ((np.ones([dataset.nrows(),1]), dataset.X ))
            self.standardized = False
        self.y = dataset.Y
        self.theta = self.theta = np.zeros(self.X.shape[1])
        self.regularization = regularization
        self.lamda = lamda
        self.data = dataset


    def buildModel(self, dataset):
        from numpy.linalg import inv
        if self.regularization:
            self.analyticalWithReg()    
        else:
            self.theta = inv(self.X.T.dot(self.X)).dot(self.X.T).dot(self.y)
    
    def analyticalWithReg(self):
        from numpy.linalg import inv
        matl = np.zeros([self.X.shape[1], self.X.shape[1]])
        for i in range(1,self.X.shape[1]): matl[i,i] = self.lamda
        mattemp = inv(self.X.T.dot(self.X) + matl)
        self.theta = mattemp.dot(self.X.T).dot(self.y)
    
    def predict(self, instance):
        x = np.empty([self.X.shape[1]])        
        x[0] = 1
        x[1:] = np.array(instance[:self.X.shape[1]-1])

        if self.standardized:
            x[1:] = (x[1:] - self.data.mu) / self.data.sigma 
        return np.dot(self.theta, x)
    
    def costFunction(self):
        m = self.X.shape[0]
        predictions = np.dot(self.X, self.theta)
        sqe = (predictions- self.y) ** 2
        res = np.sum(sqe) / (2*m)
        return res
    
    def gradientDescent(self, iterations = 1000, alpha = 0.001):
        m = self.X.shape[0]
        n = self.X.shape[1]
        self.theta = np.zeros(n)
        if self.regularization:
            lamdas = np.zeros([self.X.shape[1]])
            for i in range(1,self.X.shape[1]): lamdas[i] = self.lamda
        for its in range(iterations):
            J = self.costFunction()
            if its%100 == 0: print(J)
            delta = self.X.T.dot(self.X.dot(self.theta) - self.y)                      
            if self.regularization:
                self.theta -= (alpha/m * (lamdas+delta))
            else: self.theta -= (alpha/m * delta )
            
    
    def standardize(self):
        self.data.standardize()
        self.X = np.hstack ((np.ones([self.data.nrows(),1]), self.data.Xst ))
        self.standardized = True
    
    def printCoefs(self):
        print(self.theta)
        
    def plotDataAndModel(self, xlab, ylab):
        plt.plot(self.X[:,1], self.y, 'rx', markersize=7)
        plt.ylabel(ylab)
        plt.xlabel(xlab)
        plt.plot(self.X[:,1], np.dot(self.X, self.theta), '-')
        plt.legend(['Training data', 'Linear regression'])
        plt.show()


def test_2var(regul = False):
    ds= Dataset("lr-example1.data")   
    
    if regul:
        lrmodel = LinearRegression(ds, True, True, 100.0) 
    else:
        lrmodel = LinearRegression(ds)
    
    print("Cost function value for theta with zeros:")
    print(lrmodel.costFunction())

    print("Model with analytical solution")
    lrmodel.buildModel(ds)  
    
    print("Cost function value for theta from analytical solution:")
    print(lrmodel.costFunction())
    # 4.477
    print("Coefficients from analytical solution")
    lrmodel.printCoefs()
    # -3.896 1.193
    lrmodel.plotDataAndModel("Population", "Profit")   
    input("Press a key")    
    
    print("Gradient descent:")
    lrmodel.gradientDescent(1500, 0.01)
    print("Cost function value for theta from gradient descent:")
    print(lrmodel.costFunction())
    print("Coefficients from gradient descent")
    lrmodel.printCoefs()
    
    lrmodel.plotDataAndModel("Population", "Profit") 
    
    input("Press a key") 
    
    ex = np.array([7.0, 0.0])
    print("Prediction for example 7:")    
    print(lrmodel.predict(ex))
    

def test_multivar():
    ds= Dataset("lr-example2.data")   
    
    lrmodel = LinearRegression(ds) 
    print("Initial cost: (not optimized)", lrmodel.costFunction())
    print()
    
    print("Analytical method:")
    lrmodel.buildModel(ds)
    print("Cost: ", lrmodel.costFunction())
    print("Coefficients:")
    lrmodel.printCoefs()     
    print("Prediction for example (3000, 3):")
    ex = np.array([3000,3,100000])
    print(lrmodel.predict(ex))

    print()
    
    print("Standardized + gradient descent:")
    lrmodel.standardize()
    print("Running GD:")
    lrmodel.gradientDescent(1000, 0.01)   
    print("FInal Cost: ", lrmodel.costFunction())
    print("Coefficients:")
    lrmodel.printCoefs()  
    print("Prediction for example (3000, 3):")
    print(lrmodel.predict(ex))
  

# main - tests
if __name__ == '__main__': 
    
    #test_2var()
    test_multivar()
    #test_2var(True)
