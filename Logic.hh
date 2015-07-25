#ifndef LOGIC_HH
#define LOGIC_HH

namespace GameEngine {
   class Logic
   {
  public:
     void runGameLoop();
  private:
     void updateLogic();
     void processInput();
   };
}

#endif // LOGIC_HH
