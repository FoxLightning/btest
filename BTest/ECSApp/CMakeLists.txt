add_library(ECSApp STATIC
        Source/AppInstance.cpp
)
target_include_directories(ECSApp
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)
