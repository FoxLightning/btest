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
    auto managerPtr = entity->CreateManager<ECSCore::TObjectManager<ECSCore::Object>>();
    {

        auto obj1 = ECSCore::Object::CreateObject<ECSCore::Object>(entity);
        auto obj2 = ECSCore::Object::CreateObject<ECSCore::Object>(entity);
        auto obj3 = ECSCore::Object::CreateObject<ECSCore::Object>(entity);
        auto obj4 = ECSCore::Object::CreateObject<ECSCore::Object>(entity);
        if (managerPtr.lock()->GetObjectCount() != 4)
        {
            return 1;
        }
    }
    if (managerPtr.lock()->GetObjectCount() != 0)
    {
        return 1;
    }

    return 0;
}
