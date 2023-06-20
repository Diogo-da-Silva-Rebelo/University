from abc import ABC, abstractmethod
from data.dataset import Dataset

class Transformer(ABC):

    def fit(self, dataset: Dataset) -> None:
        """Learns the transformer parameters (if any).

        Parameters
        ----------
        dataset: Dataset
            A labeled dataset to learn from
        """
        return self

    @abstractmethod
    def transform(self, dataset, inline:bool=False) -> None:
        """Transforms a dataset.

        Parameters
        ----------
        dataset: Dataset
            A labeled dataset to learn from
        inline: bool
            If the tranformation is to be applyied inline to the input dataset
            or if a new transformed dataset is to be generated.
        """
        raise NotImplementedError

    def fit_transform(self, dataset, inline=False) -> None:
        """Fits and Transforms a dataset.

        Parameters
        ----------
        dataset: Dataset
            A labeled dataset to learn from
        inline: bool
            If the tranformation is to be applyied inline to the input dataset
            or if a new transformed dataset is to be generated.
        """
        self.fit(dataset)
        return self.transform(dataset, inline=inline)
    