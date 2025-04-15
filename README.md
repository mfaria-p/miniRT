# MiniRT: Introduction to Raytracing

MiniRT is a lightweight raytracer built as part of the 42 curriculum. It introduces the core principles of raytracing, a powerful rendering technique for generating realistic lighting and shadows in 3D scenes. This project provides hands-on experience with 3D math, geometric transformations, lighting models, and low-level graphics.

---

## Features

- **Scene Parsing**: Parses and validates `.rt` files to configure the 3D scene.
- **Geometric Objects**: Supports rendering of spheres, planes, and cylinders.
- **Lighting**: Implements ambient, diffuse, and specular lighting using the Phong reflection model.
- **Camera**: Configurable field of view and orientation.
- **Transformations**: Objects can be translated, rotated, and scaled.
- **Rendering**: Outputs a 2D image using ray-object intersection calculations.
- **MiniLibX Integration**: Uses MiniLibX to display the rendered image in a window.

---

## File Structure

```
miniRT/
├── libft/                # Custom utility library
├── scenes/               # Example scene files (.rt)
├── srcs/                 # Source code
│   ├── camera.c          # Camera-related functionality
│   ├── hit.c             # Ray-object intersection handling
│   ├── iu_main.c         # Entry point of the program
│   ├── iu_render.c       # Rendering logic
│   ├── iu_scene_parser.c # Scene parsing logic
│   ├── light.c           # Lighting calculations
│   ├── object_create.c   # Object creation and initialization
│   ├── ray.c             # Ray-related calculations
│   ├── world.c           # World and scene management
│   └── ...               # Other supporting files
├── tests/                # Test cases for validation
├── Makefile              # Build system
└── README.md             # Project documentation
```

---

## How It Works

1. **Scene Parsing**: Reads `.rt` files to extract objects, lights, and camera data.
2. **Ray Casting**: Rays are cast from the camera through each pixel to detect object intersections.
3. **Lighting**: The final pixel color is computed using the Phong lighting model.
4. **Rendering**: The computed image is displayed via MiniLibX.

---

## Example Scene File (`example.rt`)

```
A    0.2              255,255,255
C    -5.0,0,2         1,0,0         70
pl   0.0,0.0,10.0     0.0,0.0,1.0   255,0,0
L    -4.0,0.0,2       0.7           10,0,255
sp   0.0,0.0,2.06     1.6           10,0,255
cy   5.0,0.0,2        0.0,0.0,1.0   14.2   21.42   10,0,255
```

- A: Ambient light with intensity 0.2 and color 255,255,255 (white).
- C: Camera positioned at (-5.0, 0, 2) looking in the direction (1, 0, 0) with a field of view of 70.
- pl: Plane at (0.0, 0.0, 10.0) with a normal vector (0.0, 0.0, 1.0) and color 255,0,0 (red).
- L: Light source at (-4.0, 0.0, 2) with brightness 0.7 and color 10,0,255 (purple).
- sp: Sphere at (0.0, 0.0, 2.06) with a diameter of 1.6 and color 10,0,255 (purple).
- cy: Cylinder at (5.0, 0.0, 2) with orientation (0.0, 0.0, 1.0), diameter 14.2, height 21.42, and color 10,0,255 (purple).

---

## How to Build and Run

### Clone the Repository

```bash
git clone https://github.com/yourusername/miniRT.git
cd miniRT
```

### Build the Project

```bash
make
```

### Run the Program

```bash
./miniRT scenes/example.rt
```

---

## Controls: Navigating the World

### Camera Movement

- **Select Camera**: Click on `C` in the scene
- **Move Forward**: `W`
- **Move Backward**: `S`
- **Move Right**: `D`
- **Move Left**: `A`
- **Move Up**: `Space`
- **Move Down**: `Shift`

### Object Manipulation

- **Select an Object**: Right-click with the mouse on the desired object
- **Translate Object**: Select with right-click, move using `W`, `A`, `S`, `D`, `Space`, `Shift` keys
- **Rotate Object**: Click and drag with mouse
- **Scale Object**:
  - Increase Size: `Up Arrow` key
  - Decrease Size: `Down Arrow` key
  - Increase Height: `Right Arrow` key
  - Decrease Height: `Left Arrow` key

### Light Manipulation

- **Select Light**: Click on `L` in the scene
- **Move Light**: After selecting, move using `W`, `A`, `S`, `D`, `Space`, `Shift` keys

---

## Dependencies

- [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx): Lightweight graphics library.
- [libft](https://github.com/yourusername/libft): Custom utility functions.

---

Happy Raytracing! ✨

