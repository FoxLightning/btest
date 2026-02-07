#include "ECSApp/CLI.hpp"

int main()
{
    auto appInstance = ecsapp::GetAppInstance();
    appInstance->AddEntity("Test");
    return 0;
}
