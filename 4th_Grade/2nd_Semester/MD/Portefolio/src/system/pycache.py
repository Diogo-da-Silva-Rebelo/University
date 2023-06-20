import os
import shutil


def delete_cache() -> None:
    """
    Deletes all the __pycache__ directories.
    """
    # Change to your project directory
    os.chdir('../src/')

    # Search for all __pycache__ directories and delete them
    for root, dirs, files in os.walk('.', topdown=False):
        for name in dirs:
            if name == '__pycache__':
                shutil.rmtree(os.path.join(root, name))
