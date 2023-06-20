import numpy as np
from scipy.stats import mode
from .model import Model
from utils.metrics import accuracy_score
from data.dataset import Dataset


class PRISM(Model):
    """
    PRISM is a rule-based classifier that uses a greedy search to find the best rule.
    """

    def __init__(self):
        """
        Initialize the PRISM classifier.
        """

        super(PRISM, self).__init__()
        self.rules = []

    def fit(self, dataset : Dataset):
        """
        Fit the PRISM classifier to the dataset.

        Parameters
        ----------
        dataset : Dataset
            The dataset to fit the classifier to.
            
        Raises
        ------
        ValueError
            If the dataset is not a classification dataset.
        """

        self.dataset = dataset
        X, y = dataset.get_X(), dataset.get_y()
        discrete_mask = self.dataset.get_discrete_mask()

        if len(np.unique(y)) == 1:
            self.rules.append((None, y[0]))
            return
        
        while len(np.unique(y)) > 1:
            best_rule, best_score = None, -np.inf

            for feature_idx, is_discrete in enumerate(discrete_mask):
                if is_discrete:
                    unique_values = np.unique(X[:, feature_idx])
                    covered = np.equal.outer(X[:, feature_idx], unique_values)

                    for i, value in enumerate(unique_values):
                        rule = (feature_idx, value)
                        score = self.evaluate_rule(X, y, rule, covered[:, i])
                        if score > best_score:
                            best_rule, best_score = rule, score
                else:
                    # Handling numeric features
                    unique_values = np.unique(X[:, feature_idx])

                    for i, value in enumerate(unique_values):
                        covered = X[:, feature_idx] <= value
                        rule = (feature_idx, value, True)  # Less than or equal to value
                        score = self.evaluate_rule(X, y, rule, covered)

                        if score > best_score:
                            best_rule, best_score = rule, score

                        covered = X[:, feature_idx] > value
                        rule = (feature_idx, value, False)  # Greater than value
                        score = self.evaluate_rule(X, y, rule, covered)

                        if score > best_score:
                            best_rule, best_score = rule, score

            self.rules.append(best_rule)
            X, y = self.remove_covered_examples(X, y, best_rule)

    def evaluate_rule(self, X, y, rule, covered):
        """
        Evaluate the rule on the dataset.

        Parameters
        ----------
        X : np.ndarray
            The dataset to evaluate the rule on.
        y : np.ndarray
            The target values of the dataset.
        rule : tuple
            The rule to evaluate.
        covered : np.ndarray
            A boolean array indicating which examples are covered by the rule.
        
        Returns
        -------
        float
            The accuracy of the rule.
        """

        feature_idx, value = rule[:2]
        target_covered = y[covered]
        most_common, _ = mode(target_covered, keepdims = True)
        correct = np.sum(target_covered == most_common)
        return correct / len(target_covered)

    def remove_covered_examples(self, X, y, rule):
        """
        Remove the examples covered by the rule from the dataset.

        Parameters
        ----------
        X : np.ndarray
            The dataset to remove the examples from.
        y : np.ndarray
            The target values of the dataset.
        rule : tuple
            The rule to evaluate.
        
        Returns
        -------
        np.ndarray
            The dataset without the examples covered by the rule.
        np.ndarray
            The target values without the examples covered by the rule.
        """

        feature_idx, value = rule[:2]
        if len(rule) == 3:
            is_less_than_or_equal = rule[2]
            if is_less_than_or_equal:
                not_covered = X[:, feature_idx] > value
            else:
                not_covered = X[:, feature_idx] <= value
        else:
            not_covered = X[:, feature_idx] != value

        return X[not_covered], y[not_covered]

    def predict(self, X):
        """
        Predict the target values of the dataset.

        Parameters
        ----------
        X : np.ndarray
            The dataset to predict the target values of.
        
        Returns
        -------
        np.ndarray
            The predicted target values.
        
        Raises
        ------
        ValueError
            If the model is not fitted.
        
        """
        predictions = np.zeros(X.shape[0], dtype=int)
        for rule in self.rules:
            feature_idx, value = rule[:2]
            if len(rule) == 3:
                is_less_than_or_equal = rule[2]
                if is_less_than_or_equal:
                    covered = X[:, feature_idx] <= value
                else:
                    covered = X[:, feature_idx] > value
            else:
                covered = X[:, feature_idx] == value

            if np.any(covered):
                target_covered = self.dataset.y[self.dataset.X[:, feature_idx] == value]
                most_common, _ = mode(target_covered, keepdims = True)
                predictions[covered] = most_common
        return predictions
    