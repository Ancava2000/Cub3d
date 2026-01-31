*This project has been created as part of the 42 curriculum by **acarro-v** and **azibechi**.*

## DESCRIPTION

```This project is inspired by the world-famous Wolfenstein 3D game, which is considered the first FPS ever created. It enable us to explore ray-casting. Our goal is to make a dynamic view inside a maze, where you will have to find your way.```

This project’s general objectives are:
- rigor.
- use of C.
- basic algorithms.
- information research.
- team collaboration.

Furthermore, as a graphic design project, cub3D enable us to improve our skills in these
areas:
- windows.
- colors.
- events.
- fill shapes.
- raycasting.
- MLX42 library.
- computer graphics.
- map parsing.

```In conclusion, cub3D is a remarkable playground to explore the playful practical applications of mathematics without having to understand the specifics. With the help of numerous documents available on the internet, we use mathematics as a tool to create elegant and efficient algorithms.```

***

## INSTRUCTIONS

Our project's directory is organized into two modules:
```
src/
├── main.c        # Allocate memory, call all functions and initialize parse structures.
├── parse/        # Parse all the data (colors, textures, paths, map,...).
├── executor/     # Initialize the game, raycasting and movement variables. Ray-casting engine.
├── textures/     # Load the textures.
├── error_msg.c   # Utils functions (cleanup, errors, etc.).
├── maps/         # Folder with correct and incorrect maps.

include/
├── cub3d.h       # Main library.
├── libft         # Utils library.
├── MLX42         # Graphics library.
```

### Compilation
The project includes a Makefile with standard rules:
```
make        # Compiles cub3D
make clean  # Removes object files and executable
make fclean # Make clean and removes Libft objects and .a too
make re     # Recompiles everything
```

### Flags
All source files must compile with:
```
cc -Wall -Wextra -Werror
```
### Libraries
First you have to fully build the MLX42 library and install it to your system with the following command:

```
cmake -B build # build here refers to the outputfolder.
cmake --build build -j4 # or do make -C build -j4
```

The output library file is called libmlx42.a and is located in the build folder that you specified.

You'll need to link cub3d with the MLX42 and libft library:
```
# Linux
cc -Wall -Wextra -Werror *.c libft/libft.a MLX42/build/libmlx42 -lmlx42 -lglfw -ldl -lm -pthread
```

### Usage
```
./cub3D src/maps/good/valid_map.cub
```
The program takes a scene description file (textures path, colors and map) with .cub extension and displays the 3D view thanks to ray-casting.

***

## RESOURCES
### MLX42
- [MLX42 repository](https://github.com/codam-coding-college/MLX42?tab=readme-ov-file#for-linux)
### Ray-Casting
- [Lode's raycasting](https://lodev.org/cgtutor/raycasting.html)
- [Raycasting for Cub3D](https://42-fran-byte-f94097.gitlab.io/docs/cub3d/cub3d-approach-es/#/)
- [Wolfenstein 3D code](https://github.com/id-Software/wolf3d)

***

## GAME CONTENT
### Map .cub example

```
# Textures path
NO ./textures/north.xpm    
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

# Colors in RGB format
F 220,100,0
C 225,30,0

# Map made of 1(walls), 0(floor, empty space) and NSWE(position and direction of the player)
        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```
### Controls
Movement:

```
W: Move forward
A: Move left
S: Move backward
D: Move right
```

Camera:

```
Left arrow: Rotate view left
Right arrow: Rotate view right
```

Exit:

```
ESC: Close window and quit program
Red x (window close button): Close window and quit program
```
