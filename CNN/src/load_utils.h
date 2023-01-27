#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

std::vector<double> load_npy_txt(const std::string& filepath) {
  std::vector<double> array;
  std::ifstream input_file(filepath);
  std::string line;
  while (std::getline(input_file, line)) {
    std::stringstream line_stream(line);
    double value;
    while (line_stream >> value) {
      array.push_back(value);
    }
  }
  input_file.close();
  return array;
}

std::vector<std::vector<double>> load_npy_txt_2d(const std::string& filepath) {
    std::vector<std::vector<double>> array;
    std::ifstream input_file(filepath);

    // Read the file line by line
    std::string line_array;
    while (std::getline(input_file, line_array)) {
        std::stringstream line_stream(line_array);
        std::vector<double> row;
        double value;
        while (line_stream >> value) {
            row.push_back(value);
        }
        array.push_back(row);
    }
    input_file.close();
    return array;
}

void load_test_set(std::vector<std::vector<double>>& features, std::vector<int>& labels){
  // Load the input features from the file
  std::string line;
  std::ifstream input_file("../src/storage/test_set.csv");
  while (true) {
    std::getline(input_file, line);
    if (input_file.eof()) {
      std::cout << "~~ End of file ~~\n" << '\n';
      break;
    }

    std::vector<double> feature;
    size_t pos = 0;
    while ((pos = line.find(',')) != std::string::npos && feature.size() < 1024) {
      std::string value = line.substr(0, pos);
      feature.push_back(std::stod(value));  // Convert the value to a double and add it to the feature vector
      line.erase(0, pos + 1);  // Erase the value and the comma from the line string
    }

    std::string label = line.substr(pos + 1, pos);

    if(label == "blues"){labels.push_back(0);}
    if(label == "classical"){labels.push_back(1);}
    if(label == "country"){labels.push_back(2);}
    if(label == "disco"){labels.push_back(3);}
    if(label == "hiphop"){labels.push_back(4);}
    if(label == "jazz"){labels.push_back(5);}
    if(label == "metal"){labels.push_back(6);}
    if(label == "pop"){labels.push_back(7);}
    if(label == "reggae"){labels.push_back(8);}
    if(label == "rock"){labels.push_back(9);}

    // Add the last value in the line to the feature vector
    features.push_back(feature);
  }
  input_file.close();
}

void normalize(std::vector<std::vector<double>>& features, std::vector<double>& mean, std::vector<double>& scale){
  for (size_t i = 0; i < features.size(); i++) {
    for (size_t j = 0; j < features[i].size(); j++) {
      features[i][j] = (features[i][j] - mean[j]) / scale[j];
    }
  }
}
