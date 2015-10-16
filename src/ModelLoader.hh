// std
#include <memory>
#include <string>

// Magnum
#include <Corrade/PluginManager/Manager.h>
#include <Corrade/Utility/Arguments.h>
#include <Magnum/Buffer.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/TextureFormat.h>
#include <Magnum/Mesh.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/Renderer.h>
#include <Magnum/ResourceManager.h>
#include <Magnum/Texture.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/Trade/ImageData.h>
#include <Magnum/Trade/MeshData3D.h>
#include <Magnum/Trade/MeshObjectData3D.h>
#include <Magnum/Trade/PhongMaterialData.h>
#include <Magnum/Trade/SceneData.h>
#include <Magnum/Trade/TextureData.h>

#include "configure.h"


namespace GameEngine {
    typedef Magnum::ResourceManager<Magnum::Buffer, Magnum::Mesh,
            Magnum::Texture2D, Magnum::Shaders::Phong,
            Magnum::Trade::PhongMaterialData> ViewerResourceManager;
    typedef
        Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>
        Object3D;
    typedef
        Magnum::SceneGraph::Scene<Magnum::SceneGraph::MatrixTransformation3D>
        Scene3D;


    class ModelLoader {
    public:
        explicit ModelLoader(ViewerResourceManager& resourceManager_,
                Magnum::SceneGraph::DrawableGroup3D& drawables,
                Scene3D& scene);

        Object3D* loadModel(std::string sceneFile);
    private:
        void addObject(Magnum::Trade::AbstractImporter& importer, Object3D*
                parent, Magnum::UnsignedInt i);

        ViewerResourceManager* resourceManager_;
        Magnum::SceneGraph::DrawableGroup3D* drawables_;
        Scene3D* _scene;
    };
}
