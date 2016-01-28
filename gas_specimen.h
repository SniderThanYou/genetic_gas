#pragma once

#include <string>
#include <random>

static const std::string TARGET_STRING = "Greetings and salutations!";
static const size_t CHROMOSOME_LENGTH = TARGET_STRING.size();

class GasSpecimen {
public:
  GasSpecimen() : GasSpecimen(random_genes()) {}

  void update_fitness() {
    std::string target = TARGET_STRING;
    fitness = 0;
    for (size_t i = 0; i < target.size(); i++) {
      fitness += std::abs(genes[i] - target[i]);
    }
  }

  bool is_ideal() const {
    return fitness == 0;
  }

  GasSpecimen child_with(const GasSpecimen& other_parent) const {
    size_t num_genes = genes.size();
    size_t spos = rand() % num_genes;
    std::string child_genes = this->genes.substr(0, spos) + other_parent.genes.substr(spos, num_genes);
    return GasSpecimen(child_genes);
  }

  void mutate() {
    size_t i = rand() % genes.size();
    genes[i] = random_gene();
  }

  bool operator<(const GasSpecimen& other) {
    return this->fitness < other.fitness;
  }

  std::string to_s() const {
    return genes + " (" + std::to_string(fitness) + ")";
  }

private:
  std::string genes;
  int fitness;

  GasSpecimen(const std::string& genes) : genes(genes) {}

  static std::string random_genes() {
    std::string s;
    for (int j = 0; j < CHROMOSOME_LENGTH; j++) {
      s += random_gene();
    }
    return s;
  }

  static char random_gene() {
    static std::default_random_engine generator;
    static std::uniform_int_distribution<char> distribution;
    return distribution(generator);
  }
};
