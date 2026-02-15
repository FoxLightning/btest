// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "CliAppState.hpp"

#include <print>
#include <sstream>
#include <string>
#include <vector>

#include "ECSApp/ECSAppAPI.hpp"

namespace CLIApp
{
void CLIApplicaition::FetchInput()
{
    std::string input;
    std::getline(inputStream, input);

    std::istringstream iss(input);
    std::string        currentWord;

    iss >> commandState.command;
    while (iss >> currentWord)
    {
        commandState.arguments.push_back(currentWord);
    }
}

void CLIApplicaition::CallCommand()
{
    auto commandIt = GCommandsMap.find(commandState.command);

    if (commandState.command == GCommandExit)
    {
        shouldExit = true;
        return;
    }
    if (commandState.command == GCommandAddEnt)
    {
        if (commandState.arguments.size() == commandIt->second.arguments.size())
        {
            ecsApp->AddEntity(ECSApp::EntityName{commandState.arguments[0]});
            return;
        }
        std::println(errorStream, R"(Invalid arguments count for "{}" command. Expected {}, got {})",
                     commandState.command, commandIt->second.arguments.size(), commandState.arguments.size());
    }
    else if (commandState.command == GCommandDelEnt)
    {
        if (commandState.arguments.size() == commandIt->second.arguments.size())
        {
            ecsApp->RemoveEntity(ECSApp::EntityName{commandState.arguments[0]});
            return;
        }
        std::println(errorStream, R"(Invalid arguments count for "{}" command. Expected {}, got {})",
                     commandState.command, commandIt->second.arguments.size(), commandState.arguments.size());
    }
    else if (commandState.command == GCommandAddObj)
    {
        if (commandState.arguments.size() == commandIt->second.arguments.size())
        {
            ecsApp->AddObjectToEntity(ECSApp::EntityName{commandState.arguments[0]},
                                      ECSApp::ObjectType{commandState.arguments[1]},
                                      ECSApp::ObjectName{commandState.arguments[2]});
            return;
        }
        std::println(errorStream, R"(Invalid arguments count for "{}" command. Expected {}, got {})",
                     commandState.command, commandIt->second.arguments.size(), commandState.arguments.size());
    }
    else if (commandState.command == GCommandDelObj)
    {
        if (commandState.arguments.size() == commandIt->second.arguments.size())
        {
            ecsApp->RemoveActionFromEntity(ECSApp::EntityName{commandState.arguments[0]},
                                           ECSApp::ObjectName{commandState.arguments[1]});
            return;
        }
        std::println(errorStream, R"(Invalid arguments count for "{}" command. Expected {}, got {})",
                     commandState.command, commandIt->second.arguments.size(), commandState.arguments.size());
    }
    else if (commandState.command == GCommandAddMng)
    {
        if (commandState.arguments.size() == commandIt->second.arguments.size())
        {
            ecsApp->AddManagerToEntity(ECSApp::EntityName{commandState.arguments[0]},
                                       ECSApp::ManagerType{commandState.arguments[1]});
            return;
        }
        std::println(errorStream, R"(Invalid arguments count for "{}" command. Expected {}, got {})",
                     commandState.command, commandIt->second.arguments.size(), commandState.arguments.size());
    }
    else if (commandState.command == GCommandDelMng)
    {
        if (commandState.arguments.size() == commandIt->second.arguments.size())
        {
            ecsApp->RemoveManagerFromEntity(ECSApp::EntityName{commandState.arguments[0]},
                                            ECSApp::ManagerType{commandState.arguments[1]});
            return;
        }
        std::println(errorStream, R"(Invalid arguments count for "{}" command. Expected {}, got {})",
                     commandState.command, commandIt->second.arguments.size(), commandState.arguments.size());
    }
    else if (commandState.command == GCommandPrint)
    {
        if (commandState.arguments.size() == commandIt->second.arguments.size())
        {
            std::vector<std::string> visibleActions;
            if (ecsApp->GetVisibleActions(ECSApp::EntityName{commandState.arguments[0]}, visibleActions))
            {
                if (visibleActions.empty())
                {
                    std::println(outputStream, R"(No visible actions for "{}" entity.)", commandState.arguments[0]);
                    return;
                }
                std::println(outputStream, R"(Visible actions for "{}" entity:)", commandState.arguments[0]);
                for (const auto& action : visibleActions)
                {
                    std::println(outputStream, R"(  {})", action);
                }
            }
            return;
        }
        std::println(errorStream, R"(Invalid arguments count for "{}" command. Expected {}, got {})",
                     commandState.command, commandIt->second.arguments.size(), commandState.arguments.size());
    }
    else if (commandState.command == GCommandMngLst)
    {
        if (commandState.arguments.size() == commandIt->second.arguments.size())
        {
            std::vector<std::string> managers;
            if (ecsApp->GetManagerTypes(managers))
            {
                if (managers.empty())
                {
                    std::println(outputStream, R"(No available manager types.)");
                    return;
                }
                std::println(outputStream, R"(Available manager types:)");
                for (const auto& manager : managers)
                {
                    std::println(outputStream, R"(  {})", manager);
                }
            }
            return;
        }
        std::println(errorStream, R"(Invalid arguments count for "{}" command. Expected {}, got {})",
                     commandState.command, commandIt->second.arguments.size(), commandState.arguments.size());
    }
    else if (commandState.command == GCommandActLst)
    {
        if (commandState.arguments.size() == commandIt->second.arguments.size())
        {
            std::vector<std::string> actions;
            if (ecsApp->GetActionTypes(actions))
            {
                if (actions.empty())
                {
                    std::println(outputStream, R"(No available action types.)");
                    return;
                }
                std::println(outputStream, R"(Available action types:)");
                for (const auto& action : actions)
                {
                    std::println(outputStream, R"(  {})", action);
                }
            }
            return;
        }
        std::println(errorStream, R"(Invalid arguments count for "{}" command. Expected {}, got {})",
                     commandState.command, commandIt->second.arguments.size(), commandState.arguments.size());
    }
    else if (commandState.command == GCommandHelp)
    {
        PrintHelp();
        return;
    }
    else
    {
        std::println(errorStream, R"(Unknown command: "{}")", commandState.command);
    }
    std::println(outputStream, GInvalidCommandError, "help");
}

void CLIApplicaition::ResetState()
{
    commandState = {};
}

bool CLIApplicaition::ShouldExit() const
{
    return shouldExit;
}

void CLIApplicaition::PrintHelp() const
{
    auto formatArgs = [](const auto& argsVector)
    {
        std::string result;
        for (const auto& arg : argsVector)
        {
            if (!result.empty())
            {
                result += " ";
            }
            result += arg;
        }
        return result;
    };

    std::println(outputStream, R"(Commands:)");

    for (const auto& [commandName, commandInfo] : GCommandsMap)
    {
        std::println(outputStream, R"(  "{}" {} - {})", commandName, formatArgs(commandInfo.arguments),
                     commandInfo.description);
    }
}

} // namespace CLIApp
