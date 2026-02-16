# Design document

Architecture documentation is available here: [Documentation/Architecture.md](Documentation/Architecture.md)

# Container choice

Container implementations live in the `FunLib` module.

After performance testing, I decided to use `std::vector` as the primary container for objects in Object Managers.

That said, the best choice depends on the use case; a sparse array may perform better for workloads with frequent random insertions and deletions.

# App usage

Type `help` in the CLI to view available commands, or see `CliAppState.hpp`.

`BTestApp` is a CLI application that demonstrates usage of the ECS framework.

## Decision-making in git history

You can follow the decision-making process in the git history.
