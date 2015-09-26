#ifndef APPLICATION_HH
#define APPLICATION_HH

// std
#include <memory>

// GameEngine
#include "Logic.hh"

namespace GameEngine {
    class Application {
    public:
        Application();
        virtual ~Application();

        void init();

    private:
        GameEngine::Logic* gameLogic_;
    };
}

#endif // APPLICATION_HH
