#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <vector>
#include <numeric>
#include <math.h>

typedef uint32_t U32;
typedef uint16_t U16;
typedef int16_t I16;
typedef std::vector<float_t> DataVector;


#pragma pack(push, 1)
struct Header_wav{
    U32 FileTypeBlocID; // FileTypeBlocID is 'RIFF'
    U32 FileSize;
    U32 FileFormatID; // FileFormatID is 'WAVE'


    U32 FormatBlocID; // FormatBlocID is 'fmt '
    U32 BlocSize; // BlocSize is 16
    U16 AudioFormat; // 1: PCM entier, 3: PCM flottant, 65534: WAVE_FORMAT_EXTENSIBLE
    U16 NbrCanaux;
    U32 Frequence;
    U32 BytePerSec;
    U16 BytePerBloc;
    U16 BitsPerSample;
};
#pragma pack(pop)

struct Wav{
    Header_wav hdr;
    U32 DataBlocID;
    U32 DataSize;
    DataVector dataVector;
};

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

std::ostream& operator<<(std::ostream& os, const Wav& wav){
    os << "======= .wav file =======" << "\n";
    os << "FileTypeBlocID : " << std::hex << wav.hdr.FileTypeBlocID << std::dec << "\n";
    os << "FileSize : " << wav.hdr.FileSize << "\n";
    os << "FileFormatID : " << std::hex << wav.hdr.FileFormatID << std::dec << "\n";
    os << "FormatBlocID : " << std::hex << wav.hdr.FormatBlocID << std::dec << "\n";
    os << "BlocSize : " << wav.hdr.BlocSize << "\n";
    os << "AudioFormat : " << wav.hdr.AudioFormat << "\n";
    os << "NbrCanaux : " << wav.hdr.NbrCanaux << "\n";
    os << "Frequence : " << wav.hdr.Frequence << "\n";
    os << "BytePerSec : " << wav.hdr.BytePerSec << "\n";
    os << "BytePerBloc : " << wav.hdr.BytePerBloc << "\n";
    os << "BitsPerSample : " << wav.hdr.BitsPerSample << "\n";
    os << "DataBlocID : " << std::hex << wav.DataBlocID << std::dec << "\n";
    os << "DataSize : " << wav.DataSize << "\n";
    os << "========================";
    return os;
}

void load_wav(std::ifstream& datafile, Wav& wav){

    datafile.read(reinterpret_cast<char*>(&wav.hdr), sizeof(wav.hdr));
    assert(wav.hdr.FileTypeBlocID == 0x46464952); // FileTypeBlocID is 'RIFF'
    assert(wav.hdr.FileFormatID == 0x45564157); // FileFormatID is 'WAVE'
    assert(wav.hdr.FormatBlocID == 0x20746d66); // FormatBlocID is 'fmt '
    assert(wav.hdr.BlocSize == 16); // BlocSize is 16
    assert(wav.hdr.AudioFormat == 1 || wav.hdr.AudioFormat == 3 || wav.hdr.AudioFormat == 65534); // 1: PCM entier, 3: PCM flottant, 65534: WAVE_FORMAT_EXTENSIBLE
    
    datafile.read(reinterpret_cast<char*>(&wav.DataBlocID), sizeof(wav.DataBlocID));
    assert(wav.DataBlocID == 0x61746164); // DataBlocID is 'data'
    datafile.read(reinterpret_cast<char*>(&wav.DataSize), sizeof(wav.DataSize));

    I16 data;
    while (true){
        datafile.read(reinterpret_cast<char*>(&data), sizeof(data));
        if (datafile.eof()){
            // std::cout << "EOF" << "\n";
            break;
        }
        wav.dataVector.push_back(data);
    }
    std::cout << wav.dataVector << "\n";
    std::cout << wav << "\n";
}

int main(){

    std::ifstream datafile;
    std::string file_path = "../blues.00000.wav";
    datafile.open(file_path.c_str(), std::ios::binary | std::ios::in);
    if(!datafile.is_open())
        throw "Unable to load data file";
    Wav wav;
    load_wav(datafile, wav);

}
