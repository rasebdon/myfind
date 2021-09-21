#include "findBehaviour/findAttributes.h"
#include <string>

namespace myFind
{
    class findClient
    {
    private:
        std::string myDir;
    public:
        findClient(std::string dirToSerach, myFind::findAttributes attributes);
        ~findClient();
    };
}