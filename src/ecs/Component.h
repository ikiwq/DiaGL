#pragma once

inline unsigned int getComponentTypeID()
{
    static unsigned int lastID = 0;
    return lastID++;
}

template <typename T>
inline unsigned int getComponentID() noexcept
{
    static unsigned int typeID = getComponentTypeID();
    return typeID;
}

class Ramiel;

class Component
{
    Ramiel *owner = nullptr;

public:
    virtual void update(float dt) = 0;
    virtual bool init() = 0;

    void setOwner(Ramiel *owner)
    {
        this->owner = owner;
    }

    Ramiel* getOwner(){
        return owner;
    }
};