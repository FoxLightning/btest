// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ECSCore/EntityManager.hpp"

#include <ECSCore/Entity.hpp>
#include <cstdint>
#include <format>
#include <ostream>
#include <print>
#include <string>
#include <string_view>

int main()
{
    ECSCore::EntityManager manager;

    std::println("Creating entities ...");
    constexpr int32_t          iterations{10};
    constexpr std::string_view NamePattern{"Entity_{}"};

    for (int32_t i = 1; i <= iterations; ++i)
    {
        const std::string name{std::format(NamePattern, i)};
        auto              entity = manager.CreateEntity(name);
        std::println(R"(Creating entity with name "{}")", name);
        if (entity->GetName() != name)
        {
            std::println(R"(Entity name is "{}". Should be "{}".)", entity->GetName(), name);
            return 1;
        }
        if (entity = manager.GetEntity(name); !entity)
        {
            std::println(R"(Entity with name "{}" not found.)", name);
            return 1;
        }
        if (manager.GetEntityCount() != i)
        {
            std::println("Entity count is {}. Should be {}.", manager.GetEntityCount(), i);
            return 1;
        }
    }

    std::println("Deleting entities ...");
    for (int32_t i = 1; i <= iterations; ++i)
    {
        if (i % 2 == 1)
        {
            continue;
        }
        const std::string name{std::format(NamePattern, i)};
        manager.DeleteEntity(name);
        if (manager.GetEntity(name))
        {
            std::println(R"(Entity with name "{}" still exists.)", name);
            return 1;
        }
        if (manager.GetEntityCount() != iterations - i)
        {
            std::println("Entity count is {}. Should be {}.", manager.GetEntityCount(), iterations - 1);
        }
    }

    std::println("Creating entities again ...");
    for (int32_t i = 1; i <= iterations; ++i)
    {
        const std::string name{std::format(NamePattern, i)};
        auto              entity = manager.CreateEntity(name);
        std::println(R"(Creating entity with name "{}")", name);
        if (entity->GetName() != name)
        {
            std::println(R"(Entity name is "{}". Should be "{}".)", entity->GetName(), name);
            return 1;
        }
        if (entity = manager.GetEntity(name); !entity)
        {
            std::println(R"(Entity with name "{}" not found.)", name);
            return 1;
        }
    }

    if (manager.GetEntityCount() != iterations)
    {
        std::println("Entity count is {}. Should be {}.", manager.GetEntityCount(), iterations);
        return 1;
    }

    return 0;
}
