// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace ECSApp
{
struct ManagerType;
struct EntityName;
class IECSAppAPI;
} // namespace ECSApp
namespace CLIApp
{

using Callback = std::variant<bool (ECSApp::IECSAppAPI::*)(const ECSApp::EntityName&),
                              bool (ECSApp::IECSAppAPI::*)(const ECSApp::EntityName&, const ECSApp::ManagerType&)>;
struct CommandInfo
{
    std::string_view              description;
    std::vector<std::string_view> arguments;
};

static constexpr std::string_view GInvalidCommandError = R"(Type "{}" to see available commands.)";

static constexpr std::string_view GCommandExit   = "exit";
static constexpr std::string_view GCommandAddEnt = "add_ent";
static constexpr std::string_view GCommandDelEnt = "del_ent";
static constexpr std::string_view GCommandAddObj = "add_obj";
static constexpr std::string_view GCommandDelObj = "del_obj";
static constexpr std::string_view GCommandAddMng = "add_mng";
static constexpr std::string_view GCommandDelMng = "del_mng";
static constexpr std::string_view GCommandPrint  = "print";
static constexpr std::string_view GCommandMngLst = "mng_lst";
static constexpr std::string_view GCommandActLst = "act_lst";
static constexpr std::string_view GCommandHelp   = "help";

inline static const std::map<std::string_view, CommandInfo> GCommandsMap = {
    {GCommandExit, {"Exit the application", {}}},
    {GCommandAddEnt, {"Add a new entity", {"<1 entity name>"}}},
    {GCommandDelEnt, {"Remove an entity", {"<1 entity name>"}}},
    {GCommandAddObj, {"Add a new object", {"<1 entity name>", "<2 object type>", "<3 object name>"}}},
    {GCommandDelObj, {"Remove an object", {"<1 entity name>", "<2 name>"}}},
    {GCommandAddMng, {"Add a new manager", {"<1 entity name>", "<2 manager type>"}}},
    {GCommandDelMng, {"Remove a manager", {"<1 entity name>", "<2 manager type>"}}},
    {GCommandPrint, {"Print visible actions", {"<1 entity name>"}}},
    {GCommandMngLst, {"Print available managers", {}}},
    {GCommandActLst, {"Print available actions list", {}}},
    {GCommandHelp, {"Show this help message", {}}},
};

class CLIApplicaition
{
  public:
    CLIApplicaition(std::shared_ptr<ECSApp::IECSAppAPI> inECSApp, std::istream& inInputStream = std::cin,
           std::ostream& inOutputStream = std::cout, std::ostream& inErrorStream = std::cerr)
        : ecsApp(std::move(inECSApp)), inputStream(inInputStream), outputStream(inOutputStream),
          errorStream(inErrorStream)
    {
    }

    void FetchInput();
    void CallCommand();
    void ResetState();

    bool ShouldExit() const;

  private:
    void PrintHelp();

    std::shared_ptr<ECSApp::IECSAppAPI> ecsApp;

    std::istream& inputStream;
    std::ostream& outputStream;
    std::ostream& errorStream;

    struct CommandState
    {
        std::string              command   = "";
        std::vector<std::string> arguments = {};
    } commandState;
    bool shouldExit{false};
};

} // namespace CLIApp
