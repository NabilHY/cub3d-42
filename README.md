
# Cub3d - 42

## Project Overview

The RayCaster project is inspired by the legendary *Wolfenstein 3D*, the first true first-person shooter (FPS) game. This project enables exploration of ray-casting techniques by creating a dynamic 3D view inside a maze. The primary objective is to implement a functional raycasting engine that transforms a 2D map into a 3D graphical representation.

## Contributors

This project was developed collaboratively by:
	

 - Nabil Hayoun:

	  
	       intra: https://profile.intra.42.fr/users/nhayoun
	       github: https://github.com/NabilHY
	

 - Ahmed Mazzouzi:

		intra: https://profile.intra.42.fr/users/ael-maaz
		github: https://github.com/SaladBunda

## Ray-Casting Method

Raycasting is a rendering technique used to project a 2D representation into a 3D space. It involves casting rays from the player's viewpoint to determine visibility and depth, allowing for realistic visual effects in the rendered environment.

## Technology Stack

- **Programming Language:** C
- **Graphics Library:** mlx42 (included as a submodule)
- **Development Environment:** Linux/macOS

## Running the Project

To compile and run the project, follow these steps:

Navigate to the project directory.
Run the following command based on your operating system:
For Linux:
   

	    make linux

For macOS:

	    make macos

After successfully building the project, run the executable with a map of your choice:

		./cub3D maps/textures/map.cub

## Makefile Instructions

The project includes a Makefile with rules tailored for both Linux and macOS environments, ensuring compatibility based on the architecture. Below are the main rules:

- **linux:** Compile the source files and create the executable in a linux environment.
- **macos:** Compile the source files and create the executable in a macos environment.
- **all:** Compile the source files and create the executable (Defaults to linux).
- **clean:** Remove object files and other temporary files.
- **fclean:** Remove all files created by the build process, including the executable.
- **re:** Clean and rebuild the project from scratch.


### Project Structure

			srcs/: Contains the source files for the raycasting engine.
			includes/: Header files for function declarations and definitions.
			textures/: Directory for texture images used in the maze.
			maps/: Directory for .cub map files that define the maze layout.

### Gameplay Instructions

The player navigates through the maze using the keyboard:

			Arrow Keys: Look left and right.
			W, A, S, D: Move through the maze.
			ESC: Exit the game cleanly.
			Mouse: Rotate the viewpoint.


### Map Format

The maze is defined in a .cub file with the following structure:

Characters used:
0: Empty space
1: Wall
N, S, E, W: Player start position and orientation
Example Map :

    NO ./path_to_the_north_texture
    SO ./path_to_the_south_texture
    WE ./path_to_the_west_texture
    EA ./path_to_the_east_texture
    F 220,100,0
    C 225,30,0

    111111
    100101
    101001
    1100N1
    111111


### Features

	Wall collisions detection.
	A minimap system for navigation.
	Mouse-based viewpoint rotation.

### Conclusion

The RayCaster project serves as an educational exercise in graphics programming, applying fundamental concepts of mathematics and algorithms to create an engaging 3D experience. The use of the mlx42 graphics library facilitates window management and rendering, enhancing the learning experience of developing a graphical application in C.

