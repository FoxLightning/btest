// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include <iostream>
#include <print>
#include <string>
#include <vector>

#include "ECSApp/ECSAppAPI.hpp"

int main()
{
    const auto entityOneName     = ECSApp::EntityName{"TestEntityOne"};
    const auto entityTwoName     = ECSApp::EntityName{"TestEntityTwo"};
    const auto actionManagerType = ECSApp::ManagerType{"ActionManager"};

    const auto moveActionType   = ECSApp::ObjectType{"MoveAction"};
    const auto toggleActionType = ECSApp::ObjectType{"ToggleAction"};
    const auto actionNameOne    = ECSApp::ObjectName{"MoveTo10x20"};
    const auto actionNameTwo    = ECSApp::ObjectName{"ToggleToTrue"};

    const auto appInstance = ECSApp::GetAppInstance();
    appInstance->AddEntity(entityOneName);
    appInstance->AddEntity(entityTwoName);

    appInstance->AddManagerToEntity(entityOneName, actionManagerType);
    appInstance->AddManagerToEntity(entityTwoName, actionManagerType);

    appInstance->AddObjectToEntity(entityOneName, moveActionType, actionNameOne);
    appInstance->AddObjectToEntity(entityTwoName, toggleActionType, actionNameTwo);

    std::vector<std::string> actionList;
    if (!appInstance->GetVisibleActions(entityOneName, actionList) || actionList.empty())
    {
        std::println(std::cerr, "Action list for entity one is empty or failed to retrieve.");
        return 1;
    }
    if (actionList[0] != actionNameOne.str)
    {
        std::println(std::cerr, "Action name mismatch: expected {}, got {}", actionNameOne.str, actionList[0]);
        return 1;
    }
    std::println(std::cout, "Successfully added and retrieved action for entity one.");

    actionList.clear();
    if (!appInstance->GetVisibleActions(entityTwoName, actionList) && !actionList.empty())
    {
        return 1;
    }
    if (actionList[0] != actionNameTwo.str)
    {
        std::println(std::cerr, "Action name mismatch: expected {}, got {}", actionNameTwo.str, actionList[0]);
        return 1;
    }
    std::println(std::cout, "Successfully added and retrieved action for entity two.");
    return 0;
}