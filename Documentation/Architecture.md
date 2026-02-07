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
    class EntityManager {
        - Entity[0..*]: EntitiePool
        + TName: CreateEntity(Type)
        + void: DeleteEntitie(ID)
        + void: ForEachEntity(Function)
    }

    class Entity {
        - TName: ID
        - ObjectManagerComponent[*]: ManagerTuple
        + TName: GetID()
        + ObjectManagerComponent&: GetManager(Type)
    }

    class ObjectManagerComponent {
        - Object[0..*]: ObjectPool
        + TName: CreateObject(Type)
        + void: DeleteObject(ID)
        + void: ForEachObject(Function)
    }

    class Object {
        - TName: ID
        - Entitie*: Owner
        - ObjectManagerComponent: ManagerTrait
        + TName: GetID()
    }

%% relationships
    EntityManager "1" *-- "0..*" Entity
    Entity "1" *-- "0..*" ObjectManagerComponent
    ObjectManagerComponent "1" *-- "0..*" Object
```

## ECS Core class responsibilities

### EntityManager

- Entity lifecycle management
- Store and retrieve entities

### Entity

- Store managers
- Provide unique identifier

### ObjectManagerComponent

- Object lifecycle management
- Store objects
- Open for extension

### Object

- Provide unique identifier
- Open for extension

## ECS App Class Diagram

```mermaid
classDiagram
%% Class definitions
    class ActionManagerComponent {
        + ActionObject[0..*] GetVisibleActions()
    }

    class ActionObject {
        <<abstract>>
        + TName: GetType()
        + bool: IsVisible()
    }

    class IAPI {
        <<Interface>>
        + void AddEntity(string: Name)
        + void AddComponent(string: EntityName, Type, string: ComponentName)
        + string[0..*] GetVisibleEntities()
    }

    class APPInstance {
        - EntitieManager Manager:
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


