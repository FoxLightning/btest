# Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

add_library(ECSCore STATIC
        Source/Entity.cpp
        Source/Object.cpp
)

target_include_directories(ECSCore
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_link_libraries(ECSCore
        PUBLIC
        FunLib
)


add_custom_test(ObjectCreateDeleteTest ECSCore ECSCore FunLib)
add_custom_test(ManagerCreateDeleteTest ECSCore ECSCore FunLib)
add_custom_test(ObjectCreateDeleteTestSparsedArray ECSCore ECSCore FunLib)
add_custom_test(ManagerCreateDeleteTestSparsedArray ECSCore ECSCore FunLib)
