# Rush Hour - C++ Taxi Game 🚕

A complete C++ implementation of the classic sliding block puzzle game, **Rush Hour**, built for Linux environments. The objective is simple: drive the car around the grid, pick and drop the passengers, refuel and collect as many points as possible.

## 🌟 Features
* **Graphical User Interface:** Built using The C++ Template Image Processing Toolkit (CImg).
* **Object-Oriented Design:** Clean and modular code using custom game classes.
* **Audio Integration:** Includes background music and sound effects for an immersive experience.
* **Classic Puzzle Mechanics:** Accurate grid movement and collision detection.

## 📂 Project Structure
* `/GameClasses` - Contains the core object-oriented logic for the grid, vehicles, and game state.
* `/Sound` - Audio files and sound management assets.
* `CImg.h` - The core header file used for rendering the graphics and managing the display window[cite: 1].
* `main.cpp` - The entry point of the game.
* `Makefile` - The build automation script.

## 🛠️ Prerequisites & Setup

This project is configured to run on **Linux**. Before compiling, ensure you have the required development libraries installed.

### Installing Dependencies
Run the following command in your terminal to install the necessary build tools and graphics libraries:

```bash
sudo apt-get install make freeglut3-dev glew-utils libglew-dev libfreeimage-dev

## 🚀 How to Build and Run

Open your Linux terminal in the project root directory and run the following commands:

### 1. Compile the Project
To compile the source code and generate the executable file, execute:
```bash
make

### 2. Run the Game
To launch the game directly via the Makefile after a successful build, execute:
```bash
make run

### 3. Clean Build Files
To delete the compiled binary and clean up your workspace, execute:
```bash
make clean