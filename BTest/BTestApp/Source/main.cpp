#include "ECSApp/ECSAppAPI.hpp"

int main()
{
    const std::shared_ptr AppInstance{ECSApp::GetAppInstance()};
    AppInstance->AddEntity("Test");
    AppInstance->RemoveEntity("Test");
    AppInstance->AddManagerToEntity("Test", "Test");
    AppInstance->RemoveManagerFromEntity("Test", "Test");

    return 0;
}
