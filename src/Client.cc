#include "Client.hh"

#include "GameObject.hh"
#include "GraphicsComponent.hh"

GameEngine::Client::Client()
    : root_(0),
    camera_(0),
    sceneMgr_(0),
    window_(0),
    resourcesCfg_(Ogre::StringUtil::BLANK),
    pluginsCfg_(Ogre::StringUtil::BLANK),
    trayMgr_(0),
    cameraMan_(0),
    detailsPanel_(0),
    cursorWasVisible_(false),
    shutDown_(false),
    inputManager_(0),
    mouse_(0),
    keyboard_(0)
{
}

GameEngine::Client::~Client() {
    if (trayMgr_) delete trayMgr_;
    if (cameraMan_) delete cameraMan_;

    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(window_, this);
    windowClosed(window_);
    delete root_;
}

void GameEngine::Client::init() {
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
    resourcesCfg_ = "resources.cfg";
    pluginsCfg_ = "plugins.cfg";
#endif

    if (!setup())
        return;

    root_->startRendering();

    // clean up
    destroyScene();
}

bool GameEngine::Client::setup() {
    root_ = new Ogre::Root(pluginsCfg_);

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    loadResources();

    // Create the scene
    createScene();

    createFrameListener();

    return true;
}

bool GameEngine::Client::configure() {
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(root_->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        window_ = root_->initialise(true, "TutorialApplication Render Window");

        return true;
    }
    else
    {
        return false;
    }
}

void GameEngine::Client::chooseSceneManager() {
    // Get the SceneManager, in this case a generic one
    sceneMgr_ = root_->createSceneManager(Ogre::ST_GENERIC);
	overlaySystem_ = new Ogre::OverlaySystem();
	sceneMgr_->addRenderQueueListener(overlaySystem_);
}

void GameEngine::Client::createCamera() {
    // Create the camera
    camera_ = sceneMgr_->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    camera_->setPosition(Ogre::Vector3(0,0,80));
    // Look back along -Z
    camera_->lookAt(Ogre::Vector3(0,0,-300));
    camera_->setNearClipDistance(5);

    cameraMan_ = new OgreBites::SdkCameraMan(camera_);   // create a default camera controller
}

void GameEngine::Client::createFrameListener() {
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    window_->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    inputManager_ = OIS::InputManager::createInputSystem( pl );

    keyboard_ = static_cast<OIS::Keyboard*>(inputManager_->createInputObject( OIS::OISKeyboard, true ));
    mouse_ = static_cast<OIS::Mouse*>(inputManager_->createInputObject( OIS::OISMouse, true ));

    mouse_->setEventCallback(this);
    keyboard_->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(window_);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(window_, this);

	OgreBites::InputContext inputContext;
	inputContext.mMouse = mouse_; 
	inputContext.mKeyboard = keyboard_;
    trayMgr_ = new OgreBites::SdkTrayManager("InterfaceName", window_, inputContext, this);
    trayMgr_->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    trayMgr_->showLogo(OgreBites::TL_BOTTOMRIGHT);
    trayMgr_->hideCursor();

    // create a params panel for displaying sample details
    Ogre::StringVector items;
    items.push_back("cam.pX");
    items.push_back("cam.pY");
    items.push_back("cam.pZ");
    items.push_back("");
    items.push_back("cam.oW");
    items.push_back("cam.oX");
    items.push_back("cam.oY");
    items.push_back("cam.oZ");
    items.push_back("");
    items.push_back("Filtering");
    items.push_back("Poly Mode");

    detailsPanel_ = trayMgr_->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
    detailsPanel_->setParamValue(9, "Bilinear");
    detailsPanel_->setParamValue(10, "Solid");
    detailsPanel_->hide();

    root_->addFrameListener(this);
}

void GameEngine::Client::createScene() {
    sceneMgr_->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    /* Ogre::Entity* ogreEntity =sceneMgr_->createEntity("ogrehead.mesh"); */
    /* Ogre::SceneNode* ogreNode = sceneMgr_->getRootSceneNode()->createChildSceneNode("TestNode"); */
    /* ogreNode->attachObject(ogreEntity); */

    GameEngine::GameObject object;
    object.addGraphicsComponent(*sceneMgr_);

    Ogre::Light* light = sceneMgr_->createLight("MainLight");
    light->setPosition(20, 80, 50);
}

void GameEngine::Client::destroyScene() {
}

void GameEngine::Client::createViewports() {
    // Create one viewport, entire window
    Ogre::Viewport* vp = window_->addViewport(camera_);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    camera_->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void GameEngine::Client::setupResources() {
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(resourcesCfg_);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}

void GameEngine::Client::createResourceListener() {
}

void GameEngine::Client::loadResources() {
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

bool GameEngine::Client::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(window_->isClosed())
        return false;

    if(shutDown_)
        return false;

    //Need to capture/update each device
    keyboard_->capture();
    mouse_->capture();

    trayMgr_->frameRenderingQueued(evt);

    if (!trayMgr_->isDialogVisible())
    {
        cameraMan_->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
        if (detailsPanel_->isVisible())   // if details panel is visible, then update its contents
        {
            detailsPanel_->setParamValue(0, Ogre::StringConverter::toString(
                        camera_->getDerivedPosition().x));
            detailsPanel_->setParamValue(1, Ogre::StringConverter::toString(
                        camera_->getDerivedPosition().y));
            detailsPanel_->setParamValue(2, Ogre::StringConverter::toString(
                        camera_->getDerivedPosition().z));
            detailsPanel_->setParamValue(4, Ogre::StringConverter::toString(
                        camera_->getDerivedOrientation().w));
            detailsPanel_->setParamValue(5, Ogre::StringConverter::toString(
                        camera_->getDerivedOrientation().x));
            detailsPanel_->setParamValue(6, Ogre::StringConverter::toString(
                        camera_->getDerivedOrientation().y));
            detailsPanel_->setParamValue(7, Ogre::StringConverter::toString(
                        camera_->getDerivedOrientation().z));
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------
bool GameEngine::Client::keyPressed( const OIS::KeyEvent &arg )
{
    if (trayMgr_->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
    {
        trayMgr_->toggleAdvancedFrameStats();
    }
    else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
    {
        if (detailsPanel_->getTrayLocation() == OgreBites::TL_NONE)
        {
            trayMgr_->moveWidgetToTray(detailsPanel_, OgreBites::TL_TOPRIGHT, 0);
            detailsPanel_->show();
        }
        else
        {
            trayMgr_->removeWidgetFromTray(detailsPanel_);
            detailsPanel_->hide();
        }
    }
    else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::TextureFilterOptions tfo;
        unsigned int aniso;

        switch (detailsPanel_->getParamValue(9).asUTF8()[0])
        {
        case 'B':
            newVal = "Trilinear";
            tfo = Ogre::TFO_TRILINEAR;
            aniso = 1;
            break;
        case 'T':
            newVal = "Anisotropic";
            tfo = Ogre::TFO_ANISOTROPIC;
            aniso = 8;
            break;
        case 'A':
            newVal = "None";
            tfo = Ogre::TFO_NONE;
            aniso = 1;
            break;
        default:
            newVal = "Bilinear";
            tfo = Ogre::TFO_BILINEAR;
            aniso = 1;
        }

        Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
        Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
        detailsPanel_->setParamValue(9, newVal);
    }
    else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::PolygonMode pm;

        switch (camera_->getPolygonMode())
        {
        case Ogre::PM_SOLID:
            newVal = "Wireframe";
            pm = Ogre::PM_WIREFRAME;
            break;
        case Ogre::PM_WIREFRAME:
            newVal = "Points";
            pm = Ogre::PM_POINTS;
            break;
        default:
            newVal = "Solid";
            pm = Ogre::PM_SOLID;
        }

        camera_->setPolygonMode(pm);
        detailsPanel_->setParamValue(10, newVal);
    }
    else if(arg.key == OIS::KC_F5)   // refresh all textures
    {
        Ogre::TextureManager::getSingleton().reloadAll();
    }
    else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        window_->writeContentsToTimestampedFile("screenshot", ".jpg");
    }
    else if (arg.key == OIS::KC_ESCAPE)
    {
        shutDown_ = true;
    }

    cameraMan_->injectKeyDown(arg);
    return true;
}

bool GameEngine::Client::keyReleased( const OIS::KeyEvent &arg )
{
    cameraMan_->injectKeyUp(arg);
    return true;
}

bool GameEngine::Client::mouseMoved( const OIS::MouseEvent &arg )
{
    if (trayMgr_->injectMouseMove(arg)) return true;
    cameraMan_->injectMouseMove(arg);
    return true;
}

bool GameEngine::Client::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (trayMgr_->injectMouseDown(arg, id)) return true;
    cameraMan_->injectMouseDown(arg, id);
    return true;
}

bool GameEngine::Client::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (trayMgr_->injectMouseUp(arg, id)) return true;
    cameraMan_->injectMouseUp(arg, id);
    return true;
}

//Adjust mouse clipping area
void GameEngine::Client::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mouse_->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void GameEngine::Client::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == window_ )
    {
        if( inputManager_ )
        {
            inputManager_->destroyInputObject( mouse_ );
            inputManager_->destroyInputObject( keyboard_ );

            OIS::InputManager::destroyInputSystem(inputManager_);
            inputManager_ = 0;
        }
    }
}









