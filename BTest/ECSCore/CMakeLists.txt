# Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

add_library(ECSCore STATIC
        Source/EntityManager.cpp
        Source/Entity.cpp
        Source/ObjectManager.cpp
        Source/Object.cpp
)

target_include_directories(ECSCore
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

add_custom_test(CreateEntityTest ECSCore ECSCore)
