#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "Components/RenderComponent.h"

namespace nc
{
	void Scene::Create(void* data)
	{
		m_engine = static_cast<Engine*>(data);
	}

	void Scene::Destroy()
	{
		RemoveAllGameObjects();
	}

	void Scene::Read(const rapidjson::Value& value)
	{
		if (value.HasMember("Prototypes"))
		{
			const rapidjson::Value& objectsValue = value["Prototypes"];
			if (objectsValue.IsArray())
			{
				ReadPrototypes(objectsValue);
			}
		}

		if (value.HasMember("GameObjects"))
		{
			const rapidjson::Value& objectsValue = value["GameObjects"];
			if (objectsValue.IsArray())
			{
				ReadGameObjects(objectsValue);
			}
		}
	}

	void Scene::ReadGameObjects(const rapidjson::Value& value)
	{
		for (rapidjson::SizeType i = 0; i < value.Size(); i++)
		{
			const rapidjson::Value& objectValue = value[i];
			if (objectValue.IsObject())
			{
				std::string typeName;
				json::Get(objectValue, "type", typeName);
				nc::GameObject* gameObject = ObjectFactory::Instance().Create<GameObject>(typeName);

				if (gameObject)
				{
					gameObject->Create(this);
					gameObject->Read(objectValue);

					AddGameObject(gameObject);
				}
			}
		}
	}

	void Scene::ReadPrototypes(const rapidjson::Value& value)
	{
		for (rapidjson::SizeType i = 0; i < value.Size(); i++)
		{
			const rapidjson::Value& objectValue = value[i];
			if (objectValue.IsObject())
			{
				std::string typeName;
				json::Get(objectValue, "type", typeName);
				nc::GameObject* gameObject = ObjectFactory::Instance().Create<GameObject>(typeName);

				if (gameObject)
				{
					gameObject->Create(this);
					gameObject->Read(objectValue);

					//std::cout << gameObject->m_name << std::endl;

					ObjectFactory::Instance().Register(gameObject->m_name, new Prototype<Object>(gameObject));
				}
			}
		}
	}

	void Scene::Update()
	{
		// update game objects
		for (auto gameObject : m_gameObjects)
		{
			gameObject->Update();
		}

		// remove/destroy game objects
		auto iter = m_gameObjects.begin();
		while (iter != m_gameObjects.end())
		{
			if ((*iter)->m_flags[GameObject::eFlags::DESTROY])
			{
				(*iter)->Destroy();
				delete (*iter);
				iter = m_gameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void Scene::Draw()
	{
		// collect render components from game objects
		std::vector<RenderComponent*> components;
		for (auto gameObject : m_gameObjects)
		{
			RenderComponent* component = gameObject->GetComponent<RenderComponent>();
			if (component)
			{
				components.push_back(component);
			}
		}

		// sort render components
		std::sort(components.begin(), components.end(), RenderComponent::SortZ);

		// draw render components
		for (RenderComponent* component : components)
		{
			component->Draw();
		}
	}

	GameObject* Scene::Find(const std::string& name)
	{
		for (auto gameObject : m_gameObjects)
		{
			if (gameObject->m_name == name)
			{
				return gameObject;
			}
		}

		return nullptr;
	}

	std::vector<GameObject*> Scene::FindGameObjectsWithTag(const std::string& tag)
	{
		std::vector<GameObject*> gameObjects;

		for (auto gameObject : m_gameObjects)
		{
			if (gameObject->m_tag == tag)
			{
				gameObjects.push_back(gameObject);
			}
		}

		return gameObjects;
	}

	void Scene::AddGameObject(GameObject* gameObject)
	{
		m_gameObjects.push_back(gameObject);
	}

	void Scene::RemoveGameObject(GameObject* gameObject)
	{
		auto iter = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
		if (iter != m_gameObjects.end())
		{
			(*iter)->Destroy();
			delete (*iter);
			m_gameObjects.erase(iter);
		}
	}

	void Scene::RemoveAllGameObjects()
	{
		for (GameObject* gameObject : m_gameObjects)
		{
			gameObject->Destroy();
			delete gameObject;
		}

		m_gameObjects.clear();
	}
}
