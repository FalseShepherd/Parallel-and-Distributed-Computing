#pragma once
// TransitiveClosure
//
// Use Warshall's algorithm to compute the transitive closure of a boolean relation
// represented as a square 2D array.

#include "TransitiveClosure.h"
#include <omp.h>
#include <iostream>
//void TransitiveClosure(const vector<vector<uint8_t>> &r,
//	vector<vector<uint8_t>> &t) {
//	omp_set_num_threads(4);
//#pragma omp parallel
//	{
//#pragma omp single nowait
//		std::cout << "threads=" << omp_get_num_threads() << std::endl;
//		TransitiveClosureHelper(r,t);
//	}
//}
void TransitiveClosure(const vector<vector<uint8_t>> &r,
                       vector<vector<uint8_t>> &t) {
  const size_t n = r.size();  // size of matrix
  // Temporary matrix for intermediate results
  vector<vector<uint8_t>> m(n);
#pragma omp for schedule(dynamic,4)
  for (auto &mRow : m) mRow.resize(n);

  // Initialize t to be the starting matrix
  t = r;
  //all collapsable for loops have the following pragma for the more optimal solution as a comment
  //#pragma omp parallel for schedule(dynamic,1) collapse(3)
#pragma omp for schedule(dynamic,4)
  for (size_t k = 0; k < n; ++k) {
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < n; ++j) {
        // Put result in m
        m[i][j] = t[i][j] || (t[i][k] && t[k][j]);
      }
    }
    // Swap latest iteration result back to t (swap is efficient, it doesn't
    // move any data, just some private pointers to the data)
    std::swap(m, t);
  }
}
