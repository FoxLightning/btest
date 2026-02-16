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

## Time spent
According to git history and commit messages:

- Project Setup ~5 hrs
- ECS Core MVP ~7 hrs
- Architecture Refactoring ~8 hrs
- Testing & Profiling ~3 hrs
- ECS App + CLI Module ~8 hrs
- Sparse Array Container ~5 hrs

Overall: ~36h  
