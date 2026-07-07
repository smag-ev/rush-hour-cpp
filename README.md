# Rush Hour - C++ Taxi Game 🚕

A complete C++ implementation of the classic sliding-block puzzle game **Rush Hour**, built for Linux environments. The objective is simple: drive the taxi around the grid, pick up and drop off passengers, refuel when necessary, and earn as many points as possible.

## 🌟 Features

- **Graphical User Interface:** Built using the **C++ Template Image Processing Toolkit (CImg)**.
- **Object-Oriented Design:** Clean, modular, and maintainable code using custom game classes.
- **Audio Integration:** Background music and sound effects for a more immersive experience.
- **Classic Puzzle Mechanics:** Grid-based movement with accurate collision detection.

## 📂 Project Structure

```
.
├── GameClasses/    # Core object-oriented game logic
├── Sound/          # Audio files and sound assets
├── CImg.h          # Graphics rendering library
├── main.cpp        # Entry point of the game
└── Makefile        # Build automation script
```

## 🛠️ Prerequisites

This project is configured to run on **Linux**.

Before compiling, install the required development tools and graphics libraries:

```bash
sudo apt-get install make freeglut3-dev glew-utils libglew-dev libfreeimage-dev
```

## 🚀 Build and Run

Open a terminal in the project root directory.

### 1. Compile the Project

Build the source code and generate the executable:

```bash
make
```

### 2. Run the Game

Launch the game after a successful build:

```bash
make run
```

### 3. Clean Build Files

Remove the compiled executable and other generated build files:

```bash
make clean
```

## 📌 Notes

- Developed for Linux using **GNU Make**.
- Ensure all required dependencies are installed before building.
- Audio assets must remain inside the `Sound/` directory for the game to function correctly.
