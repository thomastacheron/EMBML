**How to use the SVM ?**

- First you need to compute the model.

cd src
python3 svm.py
cd ..

- Then, you can use the predictions on your computer or on the embedded system by using the model and the sources.

mkdir build && cd build
cmake .. && make
./svm
