#include "findBehaviour/findAttributes.h"

namespace myFind {

    class findServer
    {
    private:
        findAttributes _attributes;
    public:
        int activeClients;
        
        findServer();
        findServer(myFind::findAttributes attributes);
        ~findServer();
    };
}
