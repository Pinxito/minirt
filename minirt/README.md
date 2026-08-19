*This project has been created as part of the 42 curriculum by gguillen, hcostoso.*

# MiniRT

## Description

MiniRT is a small 3D ray-tracing project inspired by the classic `miniRT` assignment from the 42 curriculum. The goal of the project is to render simple 3D scenes made of basic geometric objects using a ray-tracing approach, simulating camera, lighting, and shading.

The program parses scene files written in a custom `.rt` format, then renders the result in a window using the MiniLibX graphics library. The project focuses on core ray-tracing concepts such as ray generation, intersection testing, and Lambertian lighting, while keeping the implementation compact and educational.

This project includes support for:

- Spheres
- Planes
- Cylinders
- Camera setup with field of view
- Ambient and directional light handling
- Basic shading and color computation
- Scene parsing from `.rt` files

## Instructions

### Requirements

- A Linux environment with X11 support
- `make` and a C compiler (`cc`)
- The bundled `minilibx-linux` library included in the repository

### Compilation

From the project root, run:

```bash
make
```

This will compile the executable named `minirt`.

### Execution

Run the program with a scene file as an argument:

```bash
./minirt <scene.rt>
```

Example:

```bash
./minirt tests/05_brightness/test_brightness_sphere.rt
```

Useful maintenance commands:

```bash
make clean
make fclean
make re
```

The program opens a window and renders the scene described in the `.rt` file.

## Usage Notes

The scene file format follows the project specification and supports elements such as:

- Ambient light: `A ratio R,G,B`
- Camera: `C x,y,z orientation FOV`
- Light: `L x,y,z brightness R,G,B`
- Sphere: `sp x,y,z diameter R,G,B`
- Plane: `pl x,y,z normal R,G,B`
- Cylinder: `cy x,y,z axis diameter height R,G,B`

You can find example scenes in the `tests/` directory to experiment with camera positioning, object intersections, lighting, and shadows.

## Resources

Classic references and documentation related to this topic:

- Wikipedia — Ray Tracing, Lambertian reflectance, geometric primitives
- MiniLibX documentation and examples

AI usage:

- Understanding and validating the ray intersection formulas
- Explaining shading and light computations
- Helping structure the project logic and C implementation details

This support was mainly used during the design and debugging phases.

## Project Summary

MiniRT is a compact introduction to real-time and offline rendering concepts through ray tracing. It offers a practical way to explore geometry, vectors, camera models, and lighting in C, while building a functional 3D renderer from scratch.
