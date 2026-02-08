// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include <exception>
#include <memory>
#include <print>

#include "ECSCore/Entity.hpp"
#include "ECSCore/EntityManager.hpp"
#include "ECSCore/Object.hpp"
#include "ECSCore/ObjectManager.hpp"

int main()
{
    try
    {
        ECSCore::EntityManager entityManager{};

        const auto* firstEntityName  = "firstEntity";
        const auto* secondEntityName = "secondEntity";

        std::println(R"(Creating entity "{}")", firstEntityName);

        const std::weak_ptr firstEntityPtr = entityManager.CreateEntity(firstEntityName);
        if (firstEntityPtr.expired())
        {
            std::println("Entity with name \"{}\" not found.", firstEntityName);
            return 1;
        }
        std::println(R"(Entity "{}" successfully created )", firstEntityPtr.lock()->GetName());
        std::println(R"(Creating entity "{}")", secondEntityName);

        const std::weak_ptr secondEntityPtr = entityManager.CreateEntity(secondEntityName);
        if (secondEntityPtr.expired())
        {
            std::println("Entity with name \"{}\" not found.", secondEntityName);
            return 1;
        }
        std::println(R"(Entity "{}" successfully created )", secondEntityPtr.lock()->GetName());
        std::println(R"(Creating entity "{}")", secondEntityName);

        if (entityManager.GetEntityCount() != 2)
        {
            std::println("Entity count is {}. Should be 2.", entityManager.GetEntityCount());
            return 1;
        }
        std::println("Entity count is {}.", entityManager.GetEntityCount());

        if (const std::weak_ptr foundPtr = entityManager.GetEntity(firstEntityName);
            foundPtr.lock() != firstEntityPtr.lock())
        {
            std::println(R"(Entity with name "{}" is not "{}".)", foundPtr.lock()->GetName(),
                         firstEntityPtr.lock()->GetName());
            return 1;
        }
        if (const std::weak_ptr foundPtr = entityManager.GetEntity(secondEntityName);
            foundPtr.lock() != secondEntityPtr.lock())
        {
            std::println(R"(Entity with name "{}" is not "{}".)", foundPtr.lock()->GetName(),
                         secondEntityPtr.lock()->GetName());
            return 1;
        }
        std::println("Get entity forks good.");

        std::println("Creating object manager for entity \"{}\".", firstEntityPtr.lock()->GetName());
        auto Manager = firstEntityPtr.lock()->CreateManager<ECSCore::ObjectManager>();
        if (Manager.expired())
        {
            std::println(R"(Object manager for entity "{}" not created.)", firstEntityPtr.lock()->GetName());
            return 1;
        }
        std::println("Deleting manager.");
        if (!firstEntityPtr.lock()->DeleteManager<ECSCore::ObjectManager>())
        {
            std::println(R"(Object manager for entity  not deleted.)");
            return 1;
        }
        std::println("Deleting non existing manager.");
        if (firstEntityPtr.lock()->DeleteManager<ECSCore::ObjectManager>())
        {
            std::println(R"(Object manager for entity is deleted, but it is already deleted.)");
            return 1;
        }
        std::println("Check week ptr.");
        if (!Manager.expired())
        {
            std::println(R"(Object manager for entity not deleted, week ptr is not expired.)");
            return 1;
        }

        std::println("Creating object manager for entity \"{}\" again.", firstEntityPtr.lock()->GetName());
        Manager = firstEntityPtr.lock()->CreateManager<ECSCore::ObjectManager>();
        if (Manager.expired())
        {
            std::println(R"(Object manager for entity "{}" not created.)", firstEntityPtr.lock()->GetName());
            return 1;
        }

        const auto*         testObjectName = "Test";
        const std::weak_ptr object         = Manager.lock()->CreateObject<ECSCore::Object>(testObjectName);
        if (object.expired())
        {
            std::println(R"(Object for entity "{}" not created.)", firstEntityPtr.lock()->GetName());
            return 1;
        }
        std::println(R"(Object created. "{}")", object.lock()->GetName());

        std::println("Check get object");
        if (Manager.lock()->GetObject(testObjectName).lock() != object.lock())
        {
            std::println(R"(Object for entity "{}" not found.)", firstEntityPtr.lock()->GetName());
            return 1;
        }
        std::println("Get object works good.");

        std::println("Deleting object");
        Manager.lock()->DeleteObject(testObjectName);
        if (!Manager.lock()->GetObject(testObjectName).expired())
        {
            std::println(R"(Object for entity "{}" not deleted.)", firstEntityPtr.lock()->GetName());
            return 1;
        }
        std::println("Get object works good for deleted object.");

        return 0;
    }
    catch (const std::exception& exceptionObject)
    {
        std::println("Exception: {}", exceptionObject.what());
        return 1;
    }
}
