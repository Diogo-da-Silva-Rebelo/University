from data.transformer import Transformer
from stats.f_classification import f_classification
from stats.f_regression import f_regression
from data.dataset import Dataset
from copy import copy
from typing import Callable
import numpy as np

class SelectKBest(Transformer):

    def __init__(self, k: int, score_func: Callable = f_classification) -> None:
        """The SelectKBest method selects the features according to the k highest scores
        computed using a scoring function.

        Parameters
        ---------- 
        k: int
            Number of feature with best score to be selected
        score_func: callable, optional
            The scoring function, defaults to f_classif
        -------------------------------------------------------------------------
        In this implementation we will consider the two F-statistics functions, 
        one for regression (f_regress) and the other for classification tasks (f_classif).
        The p and F values have an inverse relationship, the greater
        the F value the lesser the p.
        Larger values of F correspond to a rejection with probability
        (1-p) of the null hypothesis, meaning that the corresponding 
        features has an effect on the predictions.
        """
        self.k = k
        self.score_func = score_func

    def fit(self, dataset: Dataset)-> None:
        """
        Fit based on the train data.

        Parameters
        ----------
        dataset: Dataset
            The dataset to be fitted
        -------------------------------------------------------------------------
        """

        if not dataset.all_numeric:
            raise ValueError("Theres is not encoded data. Consider using an encoder.")
        else:
            self.F, self.p = self.score_func(dataset)

    def transform(self, dataset: Dataset, inline=False) -> Dataset:
        """


        Parameters
        ----------
        dataset: Dataset
            The dataset to be transformed
        inline: bool, optional
            If True, the transformation is applied to the dataset, otherwise
            a new dataset is returned, defaults to False

        Returns
        -------
        dataset: Dataset
            The transformed dataset
        -------------------------------------------------------------------------
        
        """
        
        if not dataset.all_numeric:
            raise ValueError("Theres is not encoded data. Consider using an encoder.")
        else:
            top_k_indices = self.F.argsort()[-self.k:][::-1]

        if inline:
            dataset.X = dataset.X[:, top_k_indices]
            dataset.features = [dataset.feature[i] for i in top_k_indices]
            dataset.numeric_features = dataset.features
            new_discrete_mask = np.zeros(dataset.X.shape[1], dtype=bool)
            new_discrete_mask[top_k_indices] = False
            return dataset
        else:
            transformed_features = [dataset.features[i] for i in top_k_indices]
            X_trans = dataset.X[:, top_k_indices]
            
            return Dataset(X=copy(X_trans), 
                           y= copy(dataset.y), 
                           features=transformed_features,
                           numeric_features =list(dataset.features), 
                           label=copy(dataset.label))
