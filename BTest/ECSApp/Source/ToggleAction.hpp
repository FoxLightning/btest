// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once
#include <format>
#include <memory>

#include "ActionObject.hpp"

namespace ECSCore
{
class Entity;
}

namespace ECSApp
{

class ToggleAction : public ActionObjectBase
{

  public:
    ToggleAction(const std::weak_ptr<ECSCore::Entity>& inOwner, const ObjectName& objectName,
                 const std::string& inIsActive)
        : ActionObjectBase(inOwner, objectName)
    {
        isActive = inIsActive == "true";
    }

    bool IsVisible() const override
    {
        return true;
    }

    std::string Print() const override
    {
        return std::format("Toggle action: {}", isActive ? "ON" : "OFF");
    }

    static constexpr std::string::const_pointer GetTypeName()
    {
        return "ToggleAction";
    }

  private:
    bool isActive{true};
};

} // namespace ECSApp
