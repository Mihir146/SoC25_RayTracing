main: main.o 
	$(CXX) main.o -o main

main.o: main.cpp vec3.h
	$(CXX) -c main.cpp -o main.o

clean:
	rm main.o



