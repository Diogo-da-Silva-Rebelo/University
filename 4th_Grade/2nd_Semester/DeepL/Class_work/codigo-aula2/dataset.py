#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import numpy as np

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
        
    def readDataset(self,filename, sep = ","):
        data = np.genfromtxt(filename, delimiter=sep)
        self.X = data[:,0:-1]
        self.Y = data[:,-1]
        
    def writeDataset(self, filename, sep = ","):
        fullds = np.hstack( (self.X, self.Y.reshape(len(self.Y),1)))
        np.savetxt(filename, fullds, delimiter = sep)
        
    def getXy (self):
        return self.X, self.Y
    
    # função de normalização
    def normalize(self):
        self.mu = np.mean(self.X[:,1:], axis = 0)
        self.X[:,1:] = self.X[:,1:] - self.mu
        self.sigma = np.std(self.X[:,1:], axis = 0)
        self.X[:,1:] = self.X[:,1:] / self.sigma
        self.normalized = True

   