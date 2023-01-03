#include <fstream>
#include <vector>

int main()
{
  // Load the parameters from the files
  std::vector<double> scale, mean, coef, intercept;

  std::ifstream file("scale.npy", std::ios::binary);
  file.read(reinterpret_cast<char*>(scale.data()), scale.size() * sizeof(double));
  file.close();

  file.open("mean.npy", std::ios::binary);
  file.read(reinterpret_cast<char*>(mean.data()), mean.size() * sizeof(double));
  file.close();

  file.open("coef.npy", std::ios::binary);
  file.read(reinterpret_cast<char*>(coef.data()), coef.size() * sizeof(double));
  file.close();

  file.open("intercept.npy", std::ios::binary);
  file.read(reinterpret_cast<char*>(intercept.data()), intercept.size() * sizeof(double));
  file.close();

  // Standardize the features
  std::vector<double> features = /* input features */;
  for (int i = 0; i < features.size(); i++) {
    features[i] = (features[i] - mean[i]) / scale[i];
  }

  // Predict the class labels
  int num_samples = features.size() / coef.size();
  std::vector<int> predictions(num_samples);
  for (int i = 0; i < num_samples; i++) {
    double max_score = -1e18;
    int max_idx = -1;
    for (int j = 0; j < coef.size(); j++) {
      double score = 0;
      for (int k = 0; k < coef.size(); k++) {
        score += coef[k] * features[i * coef.size() + k];
      }
      score += intercept[0];
      if (score > max_score) {
        max_score = score;
        max_idx = j;
      }
    }
    predictions[i] = max_idx;
  }

  return 0;
}
