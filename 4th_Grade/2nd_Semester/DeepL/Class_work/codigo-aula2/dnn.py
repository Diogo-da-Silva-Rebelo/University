import numpy as np
from dataset import Dataset

# Funções de ativação
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    return sigmoid(x) * (1 - sigmoid(x))

def relu(x):
    return np.maximum(0, x)

def relu_derivative(x):
    return np.where(x > 0, 1, 0)

def tanh(x):
    return np.tanh(x)

def tanh_derivative(x):
    return 1 - np.tanh(x)**2

# classe intermédia da camada
class DenseLayer:
    def __init__(self, input_size, output_size, activation=sigmoid):
        self.input_size = input_size
        self.output_size = output_size
        self.activation = activation
        self.W = np.random.randn(input_size, output_size) * 0.01
        self.b = np.zeros(output_size)
        
    def forward(self, X):
        self.X = X
        self.Z = np.dot(X, self.W) + self.b
        if self.Z.ndim == 1: self.Z = self.Z.reshape(1, -1)
        self.A = self.activation(self.Z)
        return self.A

# classe da rede enuronal
class NN:
    def __init__(self, layers, epochs=1000, learning_rate=0.01, loss='mse', loss_derivative='mse_derivative', verbose=False):
        self.layers = layers
        self.epochs = epochs
        self.learning_rate = learning_rate
        self.loss = loss
        self.loss_derivative = loss_derivative
        self.verbose = verbose
        
    def fit(self, X, y):
        self.losses = []
        for i in range(self.epochs):
            # Forward propagation
            output = X
            for layer in self.layers:
                output = layer.forward(output)

            # Compute loss
            loss = self._loss(y, output)
            self.losses.append(loss)


            if self.verbose and i % (self.epochs // 10) == 0:
                print(f"Epoch {i}/{self.epochs}, loss = {loss}")

    def predict(self, X):
        output = X
        for layer in self.layers:
            output = layer.forward(output)
        return output
    
    def _loss(self, y_true, y_pred):
        if self.loss == 'mse':
            return np.mean((y_true - y_pred)**2)
        elif self.loss == 'entropy':
            return -np.sum(y_true * np.log2(y_pred))
        else:
            raise ValueError("Função de loss não suportada")
            
    def _loss_derivative(self, y_true, y_pred):
        if self.loss_derivative == 'mse_derivative':
            return 2 * (y_pred - y_true) / len(y_true)
        elif self.loss_derivative == 'entropy_derivative':
            return - y_true / y_pred / np.log(2)
        else:
            raise ValueError("Função de derivada de loss não suportada")
    
def test_NN_MSE():
    # Define o conjunto de dados
    dataset = Dataset(filename="xnor.data")
    
    # Define a rede neural com 2 camadas densas, uma camada de entrada com 2 neurónios, uma camada oculta com 3 neurónios e uma camada de saída com 1 neurónio
    nn = NN(layers=[DenseLayer(2, 3, sigmoid),
            DenseLayer(3, 2, sigmoid),
            DenseLayer(2, 1, sigmoid)], # também se pode utilizar diferentes funções de ativação
            epochs=1000, 
            learning_rate=0.01, 
            loss='mse', # usar 'entropy' como alternativa
            loss_derivative='mse_derivative', verbose=True) # usar 'entropy_derivative' como alternativa
    
    # Treina a rede neural
    nn.fit(dataset.X, dataset.Y)
    
    # Faz a previsão usando a rede neural treinada
    X_test = dataset.X
    y_pred = nn.predict(X_test)
    
    print("\nPrevisões:")
    print(y_pred)

test_NN_MSE()