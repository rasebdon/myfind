#include "findBehaviour/findAttributes.h"

namespace myFind {

    class findServer
    {
    private:
        findAttributes _attributes;
    public:
        int activeClients;
        void removeQueue();
        
        findServer();
        findServer(myFind::findAttributes attributes);
        ~findServer();
    };
}
