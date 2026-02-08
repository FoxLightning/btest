# Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

# TEST_NAME - test source cpp file name
function(add_custom_test TEST_NAME TEST_NAMESPACE)
    set(TARGET_LINKS ${ARGN}) # Variadic arg with libs
    set(FULL_TEST_NAME ${TEST_NAMESPACE}_${TEST_NAME})
    add_executable(${FULL_TEST_NAME} Test/${TEST_NAME}.cpp)
    target_include_directories(${FULL_TEST_NAME}
            PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/Source
    )

    target_link_libraries(${FULL_TEST_NAME} PRIVATE ${TARGET_LINKS})
    add_test(NAME ${FULL_TEST_NAME} COMMAND ${FULL_TEST_NAME})
endfunction()
