import numpy as np
import math
from .model import Model
from utils.metrics import accuracy_score


class Node:
    
    """Implementation of a simple binary tree for DT classifier.

    Attributes
    ----------
    right: Node
        Right child of the node
    left: Node
        Left child of the node
    column: int
        Column index of the feature used to split the node
    threshold: float
        Threshold used to split the node
    probas: np.array
        Probabilities of each class in the node
    depth: int
        Depth of the node in the tree
    is_leaf: bool
        True if the node is a leaf, False otherwise
    """
    
    def __init__(self) -> None:
        self.right = None
        self.left = None
        self.column = None
        self.threshold = None
        self.probas = None
        self.depth = None
        self.is_leaf = False


class DecisionTree(Model):
    """
    Decision Tree class built with Nodes' class.
    The generated tree uses diferent criterions, conflict resolutions and pruning (pre/post)
    
    Parameters
    ----------
    criterion: str, optional
        Criterion used to split the nodes, defaults to 'gini'
    prun: str, optional
        Pruning method, defaults to 'pre'
    max_depth: int, optional
        Maximum depth of the tree, defaults to 3
    min_samples_leaf: int, optional
        Minimum number of samples in a leaf, defaults to 1
    min_samples_split: int, optional
        Minimum number of samples to split a node, defaults to 2
    x_test: np.array, optional
        Test set to be used for post pruning, defaults to None
    y_test: np.array, optional
        Test set labels to be used for post pruning, defaults to None
    """

    def __init__(self, criterion = 'gini',
                  prun = 'pre',
                  max_depth=3, 
                  min_samples_leaf=1, 
                  min_samples_split=2,
                  x_test = None,
                  y_test = None):
        
        super().__init__()
        self.criterion = criterion
        self.prun = prun
        self.max_depth = max_depth
        self.min_samples_leaf = min_samples_leaf
        self.min_samples_split = min_samples_split

        if prun == 'post' and (x_test is None or y_test is None):
            raise ValueError("Test set must be provided for post pruning.") 
        
        self.x_val = x_test
        self.y_val = y_test

    def node_probs(self, y):
        """
        Calculates probability of class in a given node

        Parameters
        ----------
        y: np.array
            Labels of the node
        
        Returns
        -------
        probas: np.array
            Probabilities of each class in the node
        """
        probas = []
        # for each unique label calculate the probability for it
        for one_class in self.classes:
            proba = y[y == one_class].shape[0] / y.shape[0]
            probas.append(proba)
        return np.asarray(probas)

    # gini index = 1 - sum ( prob[i]^2 ) for all i’s
    def gini(self, probas):
        """
        Calculates gini criterion

        Parameters
        ----------
        probas: np.array
            Probabilities of each class in the node

        Returns
        -------
        gini: float
            Gini criterion for the given probabilities
        """
        return 1 - np.sum(probas**2)
    
    def calc_impurity(self, y, criterion='gini'):
        """
        Calculates impurity using the specified criterion.

        Parameters
        ----------
        y: np.array
            Labels of the node
        criterion: str, optional
            Criterion used to split the nodes, defaults to 'gini'

        Returns
        -------
        impurity: float
            Impurity of the node
        
        Raises
        ------
        ValueError
            If the criterion is not valid
        
        """
        if criterion == 'gini':
            return self.gini(self.node_probs(y))
        elif criterion == 'entropy':
            return self.entropy(self.node_probs(y))
        elif criterion == 'loss':
            return self.log_loss(self.node_probs(y))
        else:
            raise ValueError(f'Invalid criterion: {criterion}')

    def entropy(self, probas):
        """
        Calculates entropy for the given probabilities.

        Parameters
        ----------
        probas: np.array
            Probabilities of each class in the node

        Returns
        -------
        entropy: float
            Entropy of the node
        """
        entropy = 0
        for p in probas:
            if p != 0:
                entropy -= p * math.log(p, 2)
        return entropy

    def log_loss(self, probas):
        """
        Calculates log loss for the given probabilities.

        Parameters
        ----------
        probas: np.array
            Probabilities of each class in the node
        
        Returns
        -------
        log_loss: float
            Log loss of the node
        """
        log_loss = 0
        for p in probas:
            if p == 0:
                log_loss += 1000 # To avoid division by 0
            elif p == 1:
                log_loss += 0
            else:
                log_loss -= math.log(p, 2)
        return log_loss

    def fit(self, dataset):

        self.dataset = dataset
        X, y = dataset.get_X(), dataset.get_y()
        self.classes = np.unique(y)
        self.tree = Node()
        self.tree.depth = 1
        self.tree.probas = self.node_probs(y)
        self.build_tree(X, y, self.tree)
        self.is_fitted = True

    def find_best_split(self, X_idx, y):
       """
    Calculates the best possible split for the concrete node of the tree

        Parameters
        ----------
            X_idx: np.array
                Features of the node
            y: np.array
                Labels of the node

        Returns
        -------
            best_col: int
                Index of the best feature to split the node
            best_thr: int
                Threshold of the best feature to split the node
            x_left: np.array
                Features of the left child
            x_right: np.array
                Features of the right child
            y_left: np.array
                Labels of the left child
            y_right: np.array
                Labels of the right child
       """

       y = np.array(y, dtype=np.int64)

       best_col = None 
       best_thr = None
       best_info_gain = -np.inf

       previous_impurity = self.calc_impurity(y)

       for col in range(X_idx.shape[1]):
           x_col = X_idx[:, col]

           for x_i in x_col:
               threshold = x_i
               left_idx, right_idx = y[x_col <= threshold], y[x_col > threshold]

               if left_idx.shape[0] == 0 or right_idx.shape[0] == 0:
                   continue

               # Calculate impurity for current split
               right_impurity = self.calc_impurity(right_idx)
               left_impurity = self.calc_impurity(left_idx)
               info_gain = previous_impurity
               info_gain -= (left_impurity * left_idx.shape[0] / left_idx.shape[0]) + (right_impurity * right_idx.shape[0] / y.shape[0])

               if info_gain > best_info_gain:
                   best_col = col
                   best_thr = threshold
                   best_info_gain = info_gain

               if best_info_gain == -np.inf:
                   return None, None, None, None, None, None

               x_col = X_idx[:, best_col]
               x_left, x_right = X_idx[x_col <= best_thr, :], X_idx[x_col > best_thr, :]
               y_left, y_right = y[x_col <= best_thr], y[x_col > best_thr]

       return best_col, best_thr, x_left, y_left, x_right, y_right

    def build_tree(self, X, y, node):
        """
        Builds the decision tree using the specified criterion, conflict resolution and pruning method.

        Parameters
        ----------
        X: np.array
            Features of the node
        y: np.array
            Labels of the node
        node: Node
            Node of the tree
        """
    
        # Stop condition - leaf node
        if X.shape[0] < self.min_samples_split or node.depth >= self.max_depth or np.unique(y).shape[0] == 1:
            node.is_leaf = True
            return
    
        # Splitting using specified criterion
        best_col, best_thr, x_left, y_left, x_right, y_right = self.find_best_split(X, y)
      
        if best_col is None:
            node.is_leaf = True

        if node.threshold is None:
            node.is_leaf = True

        # Create node and recursively build subtrees
        node.column = best_col
        node.threshold = best_thr
    
        # Create left and right child nodes
        node.left = Node()
        node.left.depth = node.depth + 1
        node.left.probas = self.node_probs(y_left)
    
        node.right = Node()
        node.right.depth = node.depth + 1
        node.right.probas = self.node_probs(y_right)
    
        # Split recursively
        self.build_tree(x_right, y_right, node.right)
        self.build_tree(x_left, y_left, node.left)
    
        # Stop condition - post-pruning
        if self.prun == 'post':
            self.is_fitted = True
            # Prune the tree
            while not node.is_leaf:
                # Store the current state of the tree
                old_left = node.left
                old_right = node.right
                old_is_leaf = node.is_leaf

                # Prune the left subtree
                node.left = Node()
                node.left.depth = old_left.depth
                node.left.probas = self.node_probs(y_left)
                node.left.is_leaf = True

                # Prune the right subtree
                node.right = Node()
                node.right.depth = old_right.depth
                node.right.probas = self.node_probs(y_right)
                node.right.is_leaf = True

                # Check the accuracy of the pruned tree on the validation set
                accuracy = accuracy_score(self.predict(self.x_val), self.y_val)

                # If the pruned tree is worse, restore the old state and stop pruning
                if accuracy < self.best_accuracy:
                    node.left = old_left
                    node.right = old_right
                    node.is_leaf = old_is_leaf
                    break
                
                # If the pruned tree is better, update the best accuracy and continue pruning
                self.best_accuracy = accuracy
                node.is_leaf = True

    def predict_sample(self, x, node):
        '''
        Passes one object through decision tree and return the probability of 
        it to belong to each class

        Parameters
        ----------
        x: np.array
            Object to predict
        node: Node
            Node of the tree

        Returns
        -------
        probas: np.array
            Probability of the object to belong to each class
        '''
        assert self.is_fitted, 'Model must be fit before predicting'
        # if we have reached the terminal node of the tree
        if node.is_leaf:
            return node.probas
        
        indices = np.where(x[node.column] > node.threshold)[0]

        if len(indices) > 0:
            probas = self.predict_sample(x, node.right)
        else:
            probas = self.predict_sample(x, node.left)
        return probas

    def predict(self, x):
        '''
        Passes objects through decision tree and return the predicted class
        
        Parameters
        ----------
        x: np.array
            Objects to predict
        
        Returns
        -------
        preds: np.array
            Predicted classes
        '''
        
        assert self.is_fitted, 'Model must be fit before predicting'
        preds = []
        for i in range(x.shape[0]):
            pred = np.argmax(self.predict_sample(x[i], self.tree))
            preds.append(pred)
        return np.array(preds, dtype=float)

    