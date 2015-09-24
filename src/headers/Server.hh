#ifndef SERVER_HH
#define SERVER_HH

// std
#include <vector>

// GameEngine
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
