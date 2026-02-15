#include "ECSApp/ECSAppAPI.hpp"

int main()
{
    auto appInstance = ECSApp::GetAppInstance();
    appInstance->AddEntity("Test");
    return 0;
}
