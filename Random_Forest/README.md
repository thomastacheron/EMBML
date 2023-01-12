**How to use the Random Forest ?**

- Here is how the raw model was generated with emlearn, it needs modifications by hand after that (cf. random_forest.h).

```bash
cd src
python3 random_forest.py # generate raw output random_forest0.h
cd ..
```

- Then, you can use the predictions on your computer or on the embedded system by using the model and the sources.

```bash
mkdir build && cd build
cmake .. && make
./random_forest
```
