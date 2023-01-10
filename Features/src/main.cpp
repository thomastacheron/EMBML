#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <netinet/in.h>
#include <vector>
#include <numeric>
#include <complex>
#include <filesystem>
#include <sstream>
#include "constants.h"
#include "fft_utils.h"

typedef int16_t I16;
typedef uint32_t U32;
typedef std::vector<float_t> DataVector;

#pragma pack(push, 1)
struct Header_au{
  U32 magicNumber;
  U32 dataOffset;
  U32 dataSize;
  U32 encoding;
  U32 sampleRate;
  U32 channels;

  void be2he(){
    magicNumber = ntohl(magicNumber);
    assert(magicNumber == 0x2e736e64);
    dataOffset = ntohl(dataOffset);
    dataSize = ntohl(dataSize);
    encoding = ntohl(encoding);
    sampleRate = ntohl(sampleRate);
    channels = ntohl(channels);
  }
};
#pragma pack(pop)

struct Au{
  Header_au hdr;
  DataVector dataVector;
};

std::ostream& operator<<(std::ostream& os, const Header_au& hdr){
  os << "======= .au file =======" << "\n";
  os << "magicNumber : " << std::hex << hdr.magicNumber << std::dec << "\n";
  os << "dataOffset : " << hdr.dataOffset << "\n";
  os << "dataSize : " << hdr.dataSize << "\n";
  os << "encoding : " << hdr.encoding << "\n";
  os << "sampleRate : " << hdr.sampleRate << "\n";
  os << "channels : " << hdr.channels << "\n";
  os << "========================" << "\n";
  return os;
}

std::ostream& operator<<(std::ostream& os, const DataVector& dataVector){
  bool first = true;
  for (auto& elem: dataVector){
    if (!first){
      os << ",";
    }
    first = false;
    os << elem;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Au& au){
  os << au.hdr << au.dataVector;
  return os;
}

void load_au(std::ifstream& datafile, Au& au){
  datafile.read(reinterpret_cast<char*>(&au.hdr), sizeof(au.hdr));
  au.hdr.be2he();
  assert(au.hdr.magicNumber == 0x2e736e64);
  I16 data;
  datafile.seekg(au.hdr.dataOffset);
  while (!datafile.eof()){
    datafile.read(reinterpret_cast<char*>(&data), sizeof(data));
    if (datafile.eof()){
      break;
    }
    data = ntohs(data);
    au.dataVector.push_back(data);
  }
}

void feature_extraction(const std::string& file_path){
  std::ifstream datafile;
  datafile.open(file_path.c_str(), std::ios::binary | std::ios::in);
  if(!datafile.is_open())
    throw "Unable to load data file";
  Au au;
  load_au(datafile, au);
  // std::cout << au.hdr;

  auto avg = DataVector(N);
  auto stddev = DataVector(N);
  auto sample = std::vector<Complex>(N, 0);
  for (float_t i = 0.; i < K; i += 1.){
    int c = 0;
    while (c < N && c + N * i < au.hdr.dataSize / sizeof(I16)){
      sample[c] = au.dataVector[c + N * i];
      c++;
    }
    ite_dit_fft(sample);
    for (float_t j = 0.; j < N; j += 1.){
      sample[j] = (pow(sample[j].real(), 2) + pow(sample[j].imag(), 2)) / N;
      avg[j] = i / (i + 1) * avg[j] + (sample[j].real() / (i + 1));
      stddev[j] += (pow((i + 2) * sample[j].real() - avg[j] * (i + 1), 2) / (i + 2) / (i + 1));
    }
    sample = std::vector<Complex>(N, 0);
  }
  for (auto& it: stddev){
    it = sqrt(it);
  }
  datafile.close();
  std::ofstream outfile;
  outfile.open("../features.csv", std::ios::out | std::ios::app);
  outfile << avg << "," << stddev << "," << file_path << "\n";
  outfile.close();
}

int main(){
  std::string dir_path = "../archive/genres";
  for (auto& genres : std::filesystem::directory_iterator(dir_path)){
    std::string subdir_path = genres.path().string();
    for (auto& entry : std::filesystem::directory_iterator(subdir_path)){
      std::string file_path = entry.path().string();
      std::cout << file_path << '\n';
      feature_extraction(file_path);
    }
  }
}
