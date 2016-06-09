CPPFLAGS = -fopenmp -std=c++11 -O2 -Wall

TransitiveClosureTest: TransitiveClosureTest.o TransitiveClosure.o Timer.o
	g++ $(CPPFLAGS) -o $@ $^

clean:
	rm -f *.o TransitiveClosureTest
