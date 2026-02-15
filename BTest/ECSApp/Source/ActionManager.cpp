// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ActionManager.hpp"

#include <cassert>
#include <iostream>
#include <memory>
#include <print>
#include <string>
#include <vector>

#include "ECSCore/Object.hpp"

#include "ActionObject.hpp"

std::vector<std::weak_ptr<ECSApp::ActionObjectBase>> ECSApp::ActionManager::GetVisibleActions() const
{
    std::vector<std::weak_ptr<ActionObjectBase>> outArray;
    ForEachObject(
        [&outArray](const std::weak_ptr<ECSCore::Object>& action)
        {
            if (const auto sharedAction = std::static_pointer_cast<ActionObjectBase>(action.lock());
                sharedAction->IsVisible())
            {
                outArray.push_back(sharedAction);
            }
        });
    return outArray;
}

bool ECSApp::ActionManager::PostAttachObjectToComponent(const std::weak_ptr<ECSCore::Object> object)
{
    if (const auto action = std::dynamic_pointer_cast<ActionObjectBase>(object.lock()))
    {
        actionStorage.push_back(action);
        return true;
    }
    std::println(std::cerr, "Invalid object type for ActionManager");
    assert(false);
    return false;
}

bool ECSApp::ActionManager::RemoveAction(const std::string& actionName)
{
    const auto deletedCount = std::erase_if(actionStorage, [actionName](const std::shared_ptr<ActionObjectBase>& action)
                                            { return action->GetName() == actionName; });

    if (deletedCount > 1)
    {
        std::println(std::cerr, "Multiple actions with the same name found: {}", actionName);
    }
    assert(deletedCount <= 1);
    return deletedCount == 1;
}
