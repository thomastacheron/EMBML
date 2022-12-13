#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Définition de la structure de données pour stocker les données d'entraînement
struct TrainingData {
  vector<double> inputs;
  int label;
};

// Fonction d'entraînement de la SVM qui prend en paramètre un tableau de données d'entraînement
void train(vector<TrainingData> data) {
  // TODO: implémenter l'algorithme de l'entraînement de la SVM linéaire ici
}

int main() {
  // Exemple de données d'entraînement
  vector<TrainingData> data = {
    {{1, 2, 3}, 1},
    {{4, 5, 6}, -1},
    {{7, 8, 9}, 1}
  };

  // Appel de la fonction d'entraînement
  train(data);

  return 0;
}
