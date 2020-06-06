#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <FD3D/SceneGraph/Scene.h>
#include <FDCore/ResourceManager.h>

#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <FD3D/Mesh/Mesh.h>

namespace FD3D
{
    class SceneManager
    {
        public:
            typedef std::function<void(FD3D::SceneManager*, FD3D::Element*, void*)> EventHandler; //< function called to handle an event on an element
            typedef FDCore::AssociativeContainer<std::string, EventHandler> EventHandlerMap; //< map that matches a type code to an ElementEventHandler
            typedef FDCore::AssociativeContainer<std::string, EventHandlerMap> EventMap; //< map that matches an event name to an ElementEventHandlerMap
            typedef FDCore::AssociativeContainer<FD3D::Element::id_type, int> IdIndexMap; //< map that match an Id to an index for serialization purpose
            typedef EventMap::iterator event_iterator;
            typedef EventMap::const_iterator const_event_iterator;

            enum IdIndex : int
            {
                NoIndex = -1,
                IndexError = -2
            };

        protected:
            FD3D::Scene *m_scene;
            FDCore::ResourceManager *m_resourceMgr;
            EventMap m_eventMap;
            IdIndexMap m_idIndexMap;

        public:
            SceneManager() : SceneManager(nullptr, nullptr) {}
            SceneManager(Scene *m_scene, FDCore::ResourceManager *m_resourceMgr);
            virtual ~SceneManager() = default;

            bool hasScene() const { return m_scene != nullptr; }
            FD3D::Scene *getScene() { return m_scene; }
            const FD3D::Scene *getScene() const { return m_scene; }
            void setScene(FD3D::Scene *scene) { m_scene = scene; }

            bool hasResourceManager() const { return m_resourceMgr != nullptr; }
            FDCore::ResourceManager *getResourceManager() { return m_resourceMgr; }
            const FDCore::ResourceManager *getResourceManager() const { return m_resourceMgr; }
            void setResourceManager(FDCore::ResourceManager *mgr) { m_resourceMgr = mgr; }

            EventMap &getEventMap() { return m_eventMap; }
            const EventMap &getEventMap() const { return m_eventMap; }

            IdIndexMap &getIdIndexMap() { return m_idIndexMap; }
            const IdIndexMap &getIdIndexMap() const { return m_idIndexMap; }

            void registerEvent(std::string_view event_name) { registerEvent(event_name, {}); }
            void registerEvent(std::string_view event_name, EventHandlerMap &&handlers)
            {
                m_eventMap.insert(event_name.data(), std::move(handlers));
            }

            void unregisterEvent(std::string_view event_name) { m_eventMap.erase(event_name.data()); }

            event_iterator findHandlerMap(std::string_view event_name) { return m_eventMap.find(event_name.data()); }
            const_event_iterator findHandlerMap(std::string_view event_name) const { return m_eventMap.find(event_name.data()); }

            EventHandler findHandler(std::string_view event_name, std::string_view type_code) const;

            bool hasHandlerMap(std::string_view event_name) const { return findHandlerMap(event_name) != m_eventMap.end(); }
            bool hasHandler(std::string_view event_name, std::string_view type_code) const { return findHandler(event_name, type_code).operator bool(); }

            EventHandlerMap &operator[](std::string_view event_name) { return *m_eventMap[event_name.data()]; }
            const EventHandlerMap &operator[](std::string_view event_name) const { return *m_eventMap[event_name.data()]; }

            void prepareIdIndexMap();
            void clearIdIndexMap();
            int getIdIndex(FD3D::Element::id_type id) const;
            void setIdIndex(FD3D::Element::id_type id, int index);
            FD3D::Element::id_type getIndexId(int index);

        public:
            template<typename T>
            static std::unique_ptr<FD3D::AbstractMesh> defaultMeshInstanciator()
            {
                return std::unique_ptr<FD3D::AbstractMesh>(new T());
            }
    };
}

#endif // SCENEMANAGER_H
