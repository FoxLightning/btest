// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ECSCore/ObjectManager.hpp"

#include "ActionObject.hpp"

namespace ECSApp
{

class ActionManager : public ECSCore::TObjectManager<ActionObjectBase>
{
  public:
    static std::string GetManagerTypeName()
    {
        return "ActionManager";
    }

    [[nodiscard]] std::vector<std::weak_ptr<ActionObjectBase>> GetVisibleActions() const;
    bool PostAttachObjectToComponent(std::weak_ptr<ECSCore::Object> object) override;
    bool RemoveAction(const std::string& actionName);

    ActionManager() = default;
    ~ActionManager() override = default;
private:
    std::vector<std::shared_ptr<ActionObjectBase>> actionStorage;
};

} // namespace ECSApp
