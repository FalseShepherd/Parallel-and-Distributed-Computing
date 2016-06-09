#pragma omp taskqueue
#pragma omp taskwait

// MergeSort - recursive merge-sort of a vector

#include "ParallelMergeSort.h"
#include <limits>
#include <cassert>
#include <iostream>
#include <omp.h>

namespace {               // unnamed namespace for local functions

						  // Private merge function

	void Merge(std::vector<double> &a,std::vector<double> &tmp,size_t first,size_t mid,size_t last) {
		size_t low_next = first;
		size_t high_next = mid + 1;
		double low_val = a[low_next];
		double high_val = a[high_next];
		#pragma omp parallel for
		for (size_t dest = first; dest <= last; ++dest) {
			if (low_val <= high_val) {
				// Smallest value is from low segment
				tmp[dest] = low_val;
				// Get next value; set to infinite if no more values
				if (++low_next <= mid) {
					low_val = a[low_next];
				}
				else {
					low_val = std::numeric_limits<double>::infinity();
				}
			}
			else {
				// Smallest value is from high segment
				tmp[dest] = high_val;
				// Get next value; set to infinite if no more values
				if (++high_next <= last) {
					high_val = a[high_next];
				}
				else {
					high_val = std::numeric_limits<double>::infinity();
				}
			}
		}
		// Copy range back from tmp to a
		std::copy(tmp.begin() + first, tmp.begin() + last + 1, a.begin() + first);
	}

} // namespace
void ParallelMergeSort(std::vector<double> &a,
	std::vector<double> &tmp,
	size_t first,
	size_t last){
	omp_set_num_threads(4);
#pragma omp parallel
	{
	#pragma omp single nowait
	std::cout << "threads=" << omp_get_num_threads() << std::endl;
	PMergeSort(a, tmp, first, last);
	}
}


void PMergeSort(std::vector<double> &a,
	std::vector<double> &tmp,
	size_t first,
	size_t last) {
	assert(a.size() == tmp.size() && first >= 0 && last < a.size());

	if (first >= last) return;  // exit if down to 1 item

	// Recursively sort each half of the array
	size_t mid = (first + last) / 2;
	#pragma omp task shared(a,tmp)
	PMergeSort(a, tmp, first, mid);
	#pragma omp task shared(a,tmp)
	PMergeSort(a, tmp, mid + 1, last);

	// Merge the two sorted halves into the tmp array
	#pragma omp barrier
	Merge(a, tmp, first, mid, last);
}

