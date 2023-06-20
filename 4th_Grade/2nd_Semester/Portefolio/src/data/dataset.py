from typing import Tuple, Sequence

import numpy as np
import pandas as pd

class Dataset:
    def __init__(self, X: np.ndarray, 
                 y: np.ndarray = None, 
                 features: Sequence[str] = None,
                 discrete_features: Sequence[str] = None,
                 numeric_features: Sequence[str] = None, 
                 label: str = None):
        """
        Dataset represents a machine learning tabular dataset.

        Parameters
        ----------
        X: numpy.ndarray (n_samples, n_features)
            The feature matrix
        y: numpy.ndarray (n_samples, 1)
            The label vector
        features: list of str (n_features)
            The feature names
        discrete_features : list of str (n_features)
            The features names of discrete features
        numeric_features : list of str (n_features)
            The features names of numeric features
        label: str (1)
            The label name
        """
        if X is None:
            raise ValueError("X cannot be None")

        if features is None:
            features = [str(i) for i in range(X.shape[1])]
        else:
            features = list(features)

        if discrete_features is None and numeric_features is None:
            raise ValueError("At least one of discrete_features or numeric_features must be provided")
        elif discrete_features is None:
            self.discrete_mask = np.isin(features, numeric_features)
        elif numeric_features is None:
            self.discrete_mask = np.isin(features, discrete_features, invert=True)
        else:
            self.discrete_mask = np.zeros(X.shape[1], dtype=bool)
            self.discrete_mask[np.isin(features, discrete_features)] = True
            self.discrete_mask[np.isin(features, numeric_features)] = False

        if y is not None and label is None:
            label = "y"

        self.X = X
        self.y = y
        self.features = features
        self.label = label
        self.to_numeric()

        if all(~self.discrete_mask): self.all_numeric = True
        else: self.all_numeric = False

    def to_numeric(self):
        """
        Ensures that numeric features have a numeric type.

        """
        discrete_mask = self.get_discrete_mask()
        if any(~discrete_mask):
            self.X[:, ~discrete_mask] = self.X[:, ~discrete_mask].astype(float)

    def get_X(self):
        """
        Getter for X array.

        Returns
        -------
        X: numpy.ndarray (n_samples, n_features)
            The feature matrix
        """
        return self.X
    
    def get_y(self):
        """
        Getter for y array.

        Returns
        -------
        y: numpy.ndarray (n_samples, 1)
            The label vector
        """
        return self.y
    
    def get_features(self):
        """
        Getter for features array.

        Returns
        -------
        features: list of str (n_features)
            The feature names
        """
        return self.features
    
    def get_label(self):
        """
        Getter for label name.

        Returns
        -------
        label: str (1)
            The label name
        """
        return self.label

    def get_discrete_mask(self) -> np.ndarray:
        """
        Returns the boolean mask indicating which columns in X correspond to discrete features.

        Returns
        -------
        numpy.ndarray (n_features,)
            Boolean mask indicating which columns in X correspond to discrete features
        """
        return self.discrete_mask

    def get_discrete_X(self) -> np.ndarray:
        """
        Returns the subset of X corresponding to the discrete features.

        Returns
        -------
        numpy.ndarray (n_samples, n_discrete_features)
            Subset of X corresponding to the discrete features
        """
        return self.X[:, self.discrete_mask]

    def shape(self) -> Tuple[int, int]:
        """
        Returns the shape of the dataset.

        Returns
        -------
        tuple (n_samples, n_features)
        """
        return self.X.shape

    def has_label(self) -> bool:
        """
        Returns True if the dataset has a label.

        Returns
        -------
        bool
        """
        return self.y is not None

    def get_classes(self) -> np.ndarray:
        """
        Returns the unique classes in the dataset.

        Returns
        -------
        numpy.ndarray (n_classes)
        """
        if self.y is None:
            raise ValueError("Dataset does not have a label")
        return np.unique(self.y)

    def get_mean(self) -> np.ndarray:
        """
        Computes the mean for each numeric feature in the dataset, and returns an array with the results. 
        For discrete features, the corresponding value in the array is set to np.nan.

        Returns
        -------
        numpy.ndarray (n_features,)
            An array with the mean for each numeric feature. If a feature is discrete, the corresponding 
            value in the array is np.nan.
        """
        discrete_mask = self.get_discrete_mask()

        # Calculate the mean of each numeric feature
        numeric_means = np.nanmean(self.X[:, ~discrete_mask], axis=0)

        # Create a result array with NaN values for discrete features
        result = np.empty(self.X.shape[1])
        result.fill(np.nan)

        # Assign the numeric means to the result array
        result[~discrete_mask] = numeric_means

        return result
    
    def get_var(self) -> np.ndarray:
        """
        Computes the variance for each numeric feature in the dataset, and returns an array with the results. 
        For discrete features, the corresponding value in the array is set to np.nan.

        Returns
        -------
        numpy.ndarray (n_features,)
            An array with the variance for each numeric feature. If a feature is discrete, the corresponding 
            value in the array is np.nan.
        """
        discrete_mask = self.get_discrete_mask()

        # Calculate the var of each numeric feature
        numeric_vars = np.nanvar(self.X[:, ~discrete_mask], axis=0)

        # Create a result array with NaN values for discrete features
        result = np.empty(self.X.shape[1])
        result.fill(np.nan)

        # Assign the numeric vars to the result array
        result[~discrete_mask] = numeric_vars

        return result

    def get_median(self) -> np.ndarray:
        """
        Computes the median for each numeric feature in the dataset, and returns an array with the results. 
        For discrete features, the corresponding value in the array is set to np.nan.

        Returns
        -------
        numpy.ndarray (n_features,)
            An array with the median for each numeric feature. If a feature is discrete, the corresponding 
            value in the array is np.nan.
        """
        discrete_mask = self.get_discrete_mask()

        # Calculate the var of each numeric feature
        numeric_median = np.nanmedian(self.X[:, ~discrete_mask], axis=0)

        # Create a result array with NaN values for discrete features
        result = np.empty(self.X.shape[1])
        result.fill(np.nan)

        # Assign the numeric median to the result array
        result[~discrete_mask] = numeric_median

        return result
    
    def get_max(self) -> np.ndarray:
        """
        Computes the maximum value for each numeric feature in the dataset, and returns an array with the results. 
        For discrete features, the corresponding value in the array is set to np.nan.

        Returns
        -------
        numpy.ndarray (n_features,)
            An array with the maximum value for each numeric feature. If a feature is discrete, the corresponding 
            value in the array is np.nan.
        """
        discrete_mask = self.get_discrete_mask()

        # Calculate the var of each numeric feature
        numeric_max = np.nanmax(self.X[:, ~discrete_mask], axis=0)

        # Create a result array with NaN values for discrete features
        result = np.empty(self.X.shape[1])
        result.fill(np.nan)

        # Assign the numeric max to the result array
        result[~discrete_mask] = numeric_max

        return result
    
    def get_min(self) -> np.ndarray:
        """
        Computes the minimum value for each numeric feature in the dataset, and returns an array with the results. 
        For discrete features, the corresponding value in the array is set to np.nan.

        Returns
        -------
        numpy.ndarray (n_features,)
            An array with the minimum value for each numeric feature. If a feature is discrete, the corresponding 
            value in the array is np.nan.
        """
        discrete_mask = self.get_discrete_mask()

        # Calculate the var of each numeric feature
        numeric_min = np.nanmin(self.X[:, ~discrete_mask], axis=0)

        # Create a result array with NaN values for discrete features
        result = np.empty(self.X.shape[1])
        result.fill(np.nan)

        # Assign the numeric min to the result array
        result[~discrete_mask] = numeric_min

        return result


    def summary(self) -> pd.DataFrame:
        """
        Returns a summary of the dataset

        Returns
        -------
        pandas.DataFrame (n_features, 5)
        """
        data = {
            "mean": self.get_mean(),
            "median": self.get_median(),
            "var": self.get_var(),
            "min": self.get_min(),
            "max": self.get_max(),
            "nan": self.count_nulls()
        }
        return pd.DataFrame.from_dict(data, orient="index", columns=self.features)

    @classmethod
    def from_dataframe(cls, df: pd.DataFrame, label: str = None):
        """
        Creates a Dataset object from a pandas DataFrame.

        Parameters
        ----------
        df: pandas.DataFrame
            The DataFrame
        label: str
            The label name

        Returns
        -------
        Dataset
        """
        if label:
            X = df.drop(label, axis=1).to_numpy()
            y = df[label].to_numpy()
        else:
            X = df.to_numpy()
            y = None

        features = df.columns.tolist()
        return cls(X, y, features=features, label=label)

    def to_dataframe(self) -> pd.DataFrame:
        """
        Converts the dataset to a pandas DataFrame.

        Returns
        -------
        pandas.DataFrame
        """
        if self.y is None:
            return pd.DataFrame(self.X, columns=self.features)
        else:
            df = pd.DataFrame(self.X, columns=self.features)
            df[self.label] = self.y
            return df

    @classmethod
    def from_random(cls,
                    n_samples: int,
                    n_features: int,
                    n_classes: int = 2,
                    features: Sequence[str] = None,
                    label: str = None):
        """
        Creates a Dataset object from random data.

        Parameters
        ----------
        n_samples: int
            The number of samples
        n_features: int
            The number of features
        n_classes: int
            The number of classes
        features: list of str
            The feature names
        label: str
            The label name
        Returns
        -------
        Dataset
        """
        X = np.random.rand(n_samples, n_features)
        y = np.random.randint(0, n_classes, n_samples)
        return cls(X, y, features=features, label=label)
    
    def replace_nulls(self, method='mean'):
        """
        Replace all NaN values of each numeric feature using the specified method.

        Parameters
        ----------
        method : str, optional (default='mean')
            Method of replacing
        """
        discrete_mask = self.get_discrete_mask()

        if method == 'mean':
            means = np.nanmean(self.X[:, ~discrete_mask], axis=0)
            self.X[:, ~discrete_mask] = np.where(np.isnan(self.X[:, ~discrete_mask].astype(np.float32)), means, self.X[:, ~discrete_mask])
        elif method == 'median':
            medians = np.nanmedian(self.X[:, ~discrete_mask], axis=0)
            self.X[:, ~discrete_mask] = np.where(np.isnan(self.X[:, ~discrete_mask].astype(np.float32)), medians, self.X[:, ~discrete_mask])
        else:
            raise ValueError("Invalid method: {}".format(method))

    def count_nulls(self) -> np.ndarray:
        """
        Counts the number of null values in each numeric feature of X.

        Returns
        -------
        numpy.ndarray (n_features,)
            Array containing the number of null values in each feature.
        """
        discrete_mask = self.get_discrete_mask()
        bool_array = np.isnan(self.X[:, ~discrete_mask].astype(np.float32))
        nulls = np.count_nonzero(bool_array, axis = 0)
        return nulls
    