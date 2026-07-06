# Sort Visualiser in C

A simple Bubble Sort visualizer written in C using the Raylib graphics library.

This project was built as a learning project to understand:

- Bubble Sort
- Fisher-Yates Shuffle
- Graphics programming using Raylib
- Rendering loops
- Coordinate systems
- Animation using FPS
- Structs in C

---

## Features

- Random array generation using Fisher-Yates Shuffle
- Bubble Sort visualization
- Swapped bars highlighted in **Red**
- Sorted array highlighted in **Green**
- Adjustable number of bars
- Adjustable animation speed

---

## Project Structure

```
SortVisualiser/
│
├── visualSort.c     # Source code
├── README.md        # Documentation
```

---

## Requirements

- Ubuntu / WSL Ubuntu
- GCC
- CMake
- Git
- Raylib 5.5
- OpenGL Development Libraries

---

## Installing Dependencies

Update packages:

```bash
sudo apt update
```

Install development tools:

```bash
sudo apt install git build-essential cmake \
libasound2-dev mesa-common-dev libx11-dev \
libxrandr-dev libxi-dev libgl1-mesa-dev \
libglu1-mesa-dev libxcursor-dev \
libxinerama-dev libwayland-dev libxkbcommon-dev
```

---

## Installing Raylib 5.5

Clone Raylib:

```bash
cd ~

git clone --branch 5.5 https://github.com/raysan5/raylib.git
```

Build:

```bash
cd raylib

mkdir build

cd build

cmake ..

make -j$(nproc)
```

Install:

```bash
sudo make install

sudo ldconfig
```

Verify installation:

```bash
pkg-config --modversion raylib
```

Expected output:

```
5.5.0
```

---

## Compilation

Compile using:

```bash
gcc visualSort.c -o visualSort \
-I/usr/local/include \
-L/usr/local/lib \
-lraylib \
-lm \
-lpthread \
-ldl \
-lrt \
-lX11 \
-lXrandr \
-lXi \
-lXcursor \
-lXinerama \
-lXxf86vm
```

---

## Running

```bash
./visualSort
```

---

## Current Implementation

- Random number generation
- Fisher-Yates shuffle
- Bubble Sort
- One sorting step per frame
- Animated visualization
- Swap highlighting
- Sorted state detection

---

## Future Improvements

- Multiple sorting algorithms
- Adjustable speed
- Pause / Resume
- Restart button
- Statistics (comparisons and swaps)
- User Interface
- Keyboard controls

---

## Author

Balaram