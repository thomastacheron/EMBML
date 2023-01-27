# Embedded Machine Learning

## Team : Thomas TACHERON, Augustin MORGE

### Features : C++ sources to extract features from GTZAN dataset.

**How to generate features.csv ?**

```bash
cd Features
```

- First you need to make sure there is not one already.

```bash
rm features.csv
```

- Then:

```bash
mkdir build && cd build
cmake .. && make
./au_parser
cd ..
bash setup.bash
```
### wav_parser : C++ sources to extract data from GTZAN dataset in .wav format.

```bash
cd wav_parser
```

**How to use wav_parser ?**

wav_parser parses the data stored in a .wav file from GTZAN dataset (i.e. 22050Hz Mono 16-bit audio files in .wav format).

```bash
mkdir build && cd build
cmake .. && ./wav_parser >> ../output
```

You will obtain an output which contains the data separated by a comma, followed by the header.
You can provide another .wav by changing the path or feeding multiple paths (cf. Features/src/main.cpp) in order to extract data.
To do that, it is better to comment the line 94 which displays the header.

```c++
std::cout << wav << "\n";
```

### SVM, Random_Forest, Decision_Tree : Trains a model in order to get C++ sources for inferring on an embedded system.

First you need to compute the model by running a python script, then you can use the C++ sources and the model files on an embedded system to make predictions. Refer to specific README.md to get more instructions.

### CNN

- First you need to compute the model. A .ipynb is provided for Google COLAB.

- Then, you can use the predictions on the embedded system by using the model and the sources.

```bash
./setup.bash
./cnn
```

![result2](https://user-images.githubusercontent.com/114411509/215166125-063cd745-e986-43c1-9d3d-7894796bfc71.png)

We did not manage to remove the overfitting by lack of time.

![result](https://user-images.githubusercontent.com/114411509/215166136-eef665d9-6132-44de-8796-08bd149f1241.png)

46% accuracy
