CPPFLAGS = -std=c++11 -O2 -Wall -fopenmp

MergeSortTest: MergeSortTest.o MergeSort.o ParallelMergeSort.o  Timer.o
	g++ $(CPPFLAGS) -o $@ $^

MergeSortTest.o: MergeSortTest.cpp MergeSort.h ParallelMergeSort.h Timer.h

MergeSort.o: MergeSort.cpp MergeSort.h 

ParallelMergeSort.o: ParallelMergeSort.cpp ParallelMergeSort.h

Timer.o: Timer.cpp Timer.h

clean:
	rm *.o MergeSortTest
