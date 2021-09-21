#include "findBehaviour/findAttributes.h"

namespace myFind {

    class findServer
    {
    private:
        findAttributes _attributes;
    public:
        findServer();
        findServer(findAttributes attributes);
        ~findServer();
    };
}
