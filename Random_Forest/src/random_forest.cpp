#include "random_forest.h"
#include "load_utils.h"
#include <iostream>

int main(){

  // Load parameters
  std::vector<double> scale = load_npy_txt("../src/storage/scale.txt");
  std::vector<double> mean = load_npy_txt("../src/storage/mean.txt");

  // Load and normalize features
  std::vector<std::vector<double>> features;
  std::vector<int> labels;

  load_test_set(features, labels);
  normalize(features, mean, scale);

  // Predict the class labels with a random forest
  std::cout << "features.size(): " << features.size() << '\n';

  std::vector<int> predictions;
  float percent = 0;
  for (const auto& feature : features){
    predictions.push_back(random_forest(feature));
  }
  for (size_t i = 0; i < features.size(); i++){
    if (predictions[i] == labels[i]){percent++;}
  }
  std::cout << "We found : "<< percent/features.size()*100. << "%" << '\n';
  
}
