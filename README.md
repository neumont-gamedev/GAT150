# GAT150 - C++ Game Engine

A comprehensive 2D game engine built in C++ as part of Neumont University's GAT150 - Introduction to Game Programming course. This engine provides a solid foundation for 2D game development with modern graphics, physics, and audio capabilities.

## 🚀 Features

- **Cross-platform rendering** with SDL3
- **2D physics simulation** using Box2D
- **High-quality audio** powered by FMOD
- **Component-based architecture** for flexible game object management
- **Resource management system** with automatic loading and caching
- **Event-driven input handling** supporting keyboard, mouse, and gamepad
- **JSON-based configuration** for easy data management
- **Mathematical utilities** for 2D game development

## 🛠️ Technology Stack

- **Graphics & Windowing**: SDL3 with GPU abstraction layer
- **Physics**: Box2D for 2D rigid body dynamics
- **Audio**: FMOD for advanced audio processing and effects
- **Data Format**: JSON for configuration and asset definitions
- **Build System**: Visual Studio 2022 / MSBuild
- **Platform**: Windows (with cross-platform SDL3 foundation)

## 📁 Engine Architecture

### Core Systems

#### **Renderer System**
The rendering system built on SDL3 provides:
- Hardware-accelerated 2D graphics rendering
- Sprite rendering with transformations (position, rotation, scale)
- Text rendering using SDL3_TTF
- Image loading and management via SDL3_Image
- Viewport and camera management
- Layered rendering for depth sorting

#### **Physics System**
Box2D integration offering:
- Rigid body dynamics simulation
- Collision detection and response
- Joint and constraint systems
- Trigger volumes for gameplay events
- Continuous collision detection
- Configurable physics world parameters

#### **Audio System**
FMOD-powered audio engine featuring:
- 3D positional audio
- Real-time audio effects and filtering
- Music and sound effect management
- Audio streaming for large files
- Dynamic audio mixing and volume control
- Audio event system integration

#### **Input System**
Comprehensive input handling:
- Keyboard state management
- Mouse input with position tracking
- Gamepad/controller support
- Input mapping and customization
- Event-driven input processing
- Support for multiple input devices

#### **Resource Management**
Efficient asset pipeline:
- Automatic resource loading and caching
- JSON-based asset definitions
- Texture atlas support
- Font and audio file management
- Memory-efficient resource pooling
- Hot-reloading for development

#### **Scene Management**
Flexible scene architecture:
- Scene graph for hierarchical object organization
- Component-entity system for game objects
- Scene serialization and deserialization
- Dynamic scene loading and transitions
- Object lifecycle management

#### **Math Library**
Essential mathematical utilities:
- Vector2/Vector3 classes with full operations
- Matrix transformations for 2D graphics
- Color manipulation and utilities
- Collision and intersection algorithms
- Interpolation and easing functions
- Random number generation utilities

### Component Systems

#### **Transform Component**
- Position, rotation, and scale properties
- Hierarchical parent-child relationships
- Local and world space transformations
- Automatic matrix calculations

#### **Sprite Renderer Component**
- Texture rendering with UV mapping
- Sprite animation support
- Color tinting and alpha blending
- Sorting layers for render order

#### **Physics Components**
- RigidBody component for Box2D integration
- Collider components (Box, Circle, Polygon)
- Trigger components for gameplay events
- Physics material properties

#### **Audio Components**
- AudioSource for 3D positioned sound
- AudioListener for player perspective
- Music player for background tracks
- Sound effect triggers

## 🏗️ Project Structure

```
GAT150/
├── Source/
│   ├── Engine/           # Core engine systems
│   │   ├── Core/         # Fundamental engine classes
│   │   ├── Renderer/     # Graphics and rendering
│   │   ├── Audio/        # FMOD audio integration
│   │   ├── Input/        # Input handling systems
│   │   ├── Physics/      # Box2D physics wrapper
│   │   ├── Resources/    # Asset management
│   │   └── Math/         # Mathematical utilities
│   ├── Game/             # Game-specific implementation
│   └── ThirdParty/       # External libraries
│       ├── SDL3/         # SDL3 graphics library
│       ├── Box2D/        # Physics engine
│       └── FMOD/         # Audio engine
├── Assets/               # Game assets and resources
│   ├── Textures/
│   ├── Audio/
│   ├── Fonts/
│   └── Data/             # JSON configuration files
└── Build/                # Compiled binaries and DLLs
```

## 🔧 Getting Started

### Prerequisites

- Visual Studio 2022 with C++ development tools
- Windows 10/11 SDK
- Git for version control

### Building the Project

1. **Clone the repository**
   ```bash
   git clone https://github.com/neumont-gamedev/GAT150.git
   cd GAT150
   ```

2. **Initialize third-party libraries**
   - SDL3, Box2D, and FMOD libraries should be included in the ThirdParty directory
   - Copy required DLL files to the Build directory

3. **Open in Visual Studio**
   - Open `GAT150.sln` in Visual Studio 2022
   - Set the build configuration to Debug or Release
   - Set the platform to x64

4. **Build and Run**
   - Build the entire solution (Ctrl+Shift+B)
   - Set the Game project as the startup project
   - Run the application (F5)

## 📚 Learning Objectives

This project covers essential game programming concepts:

- **Engine Architecture**: Understanding how game engines are structured and organized
- **Graphics Programming**: 2D rendering pipelines and optimization techniques
- **Physics Integration**: Implementing realistic physics simulation in games
- **Audio Programming**: 3D audio positioning and real-time audio effects
- **Resource Management**: Efficient loading and management of game assets
- **Component Systems**: Flexible, data-driven game object architecture
- **Memory Management**: C++ best practices for game development
- **Cross-platform Development**: Writing portable game code

## 🤝 Contributing

This is an educational project for Neumont University students. Contributions should follow the course guidelines and coding standards established for GAT150.

## 📄 License

This project is part of Neumont University's curriculum and is intended for educational purposes.

## 🔗 Resources

- [SDL3 Documentation](https://wiki.libsdl.org/SDL3/)
- [Box2D Manual](https://box2d.org/documentation/)
- [FMOD Documentation](https://www.fmod.com/docs)
- [Neumont Game Dev Resources](https://neumont-gamedev.github.io/)

---

*Built with ❤️ for game development education at Neumont University*
