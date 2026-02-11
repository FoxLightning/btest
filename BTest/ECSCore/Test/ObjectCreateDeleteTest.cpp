// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include <array>
#include <iostream>
#include <memory>
#include <ostream>

#include "ECSCore/Entity.hpp"
#include "ECSCore/Object.hpp"
#include "ECSCore/ObjectManager.hpp"

int main()
{
    const auto entity     = std::make_shared<ECSCore::Entity>();
    const auto managerPtr = entity->CreateManager<ECSCore::TObjectManager<ECSCore::Object>>();

    constexpr int32_t targetObjectCount{1000};
    std::println(std::cout, "Creating {} objects.", targetObjectCount);
    {
        std::array<std::shared_ptr<ECSCore::Object>, targetObjectCount> objectsPool;
        for (int32_t i = 0; i < targetObjectCount; ++i)
        {
            objectsPool[i] = ECSCore::Object::CreateObject<ECSCore::Object>(entity);
        }

        if (managerPtr.lock()->GetObjectCount() != targetObjectCount)
        {
            std::println(std::cerr, "Manager should have {} registered objects, but have {}.", targetObjectCount,
                         managerPtr.lock()->GetObjectCount());
            return 1;
        }
    }
    std::println(std::cout, "Deleting all objects.", targetObjectCount);
    if (managerPtr.lock()->GetObjectCount() != 0)
    {
        std::println(std::cerr, "Manager should have no registered objects, but have {}.", targetObjectCount,
                     managerPtr.lock()->GetObjectCount());
        return 1;
    }
    return 0;
}
