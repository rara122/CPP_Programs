all:	ShortestPaths.cpp
	g++ ShortestPaths.cpp -o run
clean:	
	rm -f *.o output.txt run
