#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

int main()
{
  // Load the parameters from the files
  std::vector<double> scale(1024);
  std::vector<double> mean(1024);
  std::vector<double> intercept(10);
  // std::vector<std::vector<double>> coef(10);

  std::ifstream coef_file("coef.npy", std::ios::binary);
  // Initialize the 2D vector with the correct size
  int rows = 10;
  int cols = 1024;
  std::vector<std::vector<double>> coef(rows, std::vector<double>(cols));

  // Read the data into the vector
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      coef_file.read(reinterpret_cast<char*>(&coef[i][j]), sizeof(double));
    }
  }
  coef_file.close();

  // // Print the 2D vector to check that it was loaded correctly
  // for (int i = 0; i < rows; i++) {
  //   for (int j = 0; j < cols; j++) {
  //     std::cout << (double)coef[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }

  std::ifstream file("../src/scale.npy", std::ios::binary);
  char buffer[8];
  file.read(buffer, sizeof(buffer));

  unsigned short int header_length;
  file.read(reinterpret_cast<char*>(&header_length), sizeof(header_length));
  std::cout << header_length << '\n';
  // file.seekg(header_length);
  std::cout << file.tellg() << '\n';

  file.read(reinterpret_cast<char*>(scale.data()), scale.size() * sizeof(double));
  file.close();
  std::cout << scale[0] << '\n';

  file.open("../src/mean.npy", std::ios::binary);
  file.read(reinterpret_cast<char*>(mean.data()), mean.size() * sizeof(double));
  file.close();

  file.open("../src/intercept.npy", std::ios::binary);
  file.read(reinterpret_cast<char*>(intercept.data()), intercept.size() * sizeof(double));
  file.close();

  // Load the input features from the file
  std::vector<std::vector<double>> features;
  std::string line;
  std::ifstream input_file("../../Features/features.csv");

  while (1) {
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

    // Add the last value in the line to the feature vector
    features.push_back(feature);
  }
  input_file.close();



  for (size_t i = 0; i < features.size(); i++) {
    for (size_t j = 0; j < features[i].size(); j++) {
      features[i][j] = (features[i][j] - mean[j]) / scale[j];
    }
  }

  // Predict the class labels
  std::cout << "features.size(): " << features.size() << '\n';
  std::cout << "coef.size(): " << coef.size() << '\n';

  std::vector<int> predictions(features.size());
  for (size_t i = 0; i < features.size(); i++) {
    double max_score = -1e18;
    int max_idx = -1;
    for (size_t j = 0; j < coef.size(); j++) {
      double score = 0;
      for (size_t k = 0; k < coef.size(); k++) {
        score += coef[j][k] * features[i][k];
      }
      score += intercept[j];
      if (score > max_score) {
        max_score = score;
        max_idx = j;
      }
    }
    predictions[i] = max_idx;
    // std::cout << predictions[i] << '\n';
  }

  return 0;
}
