#include <iostream>
#include <fstream>
#include <cassert>
#include <netinet/in.h>
#include "constants.h"
#include "fft_utils.h"

typedef uint16_t U16;
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

int main(){
  std::string file_path = "../archive/genres/blues/blues.00000.au";
  std::ifstream datafile;
  datafile.open(file_path.c_str(), std::ios::binary | std::ios::in);
  if(!datafile.is_open())
    throw "Unable to load data file";

  Header hdr;
  U16 data;
  datafile.read((char*)&hdr, sizeof(hdr));
  convert(hdr);
  assert(hdr.magicNumber == 0x2e736e64);
  std::cout << hdr << '\n';
  datafile.seekg(hdr.dataOffset * sizeof(U32));
  while (!datafile.eof()){
    datafile.read((char*)&data, sizeof(data));
    if (datafile.eof()){
      std::cout << "EOF" << '\n';
      break;
    }
    data = ntohs(data);
<<<<<<< HEAD
    // std::cout << data << '\n';
=======
    // std::cout << data;
>>>>>>> cdec74bb5e4304e7a387e716e66cf730fdf92836
  }
  datafile.close();
}

/* NOTES */
// ntohs : 16 bites
// ntohl : 32 bites
