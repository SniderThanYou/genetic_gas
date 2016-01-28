#pragma once

#include <string>
#include <random>

static const size_t NUM_GAUSS_PARAMS = 3;

static const std::vector<double> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static const std::vector<double> y = {0, 1, 3, 9, 11, 8, 4, 2, 1, 0};

double gauss(double t, double a, double b, double c) {
  return a * std::exp(-0.5 * std::pow((t - b) / c, 2));
}

std::vector<double> gauss(const std::vector<double>& t, double a, double b, double c) {
  std::vector<double> ret;
  for (double x : t) {
    ret.push_back(gauss(x, a, b, c));
  }
  return ret;
}

class GaussSpecimen {
public:
  GaussSpecimen() : GaussSpecimen(random_genes()) {}

  void update_fitness() {
    std::vector<double> inten = gauss(x, genes[0], genes[1], genes[2]);
    double sum_of_sq_error = 0;
    for (size_t i = 0; i < inten.size(); i++) {
      double diff = inten[i] - y[i];
      sum_of_sq_error += diff * diff;
    }
    fitness = sum_of_sq_error;
  }

  bool is_ideal() const {
    return fitness == 0;
  }

  GaussSpecimen child_with(const GaussSpecimen& other_parent) const {
    size_t num_genes = genes.size();
    size_t spos = rand() % num_genes;
    std::vector<double> child_genes(num_genes);
    for (size_t i = 0; i < spos; i++) {
      child_genes[i] = genes[i];
    }
    for (size_t i = spos; i < num_genes; i++) {
      child_genes[i] = other_parent.genes[i];
    }
    return GaussSpecimen(child_genes);
  }

  void mutate() {
    size_t i = rand() % genes.size();

    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution(-1.1, 1.1);

    genes[i] *= distribution(generator);
  }

  bool operator<(const GaussSpecimen& other) {
    return this->fitness < other.fitness;
  }

  std::string to_s() const {
    return "{" + std::to_string(genes[0]) + ", " + std::to_string(genes[1]) + ", " + std::to_string(genes[2]) + "}" + " (" + std::to_string(fitness) + ")";
  }

private:
  std::vector<double> genes;
  double fitness;

  GaussSpecimen(const std::vector<double>& genes) : genes(genes) {}

  static std::vector<double> random_genes() {
    std::vector<double> s;
    for (int j = 0; j < NUM_GAUSS_PARAMS; j++) {
      s.push_back(random_gene());
    }
    return s;
  }

  static double random_gene() {
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution(-1e6, 1e6);
    return distribution(generator);
  }
};
