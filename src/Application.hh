#ifndef APPLICATION_HH
#define APPLICATION_HH

// std
#include <memory>

// Magnum
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Drawable.h>

// GameEngine
#include "Logic.hh"


namespace GameEngine {
    class Application : public Magnum::Platform::Application {
    public:
        explicit Application(const Arguments& arguments);
        virtual ~Application();

        void initLogic();

    private:
        GameEngine::Logic* gameLogic_;

        Magnum::SceneGraph::Scene<Magnum::SceneGraph::MatrixTransformation3D> scene_;
        Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>* cameraObject_;
        Magnum::SceneGraph::Camera3D* camera_;
        Magnum::SceneGraph::DrawableGroup3D drawables_;

        void drawEvent() override;
    };
}

MAGNUM_APPLICATION_MAIN(GameEngine::Application)


#endif // APPLICATION_HH
