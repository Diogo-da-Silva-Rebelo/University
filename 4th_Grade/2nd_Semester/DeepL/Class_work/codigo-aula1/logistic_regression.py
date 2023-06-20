# -*- coding: utf-8 -*-
"""
@author: miguelrocha (docente)
@author: Diogo Rebelo, PG50327
"""

import numpy as np
from dataset import Dataset
import matplotlib.pyplot as plt
import argparse

class LogisticRegression:
    
    def __init__(self, dataset, standardize = False, regularization = False, lamda = 1):
        if standardize:
            dataset.standardize()
            self.X = np.hstack ((np.ones([dataset.nrows(),1]), dataset.Xst ))
            self.standardized = True
            self.sigma = dataset.sigma
        else:
            self.X = np.hstack ((np.ones([dataset.nrows(),1]), dataset.X ))
            self.standardized = False
            self.sigma = None
            
        self.y = dataset.Y
        self.theta = np.zeros(self.X.shape[1])
        self.regularization = regularization
        self.lamda = lamda
        self.data = dataset
            

    def printCoefs(self):
        print(self.theta)

    # completado na aula
    def probability(self, instance):
        x = np.empty([self.X.shape[1]])
        x[0] = 1
        x[1:] = np.array(instance[:self.X.shape[1]-1])
        if self.standardized:
            if np.all(self.sigma!= 0): 
                x[1:] = (x[1:] - self.data.mu) / self.data.sigma
            else: x[1:] = (x[1:] - self.mu) 
        return np.dot(self.theta,x)

    # completado na aula
    def predict(self, instance):
        p = self.probability(instance)
        if p>0.5: res = 1
        else: res = 0
        return res
    
    # nova função TPC
    def predict_values(self, X):
        m = X.shape[0]
        p = np.zeros(m)
        for i in range(m):
            p[i] = self.predict(X[i,:])
        return p


    # nova função TPC
    def calculate_accuracy(self, predicted_labels, true_labels):
        num_correct = sum([1 if predicted_labels[i] == true_labels[i] else 0 for i in range(len(predicted_labels))])
        num_total = len(predicted_labels)
        accuracy = num_correct / num_total
        return accuracy

    # completado na aula
    def costFunction(self, theta = None):
        epsilon = 1e-10
        if theta is None: theta = self.theta
        m = self.X.shape[0]
        # predictions
        p = sigmoid(np.dot(self.X, theta))
        # cost function
        # cost = (-self.y * np.log(p) - (1-self.y) * np.log(1-p)) / m
        # res = np.sum(cost) / m
        J = -1/m * (np.dot(self.y.T, np.log(p+epsilon)) + np.dot((1-self.y).T, np.log(1-p+epsilon)))
        return J
        

    # completado na aula regularização L2
    def costFunctionReg(self, theta = None, lamda = 1):
        if theta is None: theta= self.theta
        m = self.X.shape[0]
        p = sigmoid ( np.dot(self.X, theta) )
        cost = (-self.y * np.log(p) - (1-self.y) * np.log(1-p) )
        reg = np.dot(theta[1:], theta[1:]) * lamda / (2*m)
        return (np.sum(cost) / m) + reg

    # completado na aula
    def gradientDescent(self, alpha = 0.01, iters = 10000):
        m = self.X.shape[0]
        n = self.X.shape[1]
        self.theta = np.zeros(n)  
        for its in range(iters):
            J = self.costFunction()
            if its%1000 == 0: 
                print(J)
            delta = self.X.T.dot(sigmoid(self.X.dot(self.theta))-self.y)
            self.theta -= (alpha/m*delta)

    # alterei para ser mais intuitivo (recebe o número de iterações máximo)
    def buildModel(self, maxiter = 500):
        if self.regularization == False:
            self.optim_model(maxiter)
        else:
            self.optim_model_reg(self.lamda, maxiter)


    def optim_model(self, maxiter = 500):
        from scipy import optimize

        n = self.X.shape[1]
        options = {'full_output': True, 'maxiter': maxiter}
        initial_theta = np.zeros(n)
        self.theta, _, _, _, _ = optimize.fmin(lambda theta: self.costFunction(theta), initial_theta, **options)
    
    def optim_model_reg(self, lamda, maxiter):
        from scipy import optimize

        n = self.X.shape[1]
        initial_theta = np.ones(n)        
        result = optimize.minimize(lambda theta: self.costFunctionReg(theta, lamda), initial_theta, method='BFGS', options={"maxiter":maxiter, "disp":False} )
        self.theta = result.x    
  

    def mapX(self):
        self.origX = self.X.copy()
        mapX = mapFeature(self.X[:,1], self.X[:,2], 6)
        self.X = np.hstack((np.ones([self.X.shape[0],1]), mapX) )
        self.theta = np.zeros(self.X.shape[1])


    # alterada para lidar com divisão por 0
    def plotModel(self):
        from numpy import r_
        pos = (self.y == 1).nonzero()[:1]
        neg = (self.y == 0).nonzero()[:1]
        plt.plot(self.X[pos, 1].T, self.X[pos, 2].T, 'k+', markeredgewidth=2, markersize=7)
        plt.plot(self.X[neg, 1].T, self.X[neg, 2].T, 'ko', markerfacecolor='r', markersize=7)
        #if self.X.shape[1] <= 3:
        plot_x = r_[self.X[:,2].min(),  self.X[:,2].max()]
        if self.theta[2] == 0:
            plot_y = np.ones(plot_x.shape) * np.mean(self.X[:,2])
        else:
            plot_y = (-1./self.theta[2]) * (self.theta[1]*plot_x + self.theta[0])
        plt.plot(plot_x, plot_y)
        plt.legend(['class 1', 'class 0', 'Decision Boundary'])
        plt.show()


    def plotModel2(self):
        negatives = self.origX[self.y == 0]
        positives = self.origX[self.y == 1]
        plt.xlabel("x1"); plt.ylabel("x2")
        plt.xlim([self.origX[:,1].min(), self.origX[:,1].max()])
        plt.ylim([self.origX[:,1].min(), self.origX[:,1].max()])
        plt.scatter( negatives[:,1], negatives[:,2], c='r', marker='o', linewidth=1, s=40, label='y=0' )
        plt.scatter( positives[:,1], positives[:,2], c='k', marker='+', linewidth=2, s=40, label='y=1' )
        plt.legend()

        u = np.linspace( -1, 1.5, 50 )
        v = np.linspace( -1, 1.5, 50 )
        z = np.zeros( (len(u), len(v)) )

        for i in range(0, len(u)): 
            for j in range(0, len(v)):
                x = np.empty([self.X.shape[1]])  
                x[0] = 1
                mapped = mapFeature( np.array([u[i]]), np.array([v[j]]) )
                x[1:] = mapped
                z[i,j] = x.dot( self.theta )
        z = z.transpose()
        u, v = np.meshgrid( u, v )	
        plt.contour( u, v, z, [0.0, 0.001])
        plt.show()


def sigmoid(x):
    return 1 / (1 + np.exp(-x))
    
  
def mapFeature(X1, X2, degrees = 6):
     out = np.ones( (np.shape(X1)[0], 1) )
     for i in range(1, degrees+1):
         for j in range(0, i+1):
             term1 = X1 ** (i-j)
         term2 = X2 ** (j)
         term  = (term1 * term2).reshape( np.shape(term1)[0], 1 ) 
         out   = np.hstack(( out, term ))
     return out  
 
# main - tests
def test():
    #Teste com o dataset "log-ex1.data"
    
    ds= Dataset("log-ex1.data")   
    logmodel = LogisticRegression(ds)
    logmodel.plotModel()
    print ("Initial cost: ", logmodel.costFunction())
    # result: 0.693

    logmodel.gradientDescent(0.002, 200000)
    
    #logmodel.optim_model()
    
    logmodel.plotModel()
    print ("Final cost:", logmodel.costFunction())
    
    ex = np.array([45,65])
    print ("Prob. example:", logmodel.probability(ex))
    print ("Pred. example:", logmodel.predict(ex))


def testreg():
    ds= Dataset("log-ex2.data")   
       
    logmodel = LogisticRegression(ds)
    logmodel.plotModel()
    logmodel.mapX()
    logmodel.printCoefs()

    print (logmodel.costFunctionReg())
    logmodel.optim_model_reg(0.1)
    logmodel.printCoefs()
    print (logmodel.costFunctionReg())
    logmodel.plotModel2()    

# nova função
# sem reg. (teste que usa GD para estimar parâmetros e experimenta sem otimização de descida máxima de modelo. Dados standardizados.)
def test_hearts_noOp(dataset):
    # Teste com o dataset "hearts-bin.data"
    hearts_data = Dataset(dataset)
    # divisão em dataset de treino e teste (em Notação Matricial)
    train_data, test_data = hearts_data.train_test_split(0.3)
    print(f"Train set has {train_data.nrows()} rows and {train_data.ncols()} columns")
    print(f"Test set has {test_data.nrows()} rows and {test_data.ncols()} columns\n")


    print("No Regularization.")
    print("No Optimization of GD.")
    print("Standardized Data.")
    test_data.standardize()
    print("Aplying Logistic Regression: ")
    log_model = LogisticRegression(train_data, True, False) # para evitar valores nulos
    print("Initial Cost (not optimized):", log_model.costFunction())
    log_model.plotModel()

    # estimação de parâmetros com GD
    print("Running GD:")
    log_model.gradientDescent(alpha=0.02, iters=15000)
    print(f"Final Cost (with GD): {log_model.costFunction()}")
    # print(log_model.printCoefs())

    # criar array de previsões
    pred_1 = log_model.predict_values(test_data.X)
    y_test = test_data.Y
    acc = log_model.calculate_accuracy(y_test, pred_1) 
    print(f"Accuracy Score: {round(acc, 4)}")
    log_model.plotModel()


# nova função
# sem reg. (teste que usa GD para estimar parâmetros e experimenta com otimização de descida máxima do modelo. Dados standardizados.)
def test_hearts_op(dataset):
    # Teste com o dataset "hearts-bin.data"
    hearts_data = Dataset(dataset)
    # divisão em dataset de treino e teste (em Notação Matricial)
    train_data, test_data = hearts_data.train_test_split(0.3)
    print(f"Train set has {train_data.nrows()} rows and {train_data.ncols()} columns")
    print(f"Test set has {test_data.nrows()} rows and {test_data.ncols()} columns\n")

    print("No Regularization.")
    print("With Optimization of GD.")
    print("Standardized Data.")
    test_data.standardize()
    print("Aplying Logistic Regression: ")
    log_model = LogisticRegression(train_data, True, False) # para evitar valores nulos
    print("Initial Cost (not optimized):", log_model.costFunction())
    log_model.plotModel()

    # otimizar modelo
    log_model.buildModel(15000) # alterar maxiter consoante o necessário
    print("Final Cost (GD optimized):", log_model.costFunction())

    # criar array de previsões
    pred_1 = log_model.predict_values(test_data.X)
    y_test = test_data.Y
    acc = log_model.calculate_accuracy(y_test, pred_1) 
    print(f"Accuracy Score: {round(acc, 4)}")
    log_model.plotModel()


# nova função
# com reg. (Usa-se reg L2 com o algoritmo de otimização de segunda ordem BFGS (estimar e otimizar pesos))
def test_hearts_reg(dataset):
    # teste com o dataset "hearts-bin.data"
    hearts_data = Dataset(dataset)
    # divisão em dataset de treino e teste (em Notação Matricial)
    train_data, test_data = hearts_data.train_test_split(0.2)
    print(f"Train set has {train_data.nrows()} rows and {train_data.ncols()} columns")
    print(f"Test set has {test_data.nrows()} rows and {test_data.ncols()} columns\n")

    regularization_values = [0, 0.1, 1, 10, 100] # lista de valores de lambda a serem testados
    
    print("With Regularization.")
    print("Standardized Data.")
    test_data.standardize()
    print("Aplying Logistic Regression: ")

    scores = []

    # aplica regularização para os diferentes lamdas
    for lamda in regularization_values:
        print(f"Regularization (lambda={lamda}):")
        log_model = LogisticRegression(train_data, True, True, lamda)
        log_model.buildModel(maxiter=15000) # alterar maxiter consoante o necessário
        print("Final Cost : ", log_model.costFunctionReg()) 

        # criar array de previsões
        pred_2 = log_model.predict_values(test_data.X)
        y_test = test_data.Y
        acc = log_model.calculate_accuracy(y_test, pred_2) 
        print(f"Accuracy Score: {round(acc, 4)}")
        print("="*60)
        log_model.plotModel()
        scores.append(acc)

    # Plota o gráfico dos scores em função dos valores de lambda
    plt.plot(regularization_values, scores)
    plt.xlabel("Lambda values")
    plt.ylabel("Accuracy Score")
    plt.show()
    
# função principal
# como correr:
"""
- Sem regularização & Sem Otimização Nelder-Mead: comando: python3 logistic_regression.py <dataset> noReg noOp;
- Sem regularização & Com Otimização Nelder-Mead: comando: python3 logistic_regression.py <dataset> noReg op;
- Com regularização: comando: python3 logistic_regression.py <dataset> reg.
"""
def main():
    parser = argparse.ArgumentParser(description='Processa um dataset com Regressão Logística com ou sem Regularização')
    parser.add_argument('dataset', help='Nome do dataset a ser processado')
    parser.add_argument('flag_de_regularizacao', choices=['reg', 'noReg'], help='Com ou sem regularização')
    parser.add_argument('flag_de_otimizacao', choices=['op', 'noOp'], nargs = '?', help='Com ou sem otimização na descida máxima')
    
    args = parser.parse_args()

   # Verifica se a opção de otimização é usada apenas com regularização desativada
    if args.flag_de_regularizacao == 'reg' and ((args.flag_de_otimizacao == 'op') or (args.flag_de_otimizacao == 'noOp')):
        parser.error('A opção de otimização só pode ser usada com regularização desativada (noReg)')

    if args.flag_de_regularizacao == 'noReg':
        # Sem regularização
        if args.flag_de_otimizacao == 'op':
            test_hearts_op(args.dataset)
        elif args.flag_de_otimizacao == 'noOp':
            test_hearts_noOp(args.dataset)
        else:
            parser.error('Flag de otimização não reconhecida')
    else:
        # Com regularização
        test_hearts_reg(args.dataset)


if __name__ == '__main__':
    main()
