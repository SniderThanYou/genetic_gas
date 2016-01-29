#include "population.h"
#include "gas_specimen.h"
#include "gauss_specimen.h"
#include "sequential_specimen.h"
#include "salesman_specimen.h"

int main() {
  srand((unsigned int)time(NULL));
  int MAX_ITERATIONS = 16384;

  Population<SalesmanSpecimen> population;
  for (size_t i = 0; i < MAX_ITERATIONS; i++) {
    population.update_fitness();
    population.sort_by_fitness();
    population.print_best();
    if (population.has_ideal_specimen()) {
      break;
    }
    population.mate();
  }

  return 0;
}