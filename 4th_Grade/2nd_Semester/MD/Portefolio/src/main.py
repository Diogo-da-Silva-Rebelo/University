from rw.to_csv import *
from data.feature_selection.select_k_best import *
from data.feature_selection.variance_th import *
from system.pycache import delete_cache
from supervised.dt import DecisionTree
from utils.util import train_test_split
from utils.metrics import accuracy_score
from supervised.nb import NaiveBayes
from supervised.prism import PRISM

def test_numeric_data_with_header() -> None:
    print("="*60 + "\n")
    dataset_name = "iris_missing_data.csv"
    print("\033[93m{}\033[00m".format(f"Lendo Dataset {dataset_name}"))
    ds = read_csv(f"../datasets/{dataset_name}", ',',features=True,label=True)
    print("Leitura completa.\n")
    print("\033[93m{}\033[00m".format("Obtendo estatísticas..."))
    print(f"Mean:   {ds.get_mean()}")
    print(f"Var:    {ds.get_var()}")
    print(f"Median: {ds.get_median()}")
    print(f"Max:    {ds.get_max()}")
    print(f"Min:    {ds.get_min()}")
    print(f"Null:   {ds.count_nulls()}")
    print("\033[93m{}\033[00m".format("\nResumo: "))
    print(ds.summary())

    print("\nReplacing null values...\n")
    ds.replace_nulls()
    print(ds.summary())

def test_numeric_data_without_header() -> None:
    print("="*60 + "\n")
    dataset_name = "breast-bin.data"
    print("\033[93m{}\033[00m".format(f"Lendo Dataset {dataset_name}"))
    ds = read_csv(f"../datasets/{dataset_name}")
    print("Leitura completa.\n")
    print("\033[93m{}\033[00m".format("Obtendo estatísticas..."))
    print(f"Mean:   {ds.get_mean()}")
    print(f"Var:    {ds.get_var()}")
    print(f"Median: {ds.get_median()}")
    print(f"Max:    {ds.get_max()}")
    print(f"Min:    {ds.get_min()}")
    print(f"Null:   {ds.count_nulls()}")
    print("\033[93m{}\033[00m".format("\nResumo: "))
    print(ds.summary())

def test_discrete_data_with_header() -> None:
    print("="*60 + "\n")
    dataset_name = "titanic_dataset.csv"
    print("\033[93m{}\033[00m".format(f"Lendo Dataset {dataset_name}"))
    ds = read_csv(f"../datasets/{dataset_name}",",",features=True,label="Survived")
    print("Leitura completa.\n")
    print("\033[93m{}\033[00m".format("Obtendo estatísticas..."))
    print("\033[93m{}\033[00m".format("\nResumo: "))
    print(ds.summary())

    print("\nReplacing null values...\n")
    ds.replace_nulls()
    print(ds.summary())
    write_csv(filename="../datasets/titanic_no_missing_data.csv",dataset=ds, features=True,label=True)

def test_variance_th_and_k_features() -> None:
    print("="*65 + "\n")
    dataset_name = "iris_missing_data.csv"
    print("\033[93m{}\033[00m".format(f"Lendo Dataset {dataset_name}"))
    ds = read_csv(f"../datasets/{dataset_name}", ',',features=True,label=True)
    print("Leitura completa.\n")
    ds.replace_nulls()

    th = 0.4
    print("\033[93m{}\033[00m".format(f"Seleção de features por Variance Threshold [th = {th}]"))
    varianceth = VarianceThreshold(threshold=th)
    varianceth.fit(dataset=ds)
    transformed_datset = varianceth.transform(dataset=ds,inline=False)

    print(f"Selected Features: {transformed_datset.features}\n")
    write_csv(filename="../datasets/iris_variance_th.csv",dataset=transformed_datset, features=True,label=True)

    k = 2
    print("\033[93m{}\033[00m".format(f"Seleção de features por K Best [k = {k}]"))
    kBest = SelectKBest(k=k)
    kBest.fit(dataset=ds)
    transformed_k_datset = kBest.transform(dataset=ds,inline=False)
    print(f"Selected Features: {transformed_k_datset.features}\n")
    write_csv(filename="../datasets/iris_k_best.csv",dataset=transformed_k_datset, features=True,label=True)
    print("="*65 + "\n")
    delete_cache() # remover arquivos de __pycache__

def test_dt():
    print("="*65 + "\n")
    dataset_name = "breast-bin.data"
    print("\033[93m{}\033[00m".format(f"Lendo Dataset {dataset_name}"))
    ds = read_csv(f"../datasets/{dataset_name}", ',',features=False,label=True)
    print("Leitura completa.\n")
    ds.replace_nulls()

    print("\033[93m{}\033[00m".format(f"Dividindo dataset: {dataset_name}\n"))
    train_data, test_data = train_test_split(ds)
    print(f"Shape of train data [X_train]: ({train_data.get_X().shape[0]},{train_data.get_X().shape[1]})")
    print(f"Shape of test data   [X_test]: ({test_data.get_X().shape[0]},{test_data.get_X().shape[1]})")

    print("\033[93m{}\033[00m".format(f"\nAplicando DT ...\n"))

    dt = DecisionTree(criterion='entropy', # criterion: {'gini' (default), 'entropy', 'loss'}
                       prun='post',         # prun: {'pre' (default), 'post'}
                       max_depth=7, 
                       min_samples_leaf=2, 
                       min_samples_split=3, 
                       x_test=test_data.get_X(), 
                       y_test=test_data.get_y())

    dt.fit(train_data)
    y_pred = dt.predict(test_data.get_X())
    y_true = test_data.get_y()
    acc = accuracy_score(y_true, y_pred)
    print("Accuracy: %4f" % acc)
    print("="*65 + "\n")
    delete_cache()

def test_nb():
    dataset_name = "breast-bin.data"
    ds = read_csv(f"../datasets/{dataset_name}", ',',features=False,label=True)
    ds.replace_nulls()

    train_data, test_data = train_test_split(ds)
    print(f"Shape of train data [X_train]: ({train_data.get_X().shape[0]},{train_data.get_X().shape[1]})")
    print(f"Shape of test data   [X_test]: ({test_data.get_X().shape[0]},{test_data.get_X().shape[1]})")

    nb = NaiveBayes(alpha=1)
    nb.fit(train_data)
    y_pred = nb.predict(test_data.get_X())
    y_true = test_data.get_y()
    acc = accuracy_score(y_true, y_pred)
    print("Accuracy: %4f" % acc)
    print("Cost: %4f" % nb.cost())
    delete_cache()

def test_prism():
    dataset_name = "breast-bin.data"
    ds = read_csv(f"../datasets/{dataset_name}", ',',features=False,label=True)
    ds.replace_nulls()

    train_data, test_data = train_test_split(ds)
    print(f"Shape of train data [X_train]: ({train_data.get_X().shape[0]},{train_data.get_X().shape[1]})")
    print(f"Shape of test data   [X_test]: ({test_data.get_X().shape[0]},{test_data.get_X().shape[1]})")

    prism = PRISM()
    prism.fit(train_data)
    y_pred = prism.predict(test_data.get_X())
    y_true = test_data.get_y()
    acc = accuracy_score(y_true, y_pred)
    print("Accuracy: %4f" % acc)
    delete_cache()

def test_apriori():
    dataset_name = "discrete.data"
    ds = read_csv(f"../datasets/{dataset_name}", ',',features=False,label=False)

    print("\033[93m{}\033[00m".format(f"Aplicando Apriori ...\n"))
    min_support = 0.5
    fp_growth = FPGrowth(min_support)
    fp_growth.fit(ds)

    print(f"Min Support: {min_support}\n")
    print(str(fp_growth.display_tree()))
    print("\n")
    #freq_itemsets = fp_growth.display_freq_itemsets()
    #print(freq_itemsets)
    delete_cache()

def main():
    test_prism() # Change for testing


if __name__ == "__main__" :
    main()