#include "ECSApp/CLI.hpp"

int main()
{
    const std::shared_ptr AppInstance{ecsapp::GetAppInstance()};
    AppInstance->AddEntity("Test");
    AppInstance->RemoveEntity("Test");
    AppInstance->AddComponent("Test", "Test", "Test");
    AppInstance->RemoveComponent("Test", "Test", "Test");

    return 0;
}
