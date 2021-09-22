all: findChildProcess findRootProcess formatHelper findAttributes msgQueue forkHelper fileSystemHelper main.cpp findChildProcess.o findRootProcess.o formatHelper.o findAttributes.o msgQueue.o forkHelper.o fileSystemHelper.o
	g++ -o main main.cpp findChildProcess.o findRootProcess.o formatHelper.o findAttributes.o msgQueue.o forkHelper.o fileSystemHelper.o
	cp main ../testing
findChildProcess: findChildProcess.h findChildProcess.cpp
	g++ -c -Wall findChildProcess.h findChildProcess.cpp
findRootProcess: findRootProcess.h findRootProcess.cpp
	g++ -c -Wall findRootProcess.h findRootProcess.cpp
formatHelper: helper/formatHelper.h helper/formatHelper.cpp
	g++ -c -Wall helper/formatHelper.h helper/formatHelper.cpp
findAttributes: findAttributes.h findAttributes.cpp
	g++ -c -Wall findAttributes.h findAttributes.cpp
msgQueue: messageQueue/msgQueue.h messageQueue/msgQueue.cpp
	g++ -c -Wall messageQueue/msgQueue.h messageQueue/msgQueue.cpp
forkHelper: helper/forkHelper.h helper/forkHelper.cpp
	g++ -c -Wall helper/forkHelper.h helper/forkHelper.cpp
fileSystemHelper: helper/fileSystemHelper.h helper/fileSystemHelper.cpp
	g++ -c -Wall helper/fileSystemHelper.h helper/fileSystemHelper.cpp

clean:
	find . -type f -name '*.h.gch' -delete -o -name '*.o' -delete

