// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include <iostream>
#include <ostream>

#include "ECSCore/Entity.hpp"
#include "ECSCore/Object.hpp"
#include "ECSCore/ObjectManager.hpp"

int main()
{
    auto entity = std::make_shared<ECSCore::Entity>();
    auto manager = entity->CreateManager<ECSCore::ObjectManager>();
    if (auto sharedManager = manager.lock())
    {
        sharedManager->CreateObject<ECSCore::Object>(entity);
        sharedManager->CreateObject<ECSCore::Object>(entity);
        sharedManager->CreateObject<ECSCore::Object>(entity);
        std::cout << sharedManager->GetObjectCount() << std::endl;
    }
    std::cout << entity->GetManagersNum() << std::endl;
    return 0;
}
