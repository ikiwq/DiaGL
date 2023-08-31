#pragma once

#include <map>
#include <memory>
#include <iostream>

#include "Component.h"
#include "../ecs/components/SpriteRenderer.h"
#include "Transform.h"

constexpr unsigned int MAX_COMPONENTS = 32;

class Ramiel
{
public:
    Transform* transform;
private:
    std::string name;
    std::map<unsigned int, Component*> componentMap;

public:
    Ramiel(std::string name);

    Ramiel(std::string name, Transform* transform);

    ~Ramiel();

    template <typename T, typename... TArgs>
    void addComponent(TArgs &&...args) {
        T* cmpt(new T(std::forward<TArgs>(args)...));
        cmpt->setOwner(this);
        if (cmpt->init())
        {
            componentMap.emplace(getComponentID<T>(), cmpt);
        }
        else
        {
            delete cmpt;
        }
    }

    template <typename T>
    bool hasComponent() const
    {
        return false;
    }

    template <typename T>
    T* getComponent() const
    {
        return dynamic_cast<T*>(componentMap.at(getComponentID<T>()));
    }

    void init()
    {
    }

    void update(float dt)
    {
        for (auto &p : componentMap)
        {
            //p->second->update(dt);
        }
    }
};