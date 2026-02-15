// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "CliAppState.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ECSApp/ECSAppAPI.hpp"

namespace CLIApp
{
void CLIApp::FetchInput()
{
    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    std::string        currentWord;

    iss >> command;
    while (iss >> currentWord)
    {
        arguments.push_back(currentWord);
    }
}

void CLIApp::CallCommand()
{
    auto commandIt = GCommandsMap.find(command);

    if (command == GCommandExit)
    {
        shouldExit = true;
        return;
    }
    else if (command == GCommandAddEnt)
    {
        if (arguments.size() == commandIt->second.arguments.size())
        {
            ecsApp->AddEntity(ECSApp::EntityName{arguments[0]});
            return;
        }
        std::println(std::cerr, R"(Invalid arguments count for "{}" command. Expected {}, got {})", command,
                     commandIt->second.arguments.size(), arguments.size());
    }
    else if (command == GCommandDelEnt)
    {
        if (arguments.size() == commandIt->second.arguments.size())
        {
            ecsApp->RemoveEntity(ECSApp::EntityName{arguments[0]});
            return;
        }
        std::println(std::cerr, R"(Invalid arguments count for "{}" command. Expected {}, got {})", command,
                     commandIt->second.arguments.size(), arguments.size());
    }
    else if (command == GCommandAddObj)
    {
        if (arguments.size() == commandIt->second.arguments.size())
        {
            ecsApp->AddObjectToEntity(ECSApp::EntityName{arguments[0]}, ECSApp::ObjectType{arguments[1]},
                                      ECSApp::ObjectName{arguments[2]});
            return;
        }
        std::println(std::cerr, R"(Invalid arguments count for "{}" command. Expected {}, got {})", command,
                     commandIt->second.arguments.size(), arguments.size());
    }
    else if (command == GCommandDelObj)
    {
        if (arguments.size() == commandIt->second.arguments.size())
        {
            ecsApp->RemoveActionFromEntity(ECSApp::EntityName{arguments[0]}, ECSApp::ObjectName{arguments[1]});
            return;
        }
        std::println(std::cerr, R"(Invalid arguments count for "{}" command. Expected {}, got {})", command,
                     commandIt->second.arguments.size(), arguments.size());
    }
    else if (command == GCommandAddMng)
    {
        if (arguments.size() == commandIt->second.arguments.size())
        {
            ecsApp->AddManagerToEntity(ECSApp::EntityName{arguments[0]}, ECSApp::ManagerType{arguments[1]});
            return;
        }
        std::println(std::cerr, R"(Invalid arguments count for "{}" command. Expected {}, got {})", command,
                     commandIt->second.arguments.size(), arguments.size());
    }
    else if (command == GCommandDelMng)
    {
        if (arguments.size() == commandIt->second.arguments.size())
        {
            ecsApp->RemoveManagerFromEntity(ECSApp::EntityName{arguments[0]}, ECSApp::ManagerType{arguments[1]});
            return;
        }
        std::println(std::cerr, R"(Invalid arguments count for "{}" command. Expected {}, got {})", command,
                     commandIt->second.arguments.size(), arguments.size());
    }
    else if (command == GCommandPrint)
    {
        if (arguments.size() == commandIt->second.arguments.size())
        {
            std::vector<std::string> visibleActions;
            if (ecsApp->GetVisibleActions(ECSApp::EntityName{arguments[0]}, visibleActions))
            {
                if (visibleActions.empty())
                {
                    std::println(std::cout, R"(No visible actions for "{}" entity.)", arguments[0]);
                    return;
                }
                std::println(std::cout, R"(Visible actions for "{}" entity:)", arguments[0]);
                for (const auto& action : visibleActions)
                {
                    std::println(std::cout, R"(  {})", action);
                }
            }
            return;
        }
        std::println(std::cerr, R"(Invalid arguments count for "{}" command. Expected {}, got {})", command,
                     commandIt->second.arguments.size(), arguments.size());
    }
    else if (command == GCommandMngLst)
    {
        if (arguments.size() == commandIt->second.arguments.size())
        {
            std::vector<std::string> managers;
            if (ecsApp->GetManagerTypes(managers))
            {
                if (managers.empty())
                {
                    std::println(std::cout, R"(No available manager types.)");
                    return;
                }
                std::println(std::cout, R"(Available manager types:)");
                for (const auto& manager : managers)
                {
                    std::println(std::cout, R"(  {})", manager);
                }
            }
            return;
        }
        std::println(std::cerr, R"(Invalid arguments count for "{}" command. Expected {}, got {})", command,
                     commandIt->second.arguments.size(), arguments.size());
    }
    else if (command == GCommandActLst)
    {
        if (arguments.size() == commandIt->second.arguments.size())
        {
            std::vector<std::string> actions;
            if (ecsApp->GetActionTypes(actions))
            {
                if (actions.empty())
                {
                    std::println(std::cout, R"(No available action types.)");
                    return;
                }
                std::println(std::cout, R"(Available action types:)");
                for (const auto& action : actions)
                {
                    std::println(std::cout, R"(  {})", action);
                }
            }
            return;
        }
        std::println(std::cerr, R"(Invalid arguments count for "{}" command. Expected {}, got {})", command,
                     commandIt->second.arguments.size(), arguments.size());
    }
    else if (command == GCommandHelp)
    {
        PrintHelp();
        return;
    }
    else
    {
        std::println(std::cerr, R"(Unknown command: "{}")", command);
    }
    std::println(std::cout, GInvalidCommandError, "help");
}

void CLIApp::ResetState()
{
    command = "";
    arguments.clear();
}

bool CLIApp::ShouldExit() const
{
    return shouldExit;
}

void CLIApp::PrintHelp()
{
    auto FormatArgs = [](const auto& argsVector)
    {
        std::string result;
        for (const auto& arg : argsVector)
        {
            if (!result.empty())
                result += " ";
            result += arg;
        }
        return result;
    };

    std::println(std::cout, R"(Commands:)");

    for (const auto& [commandName, commandInfo] : GCommandsMap)
    {
        std::println(std::cout, R"(  "{}" {} - {})", commandName, FormatArgs(commandInfo.arguments),
                     commandInfo.description);
    }
}

} // namespace CLIApp
