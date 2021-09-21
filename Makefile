all: findClient findServer format finder findAttributes
	g++ -o main main.cpp findClient.o findServer.o format.o finder.o findAttributes.o
findClient:
	g++ -c -Wall findClient.h findClient.cpp
findServer:
	g++ -c -Wall findServer.h findServer.cpp
format:
	g++ -c -Wall findBehaviour/format.h findBehaviour/format.cpp
finder:
	g++ -c -Wall findBehaviour/finder.h findBehaviour/finder.cpp
findAttributes:
	g++ -c -Wall findBehaviour/findAttributes.h findBehaviour/findAttributes.cpp

clean:
	find . -type f -name '*.h.gch' -delete -o -name '*.o' -delete

