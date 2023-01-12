**How to use the Decision Tree ?**

- Here is how the raw model was generated with emlearn, it needs modifications by hand after that (cf. decision_tree.h).

```bash
cd src
python3 random_forest.py # generate raw output decision_tree0.h
cd ..
```

- Then, you can use the predictions on your computer or on the embedded system by using the model and the sources.

```bash
mkdir build && cd build
cmake .. && make
./decision_tree
```
