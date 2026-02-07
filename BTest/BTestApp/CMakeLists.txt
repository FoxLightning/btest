add_executable(BTestApp
        Source/main.cpp
)

target_link_libraries(BTestApp
        PRIVATE ECSApp
)
