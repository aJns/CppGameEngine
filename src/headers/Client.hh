/* A lot is lifted from the ogre3d "BaseApplication" */

#ifndef CLIENT_HH
#define CLIENT_HH

// std
#include <memory>

// GameEngine
#include "Logic.hh"

namespace GameEngine {
    class Client : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener
    {
    public:
        Client();
        virtual ~Client();

        void init();

    private:
        bool setup();
        bool configure(void);
        void chooseSceneManager(void);
        void createCamera(void);
        void createFrameListener(void);
        virtual void createScene(void);
        void destroyScene(void);
        void createViewports(void);
        void setupResources(void);
        void createResourceListener(void);
        void loadResources(void);

        // Ogre::FrameListener
        virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

        // OIS::KeyListener
        virtual bool keyPressed( const OIS::KeyEvent &arg );
        virtual bool keyReleased( const OIS::KeyEvent &arg );
        // OIS::MouseListener
        virtual bool mouseMoved( const OIS::MouseEvent &arg );
        virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
        virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

        // Ogre::WindowEventListener
        //Adjust mouse clipping area
        virtual void windowResized(Ogre::RenderWindow* rw);
        //Unattach OIS before window shutdown (very important under Linux)
        virtual void windowClosed(Ogre::RenderWindow* rw);

    protected:

        Ogre::Root *root_;
        Ogre::Camera* camera_;
        Ogre::SceneManager* sceneMgr_;
        Ogre::RenderWindow* window_;
        Ogre::String resourcesCfg_;
        Ogre::String pluginsCfg_;
        Ogre::OverlaySystem *overlaySystem_;

        // OgreBites
        OgreBites::SdkTrayManager* trayMgr_;
        OgreBites::SdkCameraMan* cameraMan_;       // basic camera controller
        OgreBites::ParamsPanel* detailsPanel_;     // sample details panel
        bool cursorWasVisible_;                    // was cursor visible before dialog appeared
        bool shutDown_;

        //OIS Input devices
        OIS::InputManager* inputManager_;
        OIS::Mouse*    mouse_;
        OIS::Keyboard* keyboard_;

        GameEngine::Logic* gameLogic_;
    };
}

#endif // CLIENT_HH
