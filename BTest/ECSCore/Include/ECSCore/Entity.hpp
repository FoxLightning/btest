// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once
#include <string>

namespace ECSCore
{

class Entity
{
  public:
    Entity() = delete;
    explicit Entity(std::string inName);
    virtual ~Entity();

    [[nodiscard]] std::string GetName() const;

  private:
    const std::string name;
};

} // namespace ECSCore
