import numpy as np
from data.dataset import Dataset
from typing import Tuple, Union
from scipy import stats


def f_classification(dataset: Dataset) -> Union[Tuple[np.ndarray, np.ndarray],
                                                Tuple[float, float]]:
    """Scoring function for classifications.
    Compute the ANOVA F-value for the provided sample.
    We want to identify which groups have means 
    significantly different.
    The null hypotesis, H0: means
    is the same for all groups, ie, the factors
    or features do not significantly affect the labels.

    Parameters
    ----------
    daatset: Dataset
        A labeled dataset

    Returns
    -------
    (F, p): scores and p-values (numpy.ndarray tuple)
        Tupple of numpy.ndarrays
    """

    X = dataset.X
    y = dataset.y

    # Computes the F-statistics and p values.
    classes = dataset.get_classes()
    groups = [X[y == c] for c in classes]
    F, p = stats.f_oneway(*groups)
    # O valor F mede a diferença entre as médias dos grupos em relação à 
    # variabilidade dentro dos grupos. 
    # Valores maiores de F indicam maior diferença entre as médias dos grupos.
    # +p -> - probabilidade de H0 ser verdadeira -> - probabilidade de F ser extremo -> médias muito diferentes
    return F, p
