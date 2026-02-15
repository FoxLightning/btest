# Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

add_executable(BTestApp
        Source/main.cpp
        Source/CliAppState.cpp
)

target_link_libraries(BTestApp
        PRIVATE ECSApp
)
