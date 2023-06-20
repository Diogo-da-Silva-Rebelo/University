import numpy as np
from tabulate import tabulate
from typing import List, Tuple, Dict
from collections import defaultdict
from data.dataset import Dataset

class FPTree():

    def __init__(self, item: int, count: int, parent: 'FPTree' = None):
        self.item = item
        self.count = count
        self.parent = parent
        self.children = {}
        self.node_link = None

    def increment(self, count: int):
        self.count += count

    def display(self, indent: int = 1):
        print('  ' * indent, self.item, ':', self.count)
        for child in self.children.values():
                child.display(indent + 1)


class FPGrowth():

    def __init__(self, min_support: float):
        self.min_support = min_support
        self.header_table = {}
        self.frequent_items = []
        self.frequent_itemsets = []

    def fit(self, dataset : Dataset) -> None:
        self.dataset = dataset
        X = dataset.get_X()
        self.frequent_items = self._find_frequent_items(X)
        self.fp_tree, self.header_table = self._construct_fp_tree(X)
        self.mine_frequent_itemsets(X, self.fp_tree, self.header_table)

    
    def _find_frequent_items(self, X: np.ndarray) -> List[int]:
        items = defaultdict(int)

        # Count items
        for transaction in X:
                for item in transaction:
                    items[item] += 1

        # Filter items
        frequent_items = [item 
                          for item, support in items.items() 
                          if support / len(X) >= self.min_support]
        return frequent_items
    
    def _construct_fp_tree(self, X: np.ndarray) -> Tuple[FPTree, Dict[int, Tuple[FPTree, FPTree]]]:
        root = FPTree(None, 0, None)
        header_table = {int(item): (0, None) for item in self.frequent_items}

        # Add transactions to FP tree
        for transaction in X:
            # Filter items by frequent items
            filtered_transaction = [item for item in transaction if item in self.frequent_items]
            # Sort items by support
            filtered_transaction.sort(key=lambda item: header_table[item][0] if header_table[item][0] else 0, reverse=True)
            self._add_to_fp_tree(root, filtered_transaction, header_table)
        return root, header_table

    def _add_to_fp_tree(self, node: FPTree, transaction: List[int], header_table: Dict[int, Tuple[FPTree, FPTree]]) -> None:
        if not transaction:
            return
        item = transaction[0]
        child = node.children.get(item)
        if not child:
            # Add new child node
            child = FPTree(item, 0, node)
            node.children[item] = child

            # Update header table
            if header_table[item][1]:
                # Update the node link of the last node in the list
                header_table[item][1].node_link = child
            else:
                # First node for this item
                header_table[item] = (header_table[item][0], child)
            header_table[item] = (header_table[item][0], child)
        child.count += 1
        # Recursively add rest of transaction
        self._add_to_fp_tree(child, transaction[1:], header_table)
 
    def mine_frequent_itemsets(self, X: np.ndarray, node: FPTree, header_table: Dict[int, Tuple[FPTree, FPTree]]) -> None:
        # Find all paths from node to root
        paths = self._find_paths(node)
        for path in paths:
            # Get the conditional pattern base
            conditional_pattern_base = self._get_conditional_pattern_base(path)
            # Construct conditional FP tree
            conditional_fp_tree, conditional_header_table = self._construct_conditional_fp_tree(conditional_pattern_base)
            # Mine conditional FP tree
            if conditional_header_table:
                self.mine_frequent_itemsets(X, conditional_fp_tree, conditional_header_table)
            # Add frequent itemset to list
            frequent_itemset = [node.item]
            frequent_itemset.extend([path_item.item for path_item in path])
            self.frequent_itemsets.append((frequent_itemset, node.count / len(X)))
    
    def display_tree(self):
        self.fp_tree.display()

    def display_freq_itemsets(self):
        print(tabulate(self.frequent_itemsets, headers=['Frequent Itemsets', 'Support']))
