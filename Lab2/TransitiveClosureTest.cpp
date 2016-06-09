// TransitiveClosureTest
//
// Timing and tests for transitive closure using Warshall's algorithm.
/*NOTE: found that using #pragma omp for collapse(n) was faster for nested for loops. likely due to less threads 
being spawned and less overhead computing as a result*/

#include "TransitiveClosure.h"
#include "Timer.h"
#include <omp.h>
#include <iostream>
#include <vector>

using std::vector;

int main(int argc, char *argv[]) {
	//can adjust number of threads here. 
	omp_set_num_threads(4);
  Timer totalTime;

  const size_t n = 1024;  // matrix size

  vector<vector<uint8_t>> r(n);
  #pragma omp for schedule(dynamic,1)
  for (size_t row = 0; row < n; ++row) {
    r[row].resize(n, false);
  }
  auto t = r;

  // Initialize r such that R(i, (i+1)%n) is true for all i in [0..n-1]
  #pragma omp for schedule(dynamic,4)
  for (size_t i = 0; i < n; ++i) {
    r[i][(i+1)%n] = true;
  }

  Timer timer1;
#pragma omp parallel
  {
	  omp_set_num_threads(4);
	  TransitiveClosure(r, t);
  }
  std::cout << "Time for TransitiveClosure of size " << n
            << " = " << timer1.GetElapsedTime() << " sec.\n";

  // Result should be fully populated with true
  //all collapsable for loops have the following pragma for the more optimal solution as a comment
  //#pragma omp parallel for schedule(dynamic,4) collapse(2)
#pragma omp parallel for schedule(dynamic,4)
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (!t[i][j]) {
        std::cerr << "Test 1 error at t[" << i << "][" << j << "]\n";
      }
    }
  }

  // Now modify r such that even rows are connected to even, odd to odd.
  // This test requires that n must be even.
#pragma omp parallel for schedule(dynamic,1)
  for (size_t i = 0; i < n; ++i) {
    r[i][(i+1)%n] = false;
    r[i][(i+2)%n] = true;
  }

  Timer timer2;
#pragma omp parallel
  {
	  TransitiveClosure(r, t);
  }
  std::cout << "Time for TransitiveClosure of size " << n
            << " = " << timer2.GetElapsedTime() << " sec.\n";

  // Result should have true in even entries in even rows, odd entries in odd rows
  //all collapsable for loops have the following pragma for the more optimal solution as a comment
  //#pragma omp parallel for schedule(dynamic,1) collapse(3)
#pragma omp parallel for schedule(dynamic,1)
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (t[i][j] == ((i ^ j) & 1)) {
        std::cerr << "Test 2 error at t[" << i << "][" << j << "]\n";
      }
    }
  }

  std::cout << "Total elapsed time = " << totalTime.GetElapsedTime() << std::endl;
}
