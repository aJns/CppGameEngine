#ifndef CLIENT_HH
#define CLIENT_HH

namespace GameEngine {
  class Client
  {
  public:
    Client();
    virtual ~Client();
    void init();
  private:
    void render();
  };
}

#endif // CLIENT_HH
