#pragma once

#include <string>
#include <random>

template<class Range, class UnaryFunction> inline
void erase_if(Range& range, UnaryFunction f) {
  range.erase(std::remove_if(range.begin(), range.end(), f), range.end());
}

template<class Range, class UnaryFunction> inline
bool any_of(const Range& range, UnaryFunction f) {
  return std::any_of(range.begin(), range.end(), f);
}

double square(double x) {
  return x * x;
}



















struct City {
  std::string name;
  double latitude;
  double longitude;
};

static const std::vector<City> cities = {
    {"Tallahassee", 2500, 1800},
    {"Indianapolis", 1900, 600},
    {"Los Angeles", 150, 1100},
    {"Portland", 90, 250},
    {"San Antonio", 1200, 1400},
    {"Boston", 2700, 315},
    {"St. Louis", 1700, 950},
    {"Topeka", 1125, 1200},
    {"Las Vegas", 450, 1000},
    {"New York City", 2675, 400},
    {"Chicago", 1750, 250},
    {"New Orleans", 1650, 1515},
    {"Denver", 750, 900}
};

class SalesmanSpecimen {
public:
  SalesmanSpecimen() : SalesmanSpecimen(random_genes()) {}

  void update_fitness() {
    double distance = 0;
    for (size_t i = 0; i < genes.size() - 1; i++) {
      double x1 = cities[genes[i]].latitude;
      double x2 = cities[genes[i + 1]].latitude;
      double y1 = cities[genes[i]].longitude;
      double y2 = cities[genes[i + 1]].longitude;
      distance += std::sqrt(square(x1 - x2) + square(y1 - y2));
    }
    fitness = distance;
  }

  bool is_ideal() const {
    return fitness == 0;
  }

  SalesmanSpecimen child_with(const SalesmanSpecimen& other_parent) const {
    size_t num_genes = genes.size();
    size_t start = rand() % num_genes;
    size_t end = rand() % num_genes;

    std::vector<size_t> genes_from_self;
    for (size_t i = start; i < end; i++) {
      genes_from_self.push_back(genes[i]);
    }

    std::vector<size_t> genes_from_other = other_parent.genes;
    erase_if(genes_from_other, [&](size_t gene_from_other){
      return any_of(genes_from_self, [=](size_t gene_from_self) {
        return gene_from_self == gene_from_other;
      });
    });

    std::vector<size_t> child_genes(num_genes);
    for (size_t i = 0, self_idx = 0, other_idx = 0; i < genes.size(); i++) {
      if (start <= i && i < end) {
        child_genes[i] = genes_from_self[self_idx++];
      } else {
        child_genes[i] = genes_from_other[other_idx++];
      }
    }

    return SalesmanSpecimen(child_genes);
  }

  void mutate() {
    size_t i1 = rand() % genes.size();
    size_t i2 = rand() % genes.size();
    std::swap(genes[i1], genes[i2]);
  }

  bool operator<(const SalesmanSpecimen& other) {
    return this->fitness < other.fitness;
  }

  std::string to_s() const {
    std::string s;
    s += "{";
    for (size_t i = 0; i < genes.size(); i++) {
      if (i != 0) {
        s += ", ";
      }
      s += cities[genes[i]].name;
    }
    s += "}";
    s += " (" + std::to_string(fitness) + ")";
    return s;
  }

private:
  std::vector<size_t> genes;
  double fitness;

  SalesmanSpecimen(const std::vector<size_t>& genes) : genes(genes) {}

  static std::vector<size_t> random_genes() {
    std::vector<size_t> s;
    for (size_t i = 0; i < cities.size(); i++) {
      s.push_back(i);
    }
    std::shuffle(s.begin(), s.end(), std::default_random_engine());
    return s;
  }
};
