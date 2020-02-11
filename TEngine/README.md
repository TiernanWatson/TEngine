# Odyssey Game Engine

Odyssey is a data-driven game engine featuring an entity-component-system architecture.  It is being developed and designed for Windows, but in such a way that it can be made cross-platform.

The game loop of the engine provides flexibilty with both a fixed and variable update.

The platform folder contains platform specific code, which then communicates with the platform-indepedence layer, which starts with the Engine class.  This class houses the main game loop, as well as the clock and major sub-systems such as the input, renderer and world systems.  

A world contains an entity manager (ECS) for all the entities in the world, as well as a collection of world scripts, which can run via inheritance from WorldScript.

## Progress

* Stack allocator ~5.8% faster than malloc
* Pool allocator ~9.8% faster than malloc
* Heap allocator work-in-progress
* ECS system can add/remove entities
  * ECS can loop over all matching archetypes with function
* D3D11 renderer renders everything with mesh component
  * Working on implementing render passes and queues
* World system loops over world scripts
  * Still need to add serialization
* Windows platform sends input information to main engine
  * Input is useable by world scripts

## Setup

You will need:
* Visual Studio 2017+
* DirectX 11+
* Freetype 2.10.1 (link via project properties)
* Assimp 4.1.0 (link via project properties)

stb_image is included in the External folder.

## Usage

The engine is still currently very much in development, and world serialization still needs to be added.  
However, there is a default test world that will run if started from Visual Studio.