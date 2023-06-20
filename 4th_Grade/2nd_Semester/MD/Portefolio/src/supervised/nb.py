import numpy as np
import math
from .model import Model
from utils.metrics import accuracy_score


class NaiveBayes(Model):
    """
    Naive Bayes classifier.

    Parameters
    ----------
    alpha : float, default=1.0
        Additive (Laplace/Lidstone) smoothing parameter (0 for no smoothing).

    Attributes
    ----------
    prior : ndarray of shape (n_classes,)
        Probability of each class.
    lk : ndarray of shape (n_classes, n_features)
        Empirical mean and variance of features per class.
        classes_ : ndarray of shape (n_classes,)
        Class labels known to the classifier.

        It represents the probability of observing a certain 
        attribute value for a certain class.
    """

    def __init__(self, alpha=1.0):
        super(NaiveBayes).__init__()
        self.prior = None
        self.lk = None
        self.alpha = alpha

    def fit(self, dataset):
        """
        Fit Naive Bayes classifier according to X, y.

        Parameters
        ----------
        dataset : Dataset
            Dataset to fit the model to.
        """

        X, y = dataset.get_X(), dataset.get_y()
        self.dataset = dataset
        n = X.shape[0]

        X_by_class = np.array([X[y == c] for c in np.unique(y)], dtype = object)
        self.prior = np.array([len(X_class) / n for X_class in X_by_class])

        counts = np.array([sub_arr.sum(axis=0) for sub_arr in X_by_class]) + self.alpha
        self.lk = counts / counts.sum(axis=1).reshape(-1, 1)
        self.is_fitted = True

    def predict_proba(self, x):
        """
        Predict class probabilities for X.

        Parameters
        ----------
        x : array-like of shape (n_samples, n_features)
            Samples.

        Returns
        -------
        p : array-like of shape (n_samples, n_classes)
            The class probabilities of the input samples. The order of the
            classes corresponds to that in the attribute `classes_`.

        Notes
        -----
        The predicted class probabilities of an input sample are computed as
        ``p(y|x) = p(x|y)p(y) / p(x)``, where ``p(x|y)`` is the likelihood of
        the sample ``x`` given the class ``y``, ``p(y)`` is the prior of class
        ``y`` and ``p(x)`` is the prior probability of sample ``x``.

        """
    
        assert self.is_fitted, 'Model must be fit before predicting'

        # loop over each observation to calculate conditional probabilities
        class_numerators = np.zeros(shape=(x.shape[0], self.prior.shape[0]))
        for i, x in enumerate(x):
            exists = x.astype(bool)
            lk_present = self.lk[:, exists] ** x[exists]
            lk_marginal = (lk_present).prod(axis=1)
            class_numerators[i] = lk_marginal * self.prior

        normalize_term = class_numerators.sum(axis=1).reshape(-1, 1)
        conditional_probas = class_numerators / normalize_term
        assert (conditional_probas.sum(axis=1) - 1 < 0.001).all(), 'Rows should sum to 1'
        return conditional_probas

    def predict(self, x):
        """
        Perform classification on an array of test vectors X.

        Parameters
        ----------
        x : array-like of shape (n_samples, n_features)
            Samples.

        Returns
        -------
        C : ndarray of shape (n_samples,)
            Predicted target values for X.
        """

        assert self.is_fitted, 'Model must be fit before predicting'
        return self.predict_proba(x).argmax(axis=1)

    def cost(self, X=None, y=None):
        """
        Calculate the accuracy of the model on the given dataset.

        Parameters
        ----------
        X : array-like of shape (n_samples, n_features), default=None
            Samples.
        y : array-like of shape (n_samples,), default=None
            Target values.

        Returns
        -------
        cost : float
            Accuracy of the model on the given dataset.
        """

        assert self.is_fitted, 'Model must be fit before predicting'
        X = X if X is not None else self.dataset.X
        y = y if y is not None else self.dataset.y

        y_pred = self.predict(X)
        return accuracy_score(y, y_pred)
