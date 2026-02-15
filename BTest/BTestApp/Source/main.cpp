// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "CliAppState.hpp"
#include "ECSApp/ECSAppAPI.hpp"

int main()
{
    CLIApp::CLIApp cliApp(ECSApp::GetAppInstance());
    while (!cliApp.ShouldExit())
    {
        cliApp.FetchInput();
        cliApp.CallCommand();
        cliApp.ResetState();
    }

    return 0;
}
