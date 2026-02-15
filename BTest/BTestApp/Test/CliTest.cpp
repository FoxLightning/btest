// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include <array>
#include <cassert>
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <print>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "ECSApp/ECSAppAPI.hpp"

#include "CliAppState.hpp"

class ECSAppMock : public ECSApp::IECSAppAPI
{
  public:
    bool AddEntity(const ECSApp::EntityName& /*name*/) override
    {
        return true;
    }
    bool RemoveEntity(const ECSApp::EntityName& /*name*/) override
    {
        return true;
    }
    bool AddManagerToEntity(const ECSApp::EntityName& /*name*/, const ECSApp::ManagerType& /*type*/) override
    {
        return true;
    }
    bool RemoveManagerFromEntity(const ECSApp::EntityName& /*name*/, const ECSApp::ManagerType& /*type*/) override
    {
        return true;
    }
    bool AddObjectToEntity(const ECSApp::EntityName& /*name*/, const ECSApp::ObjectType& /*type*/,
                           const ECSApp::ObjectName& /*objName*/) override
    {
        return true;
    }
    bool RemoveActionFromEntity(const ECSApp::EntityName& /*name*/, const ECSApp::ObjectName& /*objName*/) override
    {
        return true;
    }
    bool GetVisibleActions(const ECSApp::EntityName& /*name*/, std::vector<std::string>& /*outActions*/) override
    {
        return true;
    }
    bool GetActionTypes(std::vector<std::string>& out) override
    {
        out = {"MoveAction", "ToggleAction"};
        return true;
    }
    bool GetManagerTypes(std::vector<std::string>& out) override
    {
        out = {"ActionManager"};
        return true;
    }
    size_t GetEntityCount() override
    {
        return 0;
    }
};

static void TestAddEntityValid()
{
    auto               mockApi = std::make_shared<ECSAppMock>();
    std::istringstream input("add_ent TestEntity\n");
    std::ostringstream output;
    std::ostringstream error;

    CLIApp::CLIApplicaition app(mockApi, input, output, error);
    app.FetchInput();
    app.CallCommand();

    assert(error.str().empty());
    std::println(std::cout, "TestAddEntityValid passed.");
}

static void TestAddEntityMissingArgs()
{
    auto               mockApi = std::make_shared<ECSAppMock>();
    std::istringstream input("add_ent\n");
    std::ostringstream output;
    std::ostringstream error;

    CLIApp::CLIApplicaition app(mockApi, input, output, error);
    app.FetchInput();
    app.CallCommand();

    assert(!error.str().empty());
    std::println(std::cout, "TestAddEntityMissingArgs passed.");
}

static void TestExitCommand()
{
    auto               mockApi = std::make_shared<ECSAppMock>();
    std::istringstream input("exit\n");
    std::ostringstream output;
    std::ostringstream error;

    CLIApp::CLIApplicaition app(mockApi, input, output, error);
    app.FetchInput();
    app.CallCommand();
    assert(app.ShouldExit());
    std::println(std::cout, "TestExitCommand passed.");
}

static void TestActionTypes()
{
    auto               mockApi = std::make_shared<ECSAppMock>();
    std::istringstream input("act_lst\n");
    std::ostringstream output;
    std::ostringstream error;

    CLIApp::CLIApplicaition app(mockApi, input, output, error);
    app.FetchInput();
    app.CallCommand();

    std::array<std::string_view, 2> const expectedOutput{"MoveAction", "ToggleAction"};
    auto                            outString = output.str();
    assert(error.str().empty());
    for (auto expected : expectedOutput)
    {
        assert(outString.contains(expected));
    }
    std::println(std::cout, "TestActionTypes passed.");
}

static void TestManagerTypes()
{
    auto               mockApi = std::make_shared<ECSAppMock>();
    std::istringstream input("mng_lst\n");
    std::ostringstream output;
    std::ostringstream error;

    CLIApp::CLIApplicaition app(mockApi, input, output, error);
    app.FetchInput();
    app.CallCommand();

    std::array<std::string_view, 1> const expectedOutput{"ActionManager"};
    auto                            outString = output.str();
    assert(error.str().empty());
    for (auto expected : expectedOutput)
    {
        assert(outString.contains(expected));
    }
    std::println(std::cout, "TestManagerTypes passed.");
}

int main()
{
    try
    {
        TestAddEntityValid();
        TestAddEntityMissingArgs();
        TestExitCommand();
        TestActionTypes();
        TestManagerTypes();

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception occurred: " << e.what() << "\n";
        return 1;
    }
}