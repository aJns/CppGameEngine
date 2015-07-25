#ifndef SERVER_HH
#define SERVER_HH

#include <vector>

#include "Client.hh"

namespace GameEngine {
    class Server
    {
   public:
       void addClient(Client client);
   private:
       std::vector<Client> clients_;
    };
}

#endif // SERVER_HH
