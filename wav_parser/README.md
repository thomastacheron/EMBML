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