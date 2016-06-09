CPPFLAGS = -std=c++11 -msse2 -m64 -O0 -g -I${AMDAPPSDKROOT}/include
#CPPFLAGS = -std=c++11 -msse2 -m64 -O2 -I${AMDAPPSDKROOT}/include -fopenmp

Program2:	Program2.o Timer.o ReadWireWorld.o WriteWireWorld.o
	g++ $(CPPFLAGS) -o $@ $^ -L$(AMDAPPSDKROOT)/lib/x86_64 -lOpenCL

Program2.o: Program2.cpp ReadWireWorld.h

Timer.o: Timer.cpp Timer.h

ReadWireWorld.o: ReadWireWorld.cpp ReadWireWorld.h

WriteWireWorld.o: WriteWireWorld.cpp WriteWireWorld.h

clean:
	rm -f *.o Program2

