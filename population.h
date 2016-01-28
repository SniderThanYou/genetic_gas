#pragma once

#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

template<class Specimen>
class Population {
public:
  Population() : specimens(POPULATION_SIZE) {}

  void update_fitness() {
    for (Specimen& s : specimens) {
      s.update_fitness();
    }
  }

  void sort_by_fitness() {
    std::sort(specimens.begin(), specimens.end());
  }

  void print_best() const {
    std::cout << "Best: " << specimens.front().to_s() << std::endl;
  }

  bool has_ideal_specimen() const {
    return specimens.front().is_ideal();
  }

  void mate() {
    std::vector<Specimen> next_generation(POPULATION_SIZE);
    size_t num_elites = (size_t)(ELITISM_RATE * POPULATION_SIZE);

    for (size_t i = 0; i < num_elites; i++) {
      next_generation[i] = specimens[i];
    }

    for (size_t i = num_elites; i < POPULATION_SIZE; i++) {
      const Specimen& mother = random_specimen();
      const Specimen& father = random_specimen();
      Specimen child = mother.child_with(father);

      static std::default_random_engine generator;
      static std::bernoulli_distribution distribution(MUTATION_RATE);
      bool should_mutate = distribution(generator);
      if (should_mutate) {
        child.mutate();
      }

      next_generation[i] = child;
    }

    specimens.swap(next_generation);
  }

private:
  std::vector<Specimen> specimens;

  const Specimen& random_specimen() {
    return specimens[std::rand() % specimens.size()];
  }

  static constexpr double ELITISM_RATE = 0.1;
  static constexpr double MUTATION_RATE = 0.25;
  static constexpr size_t POPULATION_SIZE = 2048;
};
