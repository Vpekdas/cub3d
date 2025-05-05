# cub3d

## Screenshots

## Table of Contents
1. [Description](#description)
2. [Installation](#installation)
3. [Run](#run)
4. [Credits](#credits)
5. [Contributing](#contributing)

## Description

cub3d is a project from the 42 Common Core curriculum. The objective of this project is to replicate the mechanics of the classic game Wolfenstein 3D using raycasting. The game is developed using a minimalist graphics library called minilibx, which is part of the project's constraints. The goal is to understand the fundamentals of raycasting, texture mapping, and 3D graphics rendering in a 2D environment.

As part of the 42 curriculum, this project comes with strict coding guidelines:
- The standard C library is forbidden, requiring the use of custom code for all tasks.
- A strict rule of 5 functions per file and 25 lines per function is enforced.
- There are restrictions such as no assignments on the same line and a focus on clean, maintainable code.

This project provides hands-on experience with low-level graphical programming and reinforces good coding practices under challenging constraints.

### Purpose

The purpose of this program is to create a playable first-person shooter (FPS) with multiplayer support and custom maps. While it may not be as feature-rich as the original Wolfenstein 3D, it serves as a simplified and fun version of the classic game. You can find features below: 

- Advanced Collision System
- Multiplayer Mode
- Multiple Weapons
- Multiple Textures for Each Side of Walls (including floor and ceiling textures)
- Animated Weapons
- Minimap
- Interactive Doors

## Controls

| **Controls** | **Actions** |
|:------------:|-------------|
| `W` | Move Forward |
| `A` | Move Left |
| `S` | Move Backward |
| `D` | Move Right |
| `E` | Interact with door |
| `←` or Mouse Left | Turn Camera Left |
| `→` or Mouse Right | Turn Camera Right |
| `ESC` or Click the `X` in the Top-Right Corner | Exit the Game |

### Technologies used

- C language.
- Make.

## Challenges and Future Features

Since I was responsible for parsing, I encountered challenges related to handling input errors, such as:
Ensuring there were no more than four textures (one for each side of the wall) and that the textures were loaded correctly.

- Verifying the floor and ceiling colors: ensuring they fit within the RGB range, with one color for each, and no more.
- Validating the map: ensuring the player couldn't go outside the map, there was only one player (as required), and only the allowed characters were present.

Additionally, thanks to my teammate, I was introduced to multiplayer management. I was responsible for handling:
- Collision detection between players and walls, as well as between bullets and walls.
- Packet sending to the server to notify if a bullet hit another player.

This part of the project required me to understand some basic concepts of 3D physics and networking. The challenge of synchronizing multiplayer actions in real-time added a layer of complexity, but it was a valuable learning experience.

I'm not planning to add new features.

## Installation

- Ensure you have a C compiler installed, such as [Clang](https://clang.llvm.org/) or [GCC](https://gcc.gnu.org/)
```bash
clang --version
gcc --version
```
- Ensure you have installed [Make](https://www.gnu.org/software/make/) to build the project
```bash
make --version
```

- Install Necessary Packages: Certain packages are required to run the game. You can install them using your distribution's package manager. For example, on Ubuntu, you can use the following command:

- X11 include files (package xorg)
- XShm extension must be present (package libxext-dev)
- Utility functions from BSD systems - development files (package libbsd-dev)

```bash
sudo apt install xorg libxext-dev libbsd-dev
```

Warning: This game can only work in Unix systems sicne the functions used and the minilib functions called needs X11, in windows you can install [WSL](https://learn.microsoft.com/fr-fr/windows/wsl/install) and install packages. In Macos, it wont works.

/!\ Warning: This game is designed to run only on Unix-based systems because the functions used and the minilibx functions require X11. As a result, it may not work on Windows or macOS without additional steps:

- Windows: You can install WSL (Windows Subsystem for Linux) and set up the necessary packages to run the game.
- MacOS: Unfortunately, the game won't work on macOS as it doesn't support the necessary X11 functions natively.

## Run

1. Build the project:
```bash
make bonus
```
The bonus rule ensure all features are enabled.

2. This will create a `./cub3d` binary.

3. Run the program with the following arguments:

```bash
./cube3d [maps]
```

### Map Customization

The maps for the game are stored in files with the .cub extension. These are essentially text files where the game’s layout and elements are defined. You can find our pre-configured maps in the assets/maps directory.

When creating a custom map, be sure to follow these rules to ensure proper functionality:

#### 1. Player Boundaries
Ensure that the player cannot go outside the map's boundaries. If the player can escape the map, the algorithm will refuse the map and display an error.

#### 2. Map File Syntax
Each map file contains different sections that define walls, textures, and more. Some key elements are:
- NO: Refers to the texture used for the North wall.
- SO: Refers to the texture used for the South wall.
- WE: Refers to the texture used for the West wall.
- EA: Refers to the texture used for the East wall.
- F: Refers to the color used for the floor. It’s represented as an RGB value (e.g., F 255,255,255 for white).
- C: Refers to the color used for the ceiling. It’s also represented as an RGB value (e.g., C 0,0,0 for black).
##### Map Layout:
- 1 Refers to walls in the map, which the player cannot pass through.
- 0 Refers to empty spaces where the player can walk.
- N, S, E, W: Indicates the direction where the player will spawn (North, South, East, West). Only one spawn point is allowed per map.
- D: Refers to a door in the map.

## Credits

- [FirePh0enix](https://github.com/FirePh0enix): An outstanding teammate who was instrumental in implementing raycasting, a significant portion of the multiplayer functionality, and the minimap.

## Contributing

To report issues, please create an issue here:  [issue tracker](https://github.com/Vpekdas/cub3d/issues).

To contribute, follow these steps:

1. **Fork the repository**: Start by forking the repository to your own GitHub account.

2. **Clone the repository**: Clone the forked repository to your local machine.
```bash
git clone https://github.com/Vpekdas/cub3d
```

3. **Create a new branch**: Create a new branch for each feature or bug fix you're working on.
```bash
git checkout -b your-branch-name
```

4. **Commit your changes**: Commit your changes.
```bash
git commit -m "Your commit message"
```

5. **Push your changes**: Push your changes to your forked repository on GitHub.
```bash
git push origin your-branch-name
```

6. **Create a pull request**: Go to your forked repository on GitHub and create a new pull request against the master branch.
