# Cub3D

## Overview
**Cub3D** is a 3D graphics project based on the classic Wolfenstein 3D game. Using raycasting techniques, this project involves creating a simple first-person shooter game that provides a basic 3D rendering of a 2D map. The goal is to implement a small game engine capable of rendering a world, handling player movements, and interacting with the environment.

## Features
- **2D to 3D Rendering**:
  - Raycasting-based rendering for realistic walls and textures.
- **Player Movement**:
  - Smooth player navigation with forward, backward, left, and right movement.
  - Rotation of the view using the keyboard.
- **Environment Interaction**:
  - Detect collisions with walls.
  - Simple object interactions (optional).
- **Customizable Maps**:
  - Load maps from `.cub` files, allowing flexible level design.
- **Texture and Color Support**:
  - Apply textures to walls.
  - Define floor and ceiling colors.

## Prerequisites
To build and run Cub3D, you need:
- **C** compiler (`gcc` or `clang`).
- A graphics library (e.g., **MinilibX**).
- Basic knowledge of linear algebra and trigonometry.

## Getting Started

### 1. Clone the repository:
  ```bash
  git clone https://github.com/3bduu/Cub3D.git
  cd cub3d
  ```
### 2. Run the game:
 ```bash
./cub3d maps/example.cub
```
### 3. Controls:
  - W/A/S/D: Move forward/left/backward/right.
  - Left/Right Arrow Keys: Rotate the player's view.
  - ESC: Exit the game.
