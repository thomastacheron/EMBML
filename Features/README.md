**How to generate features.csv ?**

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
