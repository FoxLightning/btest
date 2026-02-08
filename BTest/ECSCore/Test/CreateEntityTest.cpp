// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ECSCore/EntityManager.hpp"

#include <ECSCore/Entity.hpp>
#include <cstdint>
#include <format>
#include <print>
#include <string>

int main()
{
    ECSCore::EntityManager manager;

    std::println("Creating entities ...");
    constexpr int32_t iterations{ 10 };
    
    for (int32_t i = 1; i <= iterations; ++i)
    {
        const std::string name{ std::format("Entity_{}", i) };
        auto entity = manager.CreateEntity(name);
        std::println("Creating entity with name \"{}\"", name);
        if (entity->GetName() != name)
        {
            std::println("Entity name is \"{}\". Should be \"{}\".", entity->GetName(), name);
            return 1;
        }
        if (entity = manager.GetEntity(name); !entity)
        {
            std::println("Entity with name \"{}\" not found.", name);
            return 1;
        }
        if (manager.GetEntityCount() != i)
        {
            std::println("Entity count is {}. Should be {}.", manager.GetEntityCount(), i);
            return 1;
        }
    }

    std::println("Creating entities with same name...");
    for (int32_t i = 1; i <= iterations; ++i)
    {
        const std::string name{std::format("Entity_{}", i)};
        auto              entity = manager.CreateEntity(name);
        std::println("Creating entity with name \"{}\"", name);
        if (manager.GetEntityCount() != iterations)
        {
            std::println("Entity count is {}. Should be {}.", manager.GetEntityCount(), iterations);
            return 1;
        }
    }
    return 0;
}
