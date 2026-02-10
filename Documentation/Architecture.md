# Package Diagram

Describes mudules and their relationships

```mermaid
flowchart TD

%% Entities
    CLIApp["CLI Application (btestapp)"]
    ECSCore["ECS Core (ecscore)"]
    ECSApp["ECS Application (ecsapp)"]
    Test["Test Module (coretest)"]
    FunLib["Functional Library (funlib)"]
%% Relations
    Test --> ECSApp;
    ECSApp --> ECSCore;
    CLIApp --> ECSApp;
    Test --> ECSCore;
    Test --> CLIApp;
    ECSCore --> FunLib;
```

## Modules responsibilities

### CLI Application

- Parsing CLI commands
- Send messages to **ECS Core** and receive results
- Printing and format results
- Provide **how to use** documentation
- Provide CLI

### ECS Core

- Provide base classes hierarchy for extension by app code.
- Entity and Object lifecycle management.

### ECS App

- Customization of the **ECS Core**
- Implements custom classes: Action Manager and Actions
- Provide API

### Test Module

- Unit tests for **ECS Core**
- Functional tests for **CLI Application**

### Functional Library

- Provide TName template

# ECS Core Class Diagram

```mermaid
classDiagram
%% Class definitions
    class Entity {
        - ObjectManagerComponent[]: managerTuple
        + ObjectManagerComponent*: GetManager(Type)
        + ObjectManagerComponent*: CreateManager(Type)
    }

    class ObjectManagerComponent {
        - Object[]: objectPool
        + void: ForEachObject(Function)
    }

    class Object {
        - Entitie*: owner
        + Object: Object(Entity* owner)
    }

%% relationships
    ObjectManagerComponent "1" *-- "0..*" Entity
    Object "1" o-- "0..*" ObjectManagerComponent
```

## ECS Core class responsibilities

### Entity

- Store managers (Single manager per type)

### ObjectManager

- Store raw references to objects
- Provide iteration over objects corresponding type

### Object

- Provide an object registration mechanism and guarantee that valid reference in the object manager

## ECS App Class Diagram

```mermaid
classDiagram
%% Class definitions
    class ActionManagerComponent {
        + void : GetVisibleActions(ActionObject[]* visibleActions)
    }

    class ActionObject {
        <<abstract>>
        + string : ToString()
        + bool: IsVisible()
    }

    class IAPI {
        <<Interface>>
        + void AddObject(string: Name, bool visible)
        + string[] GetVisibleEntities()
    }

    class APPInstance {
        - Entity : rootEntity
        + void AddEntity(string: Name)
        + void AddComponent(string: EntityName, Type, string: ComponentName)
        + string[0..*] GetVisibleEntities()
    }

%% relationships
    ActionManagerComponent --|> ManagementComponent
    ActionObject --|> Object
    APPInstance ..|> IAPI
```

## ECS App class responsibilities

### API

- Provides API for ECS App

### APPInstance

- Provides implementation of API
- Instantiate ECS Core classes

### ManagementComponent

- Action retrieve visible actions

### ActionObject

- Provide interface for Actions
- Open for extension


