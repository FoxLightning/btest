# Gameplay Programmer Test "ObjectManager" V3

This is a test task for Bohemia Interactive for a programmer role.

[Architecture documentation can be found here](Documentation/Architecture.md)

[Report with results can be found here](Documentation/Results.md)

# How to use

The project is built on top of the CMake project generator. There are two ways to build the project:

1. Use an extension for your IDE (CLion / VSCode recommended)
2. Use CMake manually to generate the project and then build it with your IDE or command line tools.

### Dependencies

There are no external library dependencies, only compiler or CMake bundled.

Required dependencies:

- C++23 compatible compiler (latest `clang` and `msvc` tested)
- CMake 3.20 or higher

Recommended dependencies:

- clang toolchain (clang-tidy, clang-format, clangd)
- CLion or VSCode with CMake Tools, clang, and clang-format extensions

### CLion setup

- Everything should work out of the box: just open the project in CLion and it will generate the project for you.
- Open the CMake icon in the bottom left corner and press `Reload CMake project`.
- Choose `BTestApp` as the startup project and run it.

### VSCode setup

- Install the `ms-vscode.cmake-tools` extension.
- Open the CMake Tools extension.
- Press the `Delete Cache and Reconfigure` button.
- Choose `BTestApp` as the startup project and run it.

### Terminal + Visual Studio 22 setup

1. Choose a build system (e.g. Visual Studio, Makefiles, etc.)

- Type in terminal `cmake --help` to see the list of supported generators.
- Copy the name of the generator you want to use (e.g. "Visual Studio 17 2022").

2. Generate the project for your build system

- Open a terminal in the root folder.
- Run `cmake -S . -B build -G "Visual Studio 17 2022"`.

3. Build generated project
- Run `cmake --build build --config Debug` to build the project in Debug configuration.
- Go to the `build` folder and find a corresponding executable file for `BTestApp`
- You can also open the generated solution file in Visual Studio and build it from there. 


# How to commit

The project uses clang-tidy and clang-format.  
For tests, the CMake default test framework is used.  
The project supports clangd, so you can use any IDE with clangd support.

### Linter

Clang-tidy also runs during a build process.
To check all problems without recompiling the project, you can run clang-tidy with the following command.  
This command considers the `build` folder as the CMake generated project folder.

``` PS1
run-clang-tidy -p build
```
Add `-fix` argument to automatically fix all problems that can be fixed by clang-tidy automaticaly.
``` PS1 
run-clang-tidy -p build -fix
```

### Formatter

Just use VSCode or CLion 


### How to test

Before test execution, make sure you have generated and built all modules.

Assuming you generated the project in the `build` folder, you can run tests with the following command:

```PS1
ctest --test-dir build
```
