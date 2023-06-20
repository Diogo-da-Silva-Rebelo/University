import numpy as np
from data.dataset import Dataset

class MLP:
    
    def __init__(self, dataset, hidden_nodes = 2, normalize = False):
        self.X, self.y = dataset.getXy()
        self.X = np.hstack ( (np.ones([self.X.shape[0],1]), self.X ) ) # colocar 1's no X
        
        self.h = hidden_nodes
        self.W1 = np.zeros([hidden_nodes, self.X.shape[1]])
        self.W2 = np.zeros([1, hidden_nodes+1])
        
        if normalize:
            self.normalize()
        else:
            self.normalized = False


    def setWeights(self, w1, w2):
        self.W1 = w1
        self.W2 = w2
        

    def predict(self, instance):
        x = np.empty([self.X.shape[1]])        
        x[0] = 1
        x[1:] = np.array(instance[:self.X.shape[1]-1])
        
        if self.normalized:
            if np.all(self.sigma!= 0): 
                x[1:] = (x[1:] - self.mu) / self.sigma
            else: x[1:] = (x[1:] - self.mu)
        
        z2 = np.dot(self.W1,x)
        a2 = np.empty([z2.shape[0]+1])
        a2[0] = 1
        a2[1:]= sigmoid(z2)
        z3 = sigmoid(np.dot(self.W2,a2))
        h = sigmoid(z3)
        
        return h

    def costFunction(self):
            
        m = self.X.shape[0]
        Z2 = np.dot(self.X,self.W1.T)
        A2 = np.hstack((np.ones([Z2.shape[0],1]), sigmoid(Z2)))
        Z3 = np.dot(A2, self.W2.T)
        predictions = sigmoid(Z3)
        sqe = (predictions-self.y.reshape(m,1)) ** 2
        res = np.sum(sqe) /(2*m)
        return res

    def build_model(self):
        from scipy import optimize

        size = self.h * self.X.shape[1] + self.h+1
        
        initial_w = np.random.rand(size)        
        result = optimize.minimize(lambda w: self.costFunction(w), initial_w, method='BFGS', 
                                    options={"maxiter":1000, "disp":False} )
        weights = result.x
        self.W1 = weights[:self.h * self.X.shape[1]].reshape([self.h, self.X.shape[1]])
        self.W2 = weights[self.h * self.X.shape[1]:].reshape([1, self.h+1])

    def normalize(self):
        self.mu = np.mean(self.X[:,1:], axis = 0)
        self.X[:,1:] = self.X[:,1:] - self.mu
        self.sigma = np.std(self.X[:,1:], axis = 0)
        self.X[:,1:] = self.X[:,1:] / self.sigma
        self.normalized = True

def sigmoid(x):
  return 1 / (1 + np.exp(-x))

def test():
    ds= Dataset("xnor.data")
    nn = MLP(ds, 2)
    w1 = np.array([[-30,20,20],[10,-20,-20]])
    w2 = np.array([[-10,20,20]])
    nn.setWeights(w1, w2)
    print( nn.predict(np.array([0,0]) ) )
    print( nn.predict(np.array([0,1]) ) )
    print( nn.predict(np.array([1,0]) ) )
    print( nn.predict(np.array([1,1]) ) )
    print(nn.costFunction())

def test2():
    ds= Dataset("xnor.data")
    nn = MLP(ds, 5, normalize = False)
    nn.build_model()
    print( nn.predict(np.array([0,0]) ) )
    print( nn.predict(np.array([0,1]) ) )
    print( nn.predict(np.array([1,0]) ) )
    print( nn.predict(np.array([1,1]) ) )
    print(nn.costFunction())
    
#test()
test2()
