// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include <iostream>
#include <print>

#include "ECSApp/ECSAppAPI.hpp"

int main()
{
    const auto entityOneName = ECSApp::EntityName{ "TestEntityOne" };
    const auto entityTwoName = ECSApp::EntityName{ "TestEntityTwo" };

    const auto appInstance = ECSApp::GetAppInstance();
    if (appInstance->GetEntityCount() != 0)
    {
        std::println(std::cout, "Initial entity count: {}, expected 0.", appInstance->GetEntityCount());
    }
    std::println(std::cout, "creating entities...");
    appInstance->AddEntity(entityOneName);
    appInstance->AddEntity(entityTwoName);
    if (appInstance->GetEntityCount() != 2)
    {
        std::println(std::cerr, "Entity count mismatch after adding entities: expected 2, got {}", appInstance->GetEntityCount());
    }
    std::println(std::cout, "Successfully created entities.");
    appInstance->RemoveEntity(entityOneName);
    if (appInstance->GetEntityCount() != 1)
    {
        std::println(std::cerr, "Entity count mismatch after removing one entity: expected 1, got {}", appInstance->GetEntityCount());
    }
    std::println(std::cout, "Trying to remove already removed entity.");
    appInstance->RemoveEntity(entityOneName);
    if (appInstance->GetEntityCount() != 1)
    {
        std::println(std::cerr, "Entity count mismatch after removing one entity: expected 1, got {}", appInstance->GetEntityCount());
    }

    appInstance->RemoveEntity(entityTwoName);
    if (appInstance->GetEntityCount() != 0)
    {
        std::println(std::cerr, "Entity count mismatch after removing one entity: expected 0, got {}", appInstance->GetEntityCount());
    }
    std::println(std::cout, "Successfully removed entities.");
    return 0;
}