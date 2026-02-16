# Package Diagram

Describes modules and their relationships.  
There are no double-sided dependencies between modules. Strictly layered architecture.

```mermaid
flowchart TD

%% Entities
    CLIApp["CLI Application (BTestApp)"]
    ECSCore["ECS Core (ECSCore)"]
    ECSApp["ECS Application (ECSApp)"]
    FunLib["Functional Library (FunLib)"]
%% Relations
    ECSApp --> ECSCore;
    CLIApp --> ECSApp;
    ECSCore --> FunLib;
```

## Module Responsibilities

### CLI Application

- Parse CLI commands
- Send messages to **ECS App** and receive results
- Print and format results
- Provide **how to use** documentation
- Provide CLI interface

### ECS Core

- Provide base class hierarchy for extension by app code
- Define base relationships between objects, entities, and managers

### ECS App

- Customize the **ECS Core**
- Implement custom classes: Action Manager and Actions
- Provide API

### Functional Library

- Provide custom containers

# ECS Core Class Diagram

```mermaid
classDiagram
%% Class definitions
    class Entity {
        - ObjectManagerComponent[] managerTuple
        + ObjectManagerComponent* GetManager(Type)
        + ObjectManagerComponent* CreateManager(Type)
    }

    class ObjectManager{
        - Object[] objectPool
        + void ForEachObject(Function)
    }

    class Object {
        - Entity* owner
        + Object(Entity* owner)
    }

%% relationships
    ObjectManager "1" o-- "0..*" Entity
    Object "1" o-- "0..*" ObjectManager
```

## ECS Core Class Responsibilities

### Entity

- Stores managers (single manager per type)

### ObjectManager

- Stores raw references to objects
- Provides iteration over objects of the corresponding type
- Only one manager should hold a shared reference to the object; all other managers should hold weak references
- `PostAttachObjectToComponent` should return true if the manager holds a shared reference

### Object

- Provides an object registration mechanism and guarantees a valid reference in the object manager

## ECS App Class Diagram

```mermaid
classDiagram
%% Class definitions
    class ActionManagerComponent {
        + void GetVisibleActions(ActionObject[]* visibleActions)
    }

    class ActionObject {
        <<abstract>>
        + string ToString()
        + bool IsVisible()
    }

    class IAPI {
        <<Interface>>
        + void AddObject(string Name, bool visible)
        + string[] GetVisibleEntities()
    }

    class APPInstance {
        - Entity rootEntity
        + void AddEntity(string Name)
        + void AddComponent(string EntityName, Type, string ComponentName)
        + string[0..*] GetVisibleEntities()
    }

%% relationships
    ActionManagerComponent --|> ManagementComponent
    ActionObject --|> Object
    APPInstance ..|> IAPI
```

## ECS App Class Responsibilities

### API

- Provides API for ECS App

### APPInstance

- Implements API
- Instantiates ECS Core classes

### ManagementComponent

- Retrieves visible actions

### ActionObject

- Provides interface for Actions
- Open for extension
