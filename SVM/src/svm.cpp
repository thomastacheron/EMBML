#include <vector>
#include <iostream>
#include "load_utils.h"

int main()
{
  // Load parameters
  std::vector<std::vector<double>> coef = load_npy_txt_2d("../src/storage/coef.txt");
  std::vector<double> scale = load_npy_txt("../src/storage/scale.txt");
  std::vector<double> mean = load_npy_txt("../src/storage/mean.txt");
  std::vector<double> intercept = load_npy_txt("../src/storage/intercept.txt");

  // Load and normalize features
  std::vector<std::vector<double>> features;
  std::vector<int> labels;

  load_test_set(features, labels);
  normalize(features, mean, scale);

  // Predict the class labels with an svm
  std::cout << "features.size(): " << features.size() << '\n';
  std::cout << "coef.size(): " << coef.size() << '\n';

  std::vector<int> predictions(features.size());
  float percent = 0;
  for (size_t i = 0; i < features.size(); i++) {
    double max_score = -1e18;
    int max_idx = -1;
    for (size_t j = 0; j < coef.size(); j++) {
      double score = 0;
      for (size_t k = 0; k < 1024 ; k++) {
        score += coef[j][k] * features[i][k];
      }
      score += intercept[j];
      if (score > max_score) {
        max_score = score;
        max_idx = j;
      }
    }
    predictions[i] = max_idx;
    if (predictions[i] == labels[i]){percent++;}
  }

  std::cout << "We found : "<< percent/features.size()*100. << "%" << '\n';

  return 0;
}
