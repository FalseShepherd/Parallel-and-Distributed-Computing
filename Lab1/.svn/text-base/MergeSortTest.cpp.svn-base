// Tests for MergeSort

#include "ParallelMergeSort.h"
#include "MergeSort.h"

#include "Timer.h"

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

namespace {               // unnamed namespace for local functions

	void FillRandom(std::vector<double> &a) {
		std::minstd_rand r;  // pseudo-random number generator
		std::default_random_engine e(r());

		for (double &v : a) {
			v = std::generate_canonical<double, 1>(e);
		}
	}

	void TestMergeSort(size_t aSize) {
		// Create a vector of the specified size, fill it with random numbers
		std::vector<double> a1(aSize);
		FillRandom(a1);
		auto a2 = a1;  // extra copy for verification

		std::vector<double> a3(aSize);
		FillRandom(a3);
		auto a4 = a3; // extra copy for verification

		std::vector<double> tmp(a1.size());
		std::vector<double> tmp2(a3.size());

		// Sort using MergeSort, sort copy using C++ library routine
		Timer t;
		MergeSort(a1, tmp, 0, a1.size() - 1);
		double elapsed = t.GetElapsedTime();
		

		// Sort using MergeSort, sort copy using C++ library routine
		Timer t2;
		ParallelMergeSort(a3, tmp2, 0, a3.size() - 1);
		double elapsed2 = t2.GetElapsedTime();

		std::sort(a2.begin(), a2.end());
		std::sort(a4.begin(), a4.end());

		// Check by comparing result to copy
		for (size_t i = 0; i < a1.size(); ++i) {
			if (a1[i] != a2[i]) {
				std::cout << "a1 mismatch at index " << i << ", aSize = " << aSize << std::endl;
				exit(1);
			}
			if (a3[i] != a4[i]) {
				std::cout << "a1 mismatch at index " << i << ", aSize = " << aSize << std::endl;
				exit(1);
			}
		}
		std::cout << "Done testing at size " << aSize << ", time = " << elapsed << " sec.\n";
		std::cout << "Done testing in Parallel at size " << aSize << ", time = " << elapsed2 << " sec.\n";
	}

} // namespace

int main(int argc, char *argv[]) {
	TestMergeSort(5000);
}

