import numpy as np
from copy import copy

from data.transformer import Transformer
from data.dataset import Dataset

class VarianceThreshold(Transformer):

    def __init__(self, threshold = 0) -> None:
        """
        Parameters
        ----------
        threshold: float, optional
            The threshold to be used to filter the features, defaults to 0
        """

        if threshold < 0:
            raise ValueError("The thershold must be a non-negative value.")
        self.threshold = threshold

    def fit(self, dataset: Dataset) -> None:
        """
        Parameters
        ----------
        dataset: Dataset
            The dataset to be fitted
        """

        if not dataset.all_numeric:
            raise ValueError("Theres is not encoded data. Consider using an encoder.")
        else:
            X = dataset.X
            self._var = np.var(X, axis=0)

    def transform(self, dataset, inline=False) -> Dataset:
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
        
        -----------------------------------------------------------------

        
        """
        if not dataset.all_numeric:
            raise ValueError("Theres is not encoded data. Consider using an encoder.")
        else:
            X = dataset.X
            features_mask = np.where(self._var > self.threshold)[0]
            X_trans = X[:, features_mask]
            features_names = np.array(dataset.features)[features_mask]
            numeric_features = list(features_names)
            new_discrete_mask = np.zeros(dataset.X.shape[1], dtype=bool)
            new_discrete_mask[features_mask] = False

            if inline:
                dataset.X = X_trans
                dataset.features = features_names
                dataset.numeric_features = numeric_features
                dataset.discrete_mask = new_discrete_mask
                return dataset
            else:
                return Dataset(X=copy(X_trans),
                               y=copy(dataset.y),
                               features=list(features_names),
                               numeric_features = numeric_features, 
                               label=copy(dataset.label))
