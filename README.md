# cub3d

## Screenshots

# Table of Contents
1. [Description](#description)
2. [Installation Instructions](#installation-instructions)
3. [Usage Instructions](#usage-instructions)
4. [Key Features](#key-features)
5. [Acknowledgments](#acknowledgments)

## Description

Cub3D is a 3D game development project that is part of the 42 curriculum and is implemented in C. The primary goal of this project is to create an immersive and interactive 3D game that provides an engaging gaming experience.

The game is designed with a focus on the fundamentals of 3D game development, including raycasting, rendering, user input handling, and collision detection. The challenge lies in creating a game that is not only visually appealing but also well-structured and efficient in terms of performance.

This project is a great opportunity to delve deeper into the workings of 3D game development and enhance your knowledge of programming in C. It tests your understanding of various programming concepts, including data structures, algorithms, and memory management.

## Installation Instructions

1. **Check Operating System**: This game is designed to run on Linux systems. Ensure you are running a compatible Linux distribution before proceeding with the installation.

2. **Install Necessary Packages**: Certain packages are required to run the game. You can install them using your distribution's package manager. For example, on Ubuntu, you can use the following command:

- X11 include files (package xorg)
- XShm extension must be present (package libxext-dev)
- Utility functions from BSD systems - development files (package libbsd-dev)

```bash
sudo apt install xorg libxext-dev libbsd-dev
```

3. **Install a C compiler**: If you don't already have a C compiler installed, you will need one to build and use this library. You can install the [GCC compiler](https://gcc.gnu.org).

- On a Linux machine, use the package manager for your distribution. For example, on Ubuntu:
```bash
sudo apt install build-essential
gcc --version
```

## Usage Instructions

1. **Compile the game**: Navigate to the project directory and compile the game using the `make` command:
```bash
make bonus
```
This will create an executable file named cub3d.

2. Select a map: Choose a map from the maps folder. Note the name of the map file.

3. Start the game: You can start the game by running the following command in your terminal:
```bash
./cub3d maps/minimalist.cub
```

## Controls

- `W`: Move Forward
- `A`: Move Left
- `S`: Move Backward
- `D`: Move Right
- `←` or Mouse Left: Turn Camera Left
- `→` or Mouse Right: Turn Camera Right
- `ESC` or Click the `X` in the Top-Right Corner: Exit the Game

## Key Features

- Advanced Collision System
- Multiplayer Mode
- Multiple Weapons
- Multiple Textures for Each Side of Walls (including floor and ceiling textures)
- Animated Weapons
- Minimap
- Interactive Doors

I was responsible for parsing:

- Checking textures: Ensuring there are no more than 4 textures (one for each side) and that textures are loaded correctly.
- Verifying floor and ceiling colors: Ensuring they fit within the RGB range, with one color for each and no more.
- Validating the map: Ensuring the player cannot go outside the map, there is only one player (for the mandatory part), and only allowed characters are present.

Thanks to my teammate, I was also introduced to multiplayer management. I handled collision detection between players and walls, as well as between bullets and guns. I implemented packet sending to the server to notify if a bullet hit another player.

## Acknowledgments

Special thanks to the following individuals and resources for their contributions to this project:

- [FirePh0enix](https://github.com/FirePh0enix): An outstanding teammate who was instrumental in implementing raycasting, a significant portion of the multiplayer functionality, and the minimap.
