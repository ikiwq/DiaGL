#pragma once

#include "Ramiel.h"

Ramiel::Ramiel(std::string name)
{
    this->name = name;
    this->transform = new Transform();
}

Ramiel::Ramiel(std::string name, Transform * transform) {
    this->name = name;
    this->transform = transform;
}

Ramiel::~Ramiel() {
    delete transform;
    for (auto& c : componentMap) {
        delete c.second;
    }
}