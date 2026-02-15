# Gameplay Programmer Test "ObjectManager" V3

This is a test task for Bohemia Interactive for a programmer role

[Architecture documentation could be found here](Documentation/Architecture.md)

# How to use

Project built on top of cmake project generator. There are two ways to build the project:

1. Use extension for your IDE (CLion / VSCode recommended)
2. Use cmake manually to generate the project and then build it with your IDE or command line tools.

### CLion setup

- Everything should work out of the box, just open the project in CLion and it will generate the project for you.
- Open CMake icon in a bottom left corner and press `Reload CMake project`.
- Choose `BTestApp` as a startup project and run it.

### VSCode setup

- Install `ms-vscode.cmake-tools` extension
- Open cmake-tools extension and
- Press `Delete Cache and Reconfigure` button
- Choose `BTestApp` as a startup project and run it.

### Terminal + Visual Studio 22 setup

1. Choose a build system (e.g. Visual Studio, Makefiles, etc.)

- type in terminal `cmake --help` to see the list of spported generators
- copy the name of the generator you want to use (e.g. "Visual Studio 17 2022")

2. Generate the project for your build system

- open terminal in root folder
- run `cmake -S . -B build -G "Visual Studio 17 2022"`

3. Goto `build` folder and open the generated solution file `BTest.sln` with corresponding version of Visual Studio
4. Choose `BTestApp` as a startup project and run it.


# How to extend
Project uses clang-tidy and clang-format
For test - cmake default test framework
Project supports clangd - so you can use any IDE with clangd support.

### Linter
To check all problems without recompiling the project, you can run clang-tidy with the following command.
This command consider `build` folder as cmake generated project folder.
```  PS1
run-clang-tidy -p build
```
### How to test
Before test execution, make sure you have generated and cooked all modules.

I consider that you generated project in `build` folder, so you can run tests with the following command:
``` PS1
ctest --test-dir build
```
