// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include <array>
#include <chrono>
#include <iostream>
#include <memory>
#include <ostream>

#include "ECSCore/Entity.hpp"
#include "ECSCore/Object.hpp"
#include "ECSCore/ObjectManager.hpp"

class TestObjectOne : public ECSCore::Object
{
  public:
    TestObjectOne(const std::weak_ptr<ECSCore::Entity>& inOwner) : Object(inOwner)
    {
    }
};

class TestObjectTwo : public ECSCore::Object
{
  public:
    TestObjectTwo(const std::weak_ptr<ECSCore::Entity>& inOwner) : Object(inOwner)
    {
    }
};

class TestObjectThree : public ECSCore::Object
{
  public:
    TestObjectThree(const std::weak_ptr<ECSCore::Entity>& inOwner) : Object(inOwner)
    {
    }
};

class ObjectHolderManager : public ECSCore::TObjectManager<ECSCore::Object>
{
  public:
    bool PostAttachObjectToComponent(std::weak_ptr<ECSCore::Object> object) override
    {
        objects.push_back(object.lock());
        return true;
    }

  private:
    std::vector<std::shared_ptr<ECSCore::Object>> objects;
};

int main()
{
    const auto entity      = std::make_shared<ECSCore::Entity>();
    const auto entityConst = std::static_pointer_cast<const ECSCore::Entity>(entity);
    const auto constEntity = std::static_pointer_cast<const ECSCore::Entity>(entity);

    constexpr int32_t expectedEntitiesNumOne   = 1;
    constexpr int32_t expectedEntitiesNumTwo   = 2;
    constexpr int32_t expectedEntitiesNumThree = 3;
    std::println(std::cout, "Creating managers.");
    {
        const auto managerOne         = entity->CreateManager<ECSCore::TObjectManager<TestObjectOne>>();
        const auto managerTwo         = entity->CreateManager<ECSCore::TObjectManager<TestObjectTwo>>();
        const auto managerThree       = entity->CreateManager<ECSCore::TObjectManager<TestObjectThree>>();
        const auto managerHolderOne   = entity->CreateManager<ObjectHolderManager>();
    }
    if (entity->GetManagersNum() != 4)
    {
        std::println(std::cerr, "Managers num is {}, should be {}.", entity->GetManagersNum(), 4);
        return 1;
    }

    std::println(std::cout, "Creating entities.");
    for (int i = 0; i < expectedEntitiesNumOne; i++)
    {
        ECSCore::Object::CreateObject<TestObjectOne>(entity);
    }
    for (int i = 0; i < expectedEntitiesNumTwo; i++)
    {
        ECSCore::Object::CreateObject<TestObjectTwo>(entity);
    }
    for (int i = 0; i < expectedEntitiesNumThree; i++)
    {
        ECSCore::Object::CreateObject<TestObjectThree>(entity);
    }

    if (const auto objectCount =
            entityConst->GetManager<ECSCore::TObjectManager<TestObjectOne>>().lock()->GetObjectCount();
        objectCount != expectedEntitiesNumOne)
    {
        std::println(std::cerr, R"(Object number registered in manager one is {}, should be {})", objectCount,
                     expectedEntitiesNumOne);
        return 1;
    }
    if (const auto objectCount =
            entityConst->GetManager<ECSCore::TObjectManager<TestObjectTwo>>().lock()->GetObjectCount();
        objectCount != expectedEntitiesNumTwo)
    {
        std::println(std::cerr, R"(Object number registered in manager two is {}, should be {})", objectCount,
                     expectedEntitiesNumTwo);
        return 1;
    }
    if (const auto objectCount =
            entityConst->GetManager<ECSCore::TObjectManager<TestObjectThree>>().lock()->GetObjectCount();
        objectCount != expectedEntitiesNumThree)
    {
        std::println(std::cerr, R"(Object number registered in manager three is {}, should be {})", objectCount,
                     expectedEntitiesNumThree);
        return 1;
    }

    println(std::cout, "Getting mutable manager.");
    const auto managerMutable = entity->GetManager<ECSCore::TObjectManager<TestObjectTwo>>();

    return 0;
}
