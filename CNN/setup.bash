rm -r build
mkdir build
echo "output:
	g++ -std=c++11 -o cnn -I/home/pi/tensorflow ../src/main.cpp ../src/libtensorflow-lite.a -pthread -lrt -ldl

all: output

clean:
" >> build/makefile
cd build
make
