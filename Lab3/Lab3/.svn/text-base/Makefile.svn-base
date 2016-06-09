CPPFLAGS = -std=c++11 -msse2 -m64 -O2 -I${AMDAPPSDKROOT}/include

Lab3: Lab3.o
	g++ $(CPPFLAGS) -L${AMDAPPSDKROOT}/lib/x86_64 -o $@ $^ -lOpenCL

Lab3.o: Lab3.cpp SDKBitMap.hpp SDKFile.hpp SDKUtil.hpp

clean:
	rm -f *.o Lab3
