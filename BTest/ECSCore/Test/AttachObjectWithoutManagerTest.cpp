// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include <chrono>
#include <memory>

#include "ECSCore/Entity.hpp"
#include "ECSCore/Object.hpp"

class TestObjectWithoutManager : public ECSCore::Object
{
  public:
    TestObjectWithoutManager(const std::weak_ptr<ECSCore::Entity>& inOwner) : Object(inOwner)
    {
    }
};

int main()
{
    const auto entity = std::make_shared<ECSCore::Entity>();
    auto       obj1   = ECSCore::Object::CreateObject<TestObjectWithoutManager>(entity);
    if (!obj.expired())
    {
        std::cerr << "Object should be null." << std::endl;
        return 1;
    }
    return 0;
}
