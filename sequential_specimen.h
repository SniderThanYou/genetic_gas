#pragma once

#include <string>
#include <random>

class SequentialSpecimen {
public:
  SequentialSpecimen() : SequentialSpecimen(random_genes()) {}

  void update_fitness() {
    fitness = 0;
    for (size_t i = 0; i < genes.size() - 1; i++) {
      if (genes[i + 1] == genes[i] + 1) {
        fitness += genes[i];
      } else if (genes[i + 1] <= genes[i]) {
        fitness -= 10 * genes[i];
      }
    }
  }

  bool is_ideal() {
    for (size_t i = 0; i < genes.size() - 1; i++) {
      if (genes[i + 1] != genes[i] + 1) {
        return false;
      }
    }
    return true;
  }

  SequentialSpecimen child_with(const SequentialSpecimen& other_parent) const {
    size_t num_genes = genes.size();
    size_t spos = rand() % num_genes;
    std::string child_genes = this->genes.substr(0, spos) + other_parent.genes.substr(spos, num_genes);
    return SequentialSpecimen(child_genes);
  }

  void mutate() {
    size_t i = rand() % genes.size();
    genes[i] = random_gene();
  }

  bool operator<(const SequentialSpecimen& other) {
    return this->fitness > other.fitness;
  }

  std::string to_s() {
    return genes + " (" + std::to_string(fitness) + ")";
  }

private:
  std::string genes;
  int fitness;

  SequentialSpecimen(const std::string& genes) : genes(genes) {}

  static std::string random_genes() {
    std::string s;
    for (int j = 0; j < 20; j++) {
      s += random_gene();
    }
    return s;
  }

  static char random_gene() {
    static std::default_random_engine generator;
    static std::uniform_int_distribution<char> distribution(32, 112);
    return distribution(generator);
  }
};
