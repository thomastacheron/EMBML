#include <iostream>
#include <fstream>
#include <cassert>
#include <netinet/in.h>
#include <vector>
#include <numeric>
#include "constants.h"
#include "fft_utils.h"

typedef int16_t I16;
typedef uint32_t U32;

#pragma pack(push, 1)
struct Header{
  U32 magicNumber;
  U32 dataOffset;
  U32 dataSize;
  U32 encoding;
  U32 sampleRate;
  U32 channels;
};
#pragma pack(pop)

void convert(Header& hdr){
   hdr.magicNumber = ntohl(hdr.magicNumber);
   hdr.dataOffset = ntohl(hdr.dataOffset);
   hdr.dataSize = ntohl(hdr.dataSize);
   hdr.encoding = ntohl(hdr.encoding);
   hdr.sampleRate = ntohl(hdr.sampleRate);
   hdr.channels = ntohl(hdr.channels);
}

std::ostream& operator<<(std::ostream& os, const Header& hdr){
    os << "magicNumber : " << std::hex << hdr.magicNumber << std::dec << "\n";
    os << "dataOffset : " << hdr.dataOffset << "\n";
    os << "dataSize : " << hdr.dataSize << "\n";
    os << "encoding : " << hdr.encoding << "\n";
    os << "sampleRate : " << hdr.sampleRate << "\n";
    os << "channels : " << hdr.channels << "\n";
    return os;
}

// Complex average(std::vector<Complex> const& v){
//   if(v.empty()){
//       return 0;
//   }
//
//   auto const count = static_cast<float>(v.size());
//   return std::reduce(v.begin(), v.end()) / count;
// }
//
// Complex stdev(std::vector<Complex> const& v, Complex const& mean){
//   if(v.empty()){
//       return 0;
//   }
//   Complex s = 0.;
//   float_t const count = static_cast<float>(v.size());
//   for (size_t i = 0; i < count; i++){
//     s += pow(v[i] - mean, 2);
//   }
//   s /= count;
//   s = sqrt(s);
//   return s;
// }

int main(){
  std::string file_path = "../archive/genres/blues/blues.00000.au";
  std::ifstream datafile;
  datafile.open(file_path.c_str(), std::ios::binary | std::ios::in);
  if(!datafile.is_open())
    throw "Unable to load data file";

  Header hdr;
  I16 data;
  std::vector<Complex> v;
  datafile.read((char*)&hdr, sizeof(hdr));
  convert(hdr);
  assert(hdr.magicNumber == 0x2e736e64);
  // std::cout << hdr << '\n';
  datafile.seekg(hdr.dataOffset);
  while (!datafile.eof()){
    datafile.read((char*)&data, sizeof(data));
    if (datafile.eof()){
      // std::cout << "EOF" << '\n';
      break;
    }
    data = ntohs(data);
  // std::cout << data << ',';
  //   Complex cp = data;
  //   v.push_back(cp);
  //   if (v.size() == 512){
  //     ite_dit_fft(v);
  //     // float_t mean = average(v).real();
  //     // float_t std = stdev(v, mean).real();
  //     // std::cout << mean << " " << std << '\n';
  //
  //     // TODO mean, stdev of columns
  //
  //     v = {};
  //   }
  }
  datafile.close();

  // TODO write mean, stdev in a .csv
}
