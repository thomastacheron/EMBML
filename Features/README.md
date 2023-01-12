**To generate features.csv :**

If there is one:

rm features.csv


Then:

mkdir build && cd build
cmake .. && make
./au_parser
cd ..
bash setup.bash