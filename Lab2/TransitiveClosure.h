// TransitiveClosure
//
// Use Warshall's algorithm to compute the transitive closure of a boolean relation
// represented as a square 2D array.
#ifndef TransitiveClosure_H
#define TransitiveClosure_H

#include <vector>
#include <cstdint>
#include <cstddef>

using std::vector;

// Transitive Closure
//   Uses Warshall's algorithm to compute the transitive closure.  We can't use
//   vector<bool> because it may pack multiple boolean values in a single byte,
//   and is not necessarily thread-safe.  We represent boolean values using 8-bit
//   unsigned integers.
//
// @param r - square matrix defining the relation
// @param t - result matrix (same dimensions as r) containing the result.
void TransitiveClosure(const vector<vector<uint8_t>> &r,
		       vector<vector<uint8_t>> &t);
void TransitiveClosureHelper(const vector<vector<uint8_t>> &r,
	vector<vector<uint8_t>> &t);

#endif // TransitiveClosure_H
