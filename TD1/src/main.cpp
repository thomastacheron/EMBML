#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <netinet/in.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef uint32_t U32;

#pragma pack(push, 1)
struct Bin{
  U32 magicNumber;
  U32 dataOffset;
  U32 dataSize;
  U32 encoding;
  U32 sampleRate;
  U32 channels;
};
#pragma pack(pop)

void be2le(U32& be, U32& le){ // big-endian to little-endian
  le = ntohl(be);
}

void convert(Bin& bin){
   bin.magicNumber = ntohl(&bin.magicNumber);
   bin.dataOffset = ntohl(&bin.dataOffset);
   bin.dataSize = ntohl(&bin.dataSize);
   bin.encoding = ntohl(&bin.encoding);
   bin.sampleRate = ntohl(&bin.sampleRate);
   bin.channels = ntohl(&bin.channels);
}

std::ostream& operator<<(std::ostream& os, const Bin& bin){
    os << "magicNumber : " << bin.magicNumber << "\n";
    os << "dataOffset : " << bin.dataOffset << "\n";
    os << "dataSize : " << bin.dataSize << "\n";
    os << "encoding : " << bin.encoding << "\n";
    os << "sampleRate : " << bin.sampleRate << "\n";
    os << "channels : " << bin.channels << "\n";
    return os;
}

int main(){

}
