all: findClient findServer format finder findAttributes msgQueue forkHelper
	g++ -o main main.cpp findClient.o findServer.o format.o finder.o findAttributes.o msgQueue.o forkHelper.o
	cp main ../testing
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
msgQueue:
	g++ -c -Wall messageQueue/msgQueue.h messageQueue/msgQueue.cpp
forkHelper:
	g++ -c -Wall helper/forkHelper.h helper/forkHelper.cpp

clean:
	find . -type f -name '*.h.gch' -delete -o -name '*.o' -delete

