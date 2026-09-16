# MiniRT

This project has been created as part of the 42 curriculum by spaipur and uvadakku.

MiniRT is a minimal ray‑tracing engine written in C. It loads a `.rt` scene file, parses objects and lights, and renders a simple 3D image using ray casting, intersection tests, and basic lighting.

## Scene Syntax (Reference)

- **Ambient (A):** `A <ratio> <R,G,B>` — ratio `0.0–1.0`, color `0–255` per channel. One ambient allowed.
- **Camera (C):** `C <pos> <orient> <FOV>` — orient must be normalized; one camera allowed.
- **Light (L):** `L <pos> <brightness> <R,G,B>` — brightness `0.0–1.0`.
- **Sphere (sp):** `sp <center> <diameter> <R,G,B>`
- **Plane (pl):** `pl <point> <normal> <R,G,B>` — normal should be normalized.
- **Cylinder (cy):** `cy <center> <orientation> <diameter> <height> <R,G,B>`

Each element has a fixed format: vectors, colors, ratios, and sizes.

### Minimal `.rt` Example

```text
A 0.2 255,255,255
C 0,0,0 0,0,1 70
L 10,10,10 0.7 255,255,255
sp 0,0,20 5 255,0,0
```

## Build and Run

Build and run a sample scene:

```sh
cd miniRT
```

### Build

Linux (X11) or macOS

```sh
make
```

MiniLibX (platform-specific)

### Run

```sh
./miniRT scenes/test.rt
```

### Clean

```sh
make clean
make fclean
```

## General Rules

- Values are separated by spaces. Vectors use `x,y,z` notation.
- Colors use `R,G,B` with integer values `0–255`.
- Lines starting with `#` are comments (useful for annotations).

## Mathematical Concepts

### Vector Operations

MiniRT relies heavily on basic vector math because rays, normals, and directions are all vectors.

- **Add/subtract** — used to compute directions (e.g., light − hit point), move points, and build rays.
- **Dot product** — measures how aligned two vectors are; essential for diffuse lighting (Lambert’s law).
- **Cross product** — used to build camera orientation (right/up vectors) and ensure orthogonality.
- **Normalization** — converts a vector to length 1; required for stable lighting and ray direction calculations.

These operations form the mathematical backbone of ray tracing.

### Ray–Object Intersection Tests

MiniRT computes where a ray hits an object using analytic formulas.

- **Ray–sphere** — solve a quadratic equation to find where the ray meets the sphere surface.
- **Ray–plane** — solve a linear equation using dot products; simplest intersection.
- **Ray–cylinder** — more complex; involves projecting the ray onto the cylinder axis and solving a quadratic.

These tests determine the closest visible object for each pixel.

### Projection Geometry and Camera Rays

MiniRT uses a simple pinhole camera model:

- The camera has a position, orientation, and FOV.
- For each pixel, MiniRT computes a ray direction by projecting the pixel into 3D space using the camera’s basis vectors (forward, right, up).
- This creates a ray that travels from the camera through the pixel into the scene.

This is how the 2D image becomes a 3D view.

### Lighting Model

MiniRT implements a basic but effective lighting pipeline:

- **Ambient** — constant base light so objects aren’t completely black.
- **Diffuse (Lambert)** — depends on angle between light direction and surface normal; gives soft shading.
- **Specular** — simple highlight based on reflection direction; adds shine to surfaces.

### Shadow Rays (Hard Shadows)

To determine if a point is lit:

- MiniRT sends a shadow ray from the hit point toward the light.
- If the ray hits another object before reaching the light, the point is in shadow.
- This produces hard shadows (no soft edges).

Shadow rays add depth and realism to the scene.

## References

- https://42-cursus.gitbook.io/guide/4-rank-04/minirt/understand-minirt
- https://m4nnb3ll.medium.com/minirt-mini-ray-tracer-a-42-the-network-graphical-project-d909bef10025
- https://github.com/allancrabelo/MiniRT
- https://books.google.de/books?id=YPblYyLqBM4C&pg=PA46&lpg=PA46&dq=ray+tracing+acne&source=bl&ots=yZe92KlmQ9&sig=6Bo8kzVJcAYEEAGjDeQhYut1RjI&hl=en&sa=X&ei=v-piU5OnEoz3oASpzoHACw&redir_esc=y#v=onepage&q=ray%20tracing%20acne&f=false
- https://harm-smits.github.io/42docs/libs/minilibx/images.html
- https://docs.nvidia.com/vpi/appendix_pinhole_camera.html
- https://42-cursus.gitbook.io/guide/4-rank-04/minirt/building-the-thing#parsing
- https://medium.com/@mansurimohamad92/the-mathematics-behind-the-minirt-42-project-a-comprehensive-exploration-213e149c85d8
- https://mrl.cs.nyu.edu/~dzorin/rendering/lectures/lecture3/lecture3.pdf
- https://developer.nvidia.com/discover/ray-tracing?utm_source=copilot.com
- https://medium.com/@abhapratiti27/image-processing-basics-understanding-pixels-image-sizes-formats-transformations-and-a62d5868ce25
