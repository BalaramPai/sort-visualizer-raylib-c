# Sort Visualiser in C

An interactive Sorting Visualiser written in **C** using **Raylib** and **raygui**.

This project was built as a learning project to understand computer graphics, sorting algorithms, animation, and GUI programming in C.

---

## Features

- Interactive graphical user interface using **raygui**
- Bubble Sort visualization
- Selection Sort visualization
- Random array generation using Fisher-Yates Shuffle
- Start / Pause / Resume controls
- Reset button
- Algorithm selection dropdown
- Swap highlighting in **Red**
- Sorted array highlighted in **Green**
- Resizable application window
- Adjustable number of bars through source code
- Adjustable animation speed using FPS

---

## Concepts Learned

This project helped me understand:

- Bubble Sort
- Selection Sort
- Fisher-Yates Shuffle
- Graphics Programming using Raylib
- GUI Programming using raygui
- Rendering Loops
- Coordinate Systems
- Animation using FPS
- Structs in C
- State Management
- Interactive Event Handling

---

## Project Structure

```
SortVisualiser/
│
├── visualSort.c              # Original implementation
├── visualSortEnhanced.c      # Interactive version with GUI
├── raygui.h                  # raygui header
├── README.md
└── .gitignore
```

---

## Requirements

- Ubuntu / WSL Ubuntu
- GCC
- Git
- CMake
- Raylib 5.5
- OpenGL Development Libraries

---

## Installing Dependencies

Update package lists:

```bash
sudo apt update
```

Install development packages:

```bash
sudo apt install git build-essential cmake \
libasound2-dev mesa-common-dev \
libx11-dev libxrandr-dev libxi-dev \
libgl1-mesa-dev libglu1-mesa-dev \
libxcursor-dev libxinerama-dev \
libwayland-dev libxkbcommon-dev
```

---

## Installing Raylib 5.5

Clone Raylib:

```bash
cd ~

git clone --branch 5.5 https://github.com/raysan5/raylib.git
```

Build Raylib:

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

## Installing raygui

Download the latest `raygui.h` from the official repository:

https://github.com/raysan5/raygui

Place `raygui.h` inside the project directory.

---

## Compilation

### Original Version

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

### Enhanced Version

```bash
gcc visualSortEnhanced.c -o visualSortEnhanced \
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

### Original Version

```bash
./visualSort
```

### Enhanced Version

```bash
./visualSortEnhanced
```

---

## Current Implementation

### Original Version

- Fisher-Yates Shuffle
- Bubble Sort
- Animated visualization
- Swap highlighting
- Sorted state detection

### Enhanced Version

- Bubble Sort
- Selection Sort
- Interactive GUI
- Dropdown algorithm selector
- Start button
- Pause / Resume
- Reset
- Status indicator
- Resizable window
- Dynamic bar rendering
- Swap highlighting
- Sorted state detection

---

## Future Improvements

- Insertion Sort
- Merge Sort
- Quick Sort
- Heap Sort
- Shell Sort
- Speed Slider
- Array Size Slider
- Comparison Counter
- Swap Counter
- Sorting Statistics
- Randomize Button
- Dark / Light Themes
- Sound Effects
- Complexity Information Panel

---

## Author

**Balaram**

Built while learning graphics programming and data structures in C using Raylib.