## Ray Tracing Renderer

# Overview
MiniRT is a ray tracing program written in C that generates realistic 3D images from scene descriptions.

This project implements the fundamentals of ray tracing to render simple 3D scenes with lighting, shadows, and multiple object types.

Created in collaboration with Luke Lai (@SimpleLuke).

# Features
- **Ray tracing engine**: Creates realistic images by simulating light behavior
- **Multiple 3D primitives**: Supports spheres, planes, and cylinders
- **Light system**: Implements ambient and diffuse lighting with proper shadows
- **Scene configuration**: Reads scene definitions from `.rt` files
- **Camera system**: Configurable position, orientation, and field of view
- **Transformations**: Support for object translation and rotation

# Technical Implementation
- Written in C using the MiniLibX graphics library
- Handles object intersections with mathematical precision
- Memory management optimised to prevent leaks
- Error handling for invalid scene configurations

# Scene File Format
The program reads scene descriptions from files with the `.rt` extension. 
Here's an example:
```
A 0.2 255,255,255                             # Ambient lighting
C -50,0,20 0,0,1 70                           # Camera
L -40,0,30 0.7 255,255,255                    # Light source
pl 0,0,0 0,1.0,0 255,0,225                    # Plane
sp 0,0,20 20 255,0,0                          # Sphere
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255  # Cylinder
```

# Elements:
- **A**: Ambient lighting (ratio, RGB color)
- **C**: Camera (position, orientation vector, FOV)
- **L**: Light source (position, brightness, RGB color)
- **pl**: Plane (point in plane, normal vector, RGB color)
- **sp**: Sphere (center position, diameter, RGB color)
- **cy**: Cylinder (center, axis vector, diameter, height, RGB color)

# Usage
```bash
./miniRT <scene_file.rt>
```

# Controls
You can close the program by either pressing ESC key or clicking the cross button.

# Building
```bash
make        # Compile the program
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Rebuild the program from scratch
```

# Demo Images
![1](https://github.com/user-attachments/assets/01d61cf4-8a6b-44de-8060-142b4460803c)

![2](https://github.com/user-attachments/assets/8076a3ab-e477-485c-958e-6b62b360d856)

![3](https://github.com/user-attachments/assets/f7b0f063-4d3e-408f-971d-f9a916ce0f2e)

# Technical Requirements
- MiniLibX library
- Math library
- C compiler with standard libraries

# Notes
- This is an educational project focused on understanding ray tracing concepts
- The implementation prioritises correctness over performance optimisation
- Scene complexity is limited to maintain reasonable rendering times
