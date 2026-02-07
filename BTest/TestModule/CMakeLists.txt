# ECS App Unit Tests
add_executable(AddEntityTest Source/AddEntityTest.cpp)
target_link_libraries(AddEntityTest PRIVATE ECSApp)
add_test(NAME AddEntityTest COMMAND AddEntityTest)

add_executable(RemoveEntityTest Source/RemoveEntityTest.cpp)
target_link_libraries(RemoveEntityTest PRIVATE ECSApp)
add_test(NAME RemoveEntityTest COMMAND RemoveEntityTest)
