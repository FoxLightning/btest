// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include <iostream>
#include <memory>
#include <ostream>

#include "ECSCore/Entity.hpp"
#include "ECSCore/Object.hpp"
#include "ECSCore/ObjectManager.hpp"

int main()
{
    auto entity = std::make_shared<ECSCore::Entity>();
    auto manager = entity->CreateManager<ECSCore::TObjectManager<ECSCore::Object>>();
    if (auto sharedManager = manager.lock())
    {
        sharedManager->CreateObject(entity);
        std::cout << sharedManager->GetObjectCount() << std::endl;
    }
    std::cout << entity->GetManagersNum() << std::endl;
    return 0;
}
