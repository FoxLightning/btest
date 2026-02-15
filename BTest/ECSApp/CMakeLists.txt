add_library(ECSApp STATIC
        Source/AppInstance.cpp
        Source/ActionManager.cpp
)
target_include_directories(ECSApp
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_link_libraries(ECSApp
        PUBLIC
        ECSCore
)

add_custom_test(AddRemoveEntityTest ECSApp ECSApp)
add_custom_test(AddRemoveManagerTest ECSApp ECSApp)
