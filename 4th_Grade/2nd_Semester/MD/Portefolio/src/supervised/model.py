from abc import ABC, abstractmethod
from data.dataset import Dataset
import numpy as np

class Model(ABC):

    def __init__(self) -> None:
        """
        Abstract class for defining an interface for supervised learning models.
        A model needs all the above three methods to be implemented.
        """
        self.is_fitted = False

    @abstractmethod
    def fit(self, dataset: Dataset) -> None:
        raise NotImplementedError
    
    @abstractmethod
    def predict(self, x: np.ndarray) -> None:
        raise NotImplementedError

    
    def cost(self, *args, **kwarg) -> None:
        raise NotImplementedError
    